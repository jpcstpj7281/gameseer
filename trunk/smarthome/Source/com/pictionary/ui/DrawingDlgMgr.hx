package com.pictionary.ui;

import base.social.SocialMgr;
import com.eclecticdesignstudio.motion.Actuate;

import base.network.NetworkMgr;
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

    var _draw:Sprite;
    var _view:Sprite;
    public var _returnCallback:Dynamic;
    public var _dispatchCallback:Array<Bytes>->Void;

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
        _draw= new Sprite();
        _view.addChild(_draw);
        droppoint.addChild(_view);
        super( _view);
        //_draw.cacheAsBitmap = true;
        _draw.cacheAsBitmap = false;

        _maxWidth =  nme.Lib.current.stage.stageWidth;
        _maxHeight =  nme.Lib.current.stage.stageHeight;
        _bmd = new BitmapData( _maxWidth, _maxHeight, true, 0);
        _rect = new Rectangle( 0, 0, _maxWidth, _maxHeight);

        _oldx = _draw.x;
        _oldy = _draw.y;
        _isDown = false;
        _linesArr = new Array<Bytes>();
        _lines = new BytesBuffer();

        new base.ui.ReturnDlg( this , returnCallback);
        new UploadImgDlg(this);
        new base.ui.EditDlg(this);
        new EraseDlg(this);
        _draw.visible = false;
        _isFixed = true;
    }

    public override function showListDialog():Void{
        _isDown = false;
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);
        nme.Lib.current.stage.addEventListener( Event.ENTER_FRAME , onEnterFrame);
        _draw.visible = true;
        cacheBitmapData();
        super.showListDialog();
        _isFixed = true;
    }
    public override function hideListDialog( ):Void{
        _isDown = false;
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_UP, onMouseUp);
        nme.Lib.current.stage.removeEventListener( Event.ENTER_FRAME, onEnterFrame);
        _draw.visible = false;
        super.hideListDialog();
    }
    public override function clear():Void{
        hideListDialog();
        super.clear();
        _returnCallback = null;
        _dispatchCallback = null;
        _bmd = null;
        _bm = null;
        _view = null;
        _draw = null;
        _rect = null;
        _linesArr = null;
        _lines = null;
    }

    inline public function draw( data:Array<Bytes> ){
        _draw.graphics.lineStyle( 5, 0xf75544, 0.75);

        for ( line in data){
            var pos:Int = 0;
            _draw.graphics.moveTo( NetworkMgr.bytes2Short(line, 0), NetworkMgr.bytes2Short(line, 2) );
            pos+=4;
            while ( pos < line.length){
                _draw.graphics.lineTo( NetworkMgr.bytes2Short(line, pos), NetworkMgr.bytes2Short(line, pos+2) );
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
        _downx = evt.stageX;
        _downy = evt.stageY;

        for ( i in _instancesByDisplayOrder){
            if( i.hitTestPoint(evt.stageX, evt.stageY)){
                return;
            }
        }

        _movex= 0;
        _movey= 0;
        _oldx = evt.stageX;
        _oldy = evt.stageY;

        if( _isFixed ){
            _draw.graphics.lineStyle(10, 0xf75544, 0.75);
            //_draw.graphics.beginFill(0xf75544, 0.75);

            var x:Int = cast (evt.stageX - _draw.x);
            var y:Int = cast (evt.stageY - _draw.y);
            _draw.graphics.moveTo(x, y);

            x1 = x; y1 = y;
            x2 = x1; y2 = y1;
            x3 = x2; y3 = y2;
            //x4 = x3; y4 = y3;

            if ( _dispatchCallback != null){ storePoint( x, y); }

            var mw:Int = nme.Lib.current.stage.stageWidth - Std.int(_draw.x);
            var mh:Int = nme.Lib.current.stage.stageHeight- Std.int(_draw.y);
            if( _maxWidth < mw){ _maxWidth =  mw; }
            if( _maxHeight < mh){ _maxHeight = mh; }
        }
        else {
            _pressTime = 0;
        }
        _isDown = true;
    }
    public function onMouseMove(evt:MouseEvent):Void{ 

        if ( isAnimating()  ) return;
        if ( _isDown){
#if flash
            if( evt.stageX < 0 || evt.stageX > nme.Lib.current.stage.stageWidth || evt.stageY < 0 || evt.stageY > nme.Lib.current.stage.stageHeight ) {
                onMouseUp(evt);
                return;
            }
#end
            if ( !_isFixed){
                if ( _draw.x >= -RightEdge || _draw.y >= -BottomEdge){
                    _draw.x += evt.stageX - _oldx;
                    if (_draw.x <-RightEdge) _draw.x = -RightEdge;
                    else if (_draw.x >0) _draw.x = 0;
                    _draw.y += evt.stageY - _oldy;
                    if (_draw.y <-BottomEdge) _draw.y = -BottomEdge;
                    else if (_draw.y > 0) _draw.y = 0;
                    _oldx = evt.stageX;
                    _oldy = evt.stageY;

                    if( _maxWidth <  cast(- _draw.x) + nme.Lib.current.stage.stageWidth){
                        _maxWidth = cast( - _draw.x) + nme.Lib.current.stage.stageWidth;
                    }
                    if( _maxHeight < cast(- _draw.y)+ nme.Lib.current.stage.stageHeight){
                        _maxHeight =  cast(- _draw.y)+ nme.Lib.current.stage.stageHeight;
                    }

                }
                else{
                    trace("out range!");
                }

            }
            else {
                //trace("drawing: "+ evt.stageX + " "+ evt.stageY);

                var x:Int = cast (evt.stageX - _draw.x);
                var y:Int = cast (evt.stageY - _draw.y);

                //_draw.graphics.lineTo(x, y);

                x1 = x2; y1 = y2;
                x2 = x3; y2 = y3;
                x3 = x; y3 = y;
                var cx = (x2 - x1)/4+x2;
                var cy = (y2 - y1)/4+y2;
                _draw.graphics.curveTo(cx, cy, x3, y3);

                /*
                var cx2 = (x3 - x4)/4+x3;
                var cy2 = (y3 - y4)/4+y3;
                _draw.graphics.cubicCurveTo(cx, cy, cx2, cy2, x3, y3);
                */

                //x4 = x; y4 = y;

                if (_dispatchCallback != null) storePoint( x, y);
            }
        }
    }

    public function eraseDrawing( ):Void{
        if ( _bm != null && _bm.parent != null ){
            _bm.parent.removeChild( _bm);
        }
        //#if flash
        //_bmd.fillRect( _bmd.rect,0);
        //#else
        //_bmd.clear( 0x0);
        //#end
        _draw.graphics.clear();
        _maxWidth =  nme.Lib.current.stage.stageWidth;
        _maxHeight =  nme.Lib.current.stage.stageHeight;
        _bmd = new BitmapData( _maxWidth, _maxHeight, true, 0);
        _rect = new Rectangle( 0, 0, _maxWidth, _maxHeight);
    }
    public function toggleFixed( ):Void{
        if( _isDown && _isFixed ){
            _draw.graphics.moveTo(_oldx-_draw.x, _oldy-_draw.y);
        }
        _isFixed = !_isFixed;
    }


    public function onMouseUp(evt:MouseEvent){ 
        if ( isAnimating()  ) return;
        if(  (evt.stageY - _downy) <50 && (evt.stageY - _downy ) > -50 &&  (evt.stageX - _downx) <50 && (evt.stageX - _downx ) > -50 ){
            for ( i in _instancesByDisplayOrder){
                if( i.hitTestPoint(evt.stageX, evt.stageY)){
                    i.onMouseClick();
                }
            }
        }
        var x:Float = evt.stageX, y:Float = evt.stageY;
        //#if flash
        if ( evt.stageX < 0 ){ x = 0; }else x = evt.stageX;
        if ( evt.stageY < 0 ){ y = 0; }else y = evt.stageY;
        if ( evt.stageX > nme.Lib.current.stage.stageWidth ){ x = nme.Lib.current.stage.stageWidth; }else x = evt.stageX;
        if ( evt.stageY > nme.Lib.current.stage.stageHeight){ y = nme.Lib.current.stage.stageHeight; }else y = evt.stageY;
        //#end

        if ( _isDown){
            if ( _isFixed  ){
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
            sina.login( false, null);
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

            _pressTime = 0;
            _releaseTime = 0;
        }
    }

    public function cacheBitmapData():Void{
        var tx = _draw.x;
        var ty = _draw.y;
        _draw.x = 0;
        _draw.y = 0;
        //trace("end drawing: "+ _maxWidth+ " "+ _maxHeight+" " + tx+" "+ty);
        _rect.height = _maxHeight;
        _rect.width = _maxWidth;
        if ( _maxWidth > _bmd.width || _maxHeight > _bmd.height){
            _bmd = new BitmapData( _maxWidth, _maxHeight, true, 0);
        }
        _bmd.draw(_draw, _rect);
        if( _bm!=null && _bm.parent != null ) {
            _bm.parent.removeChild( _bm);
        }
        _bm = new Bitmap(_bmd);
        _draw.addChild(_bm);
        _draw.graphics.clear();
        _draw.x = tx;
        _draw.y = ty;
        trace("clear once");
    }

    public function returnCallback( evt:MouseEvent) :Void{
        cacheBitmapData();
        if ( _returnCallback != null ){
            _returnCallback();
        }
        hideListDialog();
    }
}
