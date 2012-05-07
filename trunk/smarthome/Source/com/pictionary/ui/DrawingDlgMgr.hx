package com.pictionary.ui;

import base.social.SocialMgr;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogType;
import com.eclecticdesignstudio.dialog.DialogData;
import com.eclecticdesignstudio.dialog.events.DialogEvent;
import com.eclecticdesignstudio.motion.Actuate;

import base.network.NetworkMgr;
import nme.geom.Matrix;
import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;
import base.ui.CommDialogMgr;

import nme.geom.Rectangle;
import nme.display.Bitmap;
import nme.display.BitmapData;

import haxe.io.Bytes;
import haxe.io.BytesBuffer;

import haxe.Timer;

class DrawingDlgMgr extends CommDialogMgr{

    var _downy:Float;
    var _downx:Float;
    var _movey:Float;
    var _movex:Float;

    var _oldx:Float;
    var _oldy:Float;

    var _isDown:Bool;

    var _view:Sprite;
    var _returnParent:Sprite;
    public var _returnCallback:Dynamic;
    public var _dispatchCallback:Array<Bytes>->Void;

    var _edit:Sprite;
    var _erase:Sprite;
    var _upload:Sprite;
    var _isFixed:Bool;

    var _pressTime:Float;
    var _releaseTime:Float;
    public inline static var RightEdge:Float  = 768;
    public inline static var BottomEdge:Float  = 1024;

    //the max edge the usr drawn
    var _maxWidth:Int;
    var _maxHeight:Int;

    var _bmd:BitmapData;
    var _bm:Bitmap;
    var _rect:Rectangle;

    var _linesArr:Array< Bytes >;
    var _lines:BytesBuffer;

    var x1:Int;
    var y1:Int;
    var x2:Int;
    var y2:Int;
    var x3:Int;
    var y3:Int;
    var x4:Int;
    var y4:Int;

    public function new (droppoint:Sprite ){
        _view= new Sprite();
        droppoint.addChild(_view);
        super( _view);
        _view.cacheAsBitmap = false;

        var w =  nme.Lib.current.stage.stageWidth;
        var h =  nme.Lib.current.stage.stageHeight;
        _bmd = new BitmapData(w + RightEdge, h+BottomEdge , true,0 );
        _rect = new Rectangle( 0, 0, w, h);

        _oldx = _view.x;
        _oldy = _view.y;
        _isDown = false;
        _linesArr = new Array<Bytes>();
        _lines = new BytesBuffer();

        _returnParent = new Sprite();
        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("btn_return"));
        _returnParent.addChild( bm);
        _returnParent.x = nme.Lib.current.stage.stageWidth - 80;
        _returnParent.y= nme.Lib.current.stage.stageHeight - 80;
        _returnParent.addEventListener( MouseEvent.CLICK, onClickReturn);

        _edit = new Sprite();
        bm= new Bitmap( DataLoader.getInst().bms_.get("btn_edit"));
        _edit.addChild( bm);
        _edit.x = nme.Lib.current.stage.stageWidth - 160;
        _edit.y= nme.Lib.current.stage.stageHeight - 80;
        _edit.addEventListener( MouseEvent.CLICK, onClickEdit);


        _erase = new Sprite();
        bm= new Bitmap( DataLoader.getInst().bms_.get("erase"));
        _erase.addChild( bm);
        _erase.x = 60;
        _erase.y= nme.Lib.current.stage.stageHeight - 80;
        _erase.addEventListener( MouseEvent.CLICK, onClickErase);

        _upload= new Sprite();
        var m = new Matrix();
        m.rotate(3.14/2);
        m.translate( 60, 0);
        var bmt = DataLoader.getInst().bms_.get("exit");
        var bmd = new BitmapData(bmt.width, bmt.height);
        bmd.draw( bmt, m);
        bm= new Bitmap( bmd);
        _upload.addChild( bm);
        _upload.x = 160;
        _upload.y= nme.Lib.current.stage.stageHeight - 80;
        _upload.addEventListener( MouseEvent.CLICK, onClickUpload);


        _isFixed = true;

    }

    public function showListDialog():Void{
        //if ( getInstancesByDisplayOrder() != null ){
        //setAnimationNum(getInstancesByDisplayOrder().length);
        //var c:Int = 0;
        //for ( i in getInstancesByDisplayOrder()){
        //++c;
        //i.show().delay(0.05 * c).onComplete( decreaseAnimationNum, []);
        //}
        //}
        _isDown = false;
        if ( _returnParent.parent == null ) {
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            nme.Lib.current.stage.addEventListener( Event.ENTER_FRAME , onEnterFrame);
            nme.Lib.current.addChild(_returnParent);
            nme.Lib.current.addChild(_edit);
            nme.Lib.current.addChild(_erase);
            nme.Lib.current.addChild(_upload);
            cacheBitmapData();
        }
        _isFixed = true;
        //fixedDialog(_isFixed);
    }
    public function hideListDialog( ):Void{
        //for ( i in getInstancesByDisplayOrder()){
        //i.hide();
        //}
        _isDown = false;
        if ( _returnParent.parent != null ) {
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            nme.Lib.current.stage.removeEventListener( Event.ENTER_FRAME, onEnterFrame);
            nme.Lib.current.removeChild(_returnParent);
            nme.Lib.current.removeChild(_edit);
            nme.Lib.current.removeChild(_erase);
            nme.Lib.current.removeChild(_upload);
        }
    }
    public override function clear():Void{
        hideListDialog();
        super.clear();
        _returnParent = null;
        _returnCallback = null;
        _dispatchCallback = null;
        _edit = null;
        _erase =null;
        _upload = null;
        _bmd = null;
        _bm = null;
        _rect = null;
        _linesArr = null;
        _lines = null;
    }

    inline public function draw( data:Array<Bytes> ){
        _view.graphics.lineStyle( 5, 0xf75544, 0.75);

        for ( line in data){
            var pos:Int = 0;
            _view.graphics.moveTo( NetworkMgr.bytes2Short(line, 0), NetworkMgr.bytes2Short(line, 2) );
            pos+=4;
            while ( pos < line.length){
                _view.graphics.lineTo( NetworkMgr.bytes2Short(line, pos), NetworkMgr.bytes2Short(line, pos+2) );
                pos+=4;
            }
        }
    }

    inline public function dispatchDrawing(){

        //trace( "line len: "+ b.length );
        if( _dispatchCallback != null){
            var b = _lines.getBytes();
            _linesArr.push( b);
            _dispatchCallback( _linesArr);
            _lines = new BytesBuffer();
        }
    }

    inline public function storePoint( x:Int, y:Int){
        //_lines.push( (x << 16) + y);
        _lines.add( base.network.NetworkMgr.short2Bytes(x) );
        _lines.add( base.network.NetworkMgr.short2Bytes(y) );
    }

    public function onMouseDown(evt:MouseEvent){ 
        //trace( "DrawingDlgMgr onMouseDown");
        if ( isAnimating()  ) return;
        if(_edit.hitTestPoint(evt.stageX,evt.stageY ) ||
                _returnParent.hitTestPoint(evt.stageX, evt.stageY)||
                _erase.hitTestPoint(evt.stageX, evt.stageY)||
                _upload.hitTestPoint(evt.stageX, evt.stageY)
          ){ 
            //trace("hit");
            return; 
        }

        _downx = evt.stageX;
        _downy = evt.stageY;
        _movex= 0;
        _movey= 0;
        _oldx = evt.stageX;
        _oldy = evt.stageY;


        //_view.graphics.moveTo(250, 0);
        //_view.graphics.curveTo(300, 0, 300, 50);
        //_view.graphics.curveTo(300, 100, 250, 100);
        //_view.graphics.curveTo(200, 100, 200, 50);
        //_view.graphics.curveTo(200, 0, 250, 0);
        if( _isFixed ){
            _view.graphics.lineStyle(10, 0xf75544, 0.75);
            //_view.graphics.beginFill(0xf75544, 0.75);

            var x:Int = cast (evt.stageX - _view.x);
            var y:Int = cast (evt.stageY - _view.y);
            _view.graphics.moveTo(x, y);

            x1 = x; y1 = y;
            x2 = x1; y2 = y1;
            x3 = x2; y3 = y2;
            //x4 = x3; y4 = y3;

            if ( _dispatchCallback != null){ storePoint( x, y); }

            var mw:Int = nme.Lib.current.stage.stageWidth - Std.int(_view.x);
            var mh:Int = nme.Lib.current.stage.stageHeight- Std.int(_view.y);
            if( _maxWidth < mw){ _maxWidth =  mw; }
            if( _maxHeight < mh){ _maxHeight = mh; }
        }
        else {
            _pressTime = 0;
        }
        _isDown = true;
    }
    public function onMouseMove(evt:MouseEvent):Void{ 

        if ( _isDown){
#if flash
            if( evt.stageX < 0 || evt.stageX > nme.Lib.current.stage.stageWidth || evt.stageY < 0 || evt.stageY > nme.Lib.current.stage.stageHeight ) {
                onMouseUp(evt);
                return;
            }
#end
            if ( !_isFixed){
                if ( _view.x >= -RightEdge || _view.y >= -BottomEdge){
                    _view.x += evt.stageX - _oldx;
                    if (_view.x <-RightEdge) _view.x = -RightEdge;
                    else if (_view.x >0) _view.x = 0;
                    _view.y += evt.stageY - _oldy;
                    if (_view.y <-BottomEdge) _view.y = -BottomEdge;
                    else if (_view.y > 0) _view.y = 0;
                    _oldx = evt.stageX;
                    _oldy = evt.stageY;

                    if( _maxWidth <  cast(- _view.x) + nme.Lib.current.stage.stageWidth){
                        _maxWidth = cast( - _view.x) + nme.Lib.current.stage.stageWidth;
                    }
                    if( _maxHeight < cast(- _view.y)+ nme.Lib.current.stage.stageHeight){
                        _maxHeight =  cast(- _view.y)+ nme.Lib.current.stage.stageHeight;
                    }

                }
                else{
                    trace("out range!");
                }

            }
            else {
                var x:Int = cast (evt.stageX - _view.x);
                var y:Int = cast (evt.stageY - _view.y);
                //_view.graphics.lineTo(x, y);
                //trace("drawing: "+ evt.stageX + " "+ evt.stageY);

                //x1 = x2; y1 = y2;
                //x2 = x3; y2 = y3;
                //x3 = x4; y3 = y4;
                //x4 = x; y4 = y;

                x1 = x2; y1 = y2;
                x2 = x3; y2 = y3;
                x3 = x; y3 = y;

                var cx = (x2 - x1)/4+x2;
                var cy = (y2 - y1)/4+y2;

                //var cx2 = (x3 - x4)/4+x3;
                //var cy2 = (y3 - y4)/4+y3;

                //x4 = x; y4 = y;
                //_view.graphics.cubicCurveTo(cx, cy, cx2, cy2, x3, y3);
                _view.graphics.curveTo(cx, cy, x3, y3);

                if (_dispatchCallback != null) storePoint( x, y);
            }
        }
    }

    public function onClickErase( evt:MouseEvent):Void{
        //_view.graphics.clear();
        if ( _bm != null && _bm.parent != null ){
            _bm.parent.removeChild( _bm);
        }
#if flash
        _bmd.fillRect( _bmd.rect,0);
#else
        _bmd.clear( 0x0);
#end
        _view.graphics.clear();
    }
    public function onClickEdit( evt:MouseEvent):Void{
        if( _isDown && _isFixed ){
            _view.graphics.moveTo(_oldx-_view.x, _oldy-_view.y);
        }
        _isFixed = !_isFixed;
        //fixedDialog( _isFixed);
    }


    public function onMouseUp(evt:MouseEvent){ 
        var x:Float = evt.stageX, y:Float = evt.stageY;
        //#if flash
        if ( evt.stageX < 0 ){ x = 0; }else x = evt.stageX;
        if ( evt.stageY < 0 ){ y = 0; }else y = evt.stageY;
        if ( evt.stageX > nme.Lib.current.stage.stageWidth ){ x = nme.Lib.current.stage.stageWidth; }else x = evt.stageX;
        if ( evt.stageY > nme.Lib.current.stage.stageHeight){ y = nme.Lib.current.stage.stageHeight; }else y = evt.stageY;
        //#end

        if ( _isDown){
            if ( _isFixed  ){
                //_view.graphics.endFill();
                if (_dispatchCallback != null) dispatchDrawing();
                _releaseTime = Timer.stamp();
            }
        }
        _downx = 10000;
        _downy = 10000;
        _isDown = false;
        _movex = 0;
        _oldx = 0;
        _oldy = 0;
    }

    public function uploadImg():Void{
        if( _pressTime > 0 ) cacheBitmapData();
        var bytes = base.common.Tools.converToPNGBytes( _bmd, _maxWidth, _maxHeight);

        var sina = SocialMgr.getInst()._socials.get( Type.getClassName( base.social.SinaWeibo) );
        if( sina!= null && sina.isBound()) {
            sina.updateNewStatusWithImg("test"+Timer.stamp(), bytes);
        }else{
            SocialMgr.getInst().bindSina();
        }
#if (!android && cpp)
        cpp.io.File.write("test.png", true).writeBytes( bytes, 0, bytes.length);
#end

    }

    public function onClickUpload( evt:Event){
        uploadImg();
    }


    public function onEnterFrame(evt:Event){
        if(  _isFixed &&  !_isDown  && _releaseTime > 0 && Timer.stamp() - _releaseTime > 1){
            cacheBitmapData();

            if( _pressTime > 0 ) cacheBitmapData();
            _pressTime = 0;
            _releaseTime = 0;
        }
    }

    public function cacheBitmapData():Void{
        var tx = _view.x;
        var ty = _view.y;
        _view.x = 0;
        _view.y = 0;
        //trace("end drawing: "+ _maxWidth+ " "+ _maxHeight+" " + tx+" "+ty);
        _rect.height = _maxHeight;
        _rect.width = _maxWidth;
        _bmd.draw(_view, _rect);
        if( _bm!=null && _bm.parent != null ) {
            _bm.parent.removeChild( _bm);
        }
        _bm = new Bitmap(_bmd);
        _view.addChild(_bm);
        _view.graphics.clear();
        _view.x = tx;
        _view.y = ty;
        trace("clear once");
    }

    //public function fixedDialog( flag:Bool){
    //if( flag){
    //for ( i in getInstancesByDisplayOrder()){
    //i.dialogData.type = DialogType.FIXED;
    //}
    //}else{
    //for ( i in getInstancesByDisplayOrder()){
    //i.dialogData.type = DialogType.DRAGGABLE;
    //}
    //}
    //}


    public function onClickReturn( evt:MouseEvent) :Void{

        onClickErase(null);
        if ( _returnCallback != null ){
            _returnCallback();
        }
        hideListDialog();
    }
}
