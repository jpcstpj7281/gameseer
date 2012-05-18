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
import nme.display.BitmapInt32;

import haxe.io.Bytes;
import haxe.io.BytesBuffer;

import haxe.Timer;
import base.ui.ReturnDlg;

class DrawingDlgMgr extends CommDialogMgr{

    var _downy:Float;
    var _downx:Float;
    var _movey:Float;
    var _movex:Float;

    var _oldx:Float;
    var _oldy:Float;

    var _isDown:Bool;

    var _graphic:Sprite;
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

    public var _color:Int;
    public var _linePixel:Int;
    public var _alpha:Float;

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
        _graphic = new Sprite();
        _graphic.addChild(_draw);
        _view.addChild(_graphic);
        droppoint.addChild(_view);
        super( _view);
        //_draw.cacheAsBitmap = true;
        _draw.cacheAsBitmap = false;

        _color = 0xf75544;
        _linePixel = 1;
        _alpha = 1.0;

        _maxWidth =  nme.Lib.current.stage.stageWidth;
        _maxHeight =  nme.Lib.current.stage.stageHeight;
        _bmd = new BitmapData( _maxWidth, _maxHeight, true, #if neko {rgb:0, a:0} #else 0 #end );
        _rect = new Rectangle( 0, 0, _maxWidth, _maxHeight);

        _oldx = _graphic.x;
        _oldy = _graphic.y;
        _isDown = false;
        _linesArr = new Array<Bytes>();
        _lines = new BytesBuffer();

        new ReturnDlg( this , returnCallback);
        new UploadImgDlg(this);
        new DrawEditDlg(this);
        new EraseDlg(this);
        new ColorPanelDlg(this);
        new SelectAlphaDlg(this);
        new SelectLineDlg(this);
        new LineThickScrollDlg(this);
        new AlphaScrollDlg(this);
        _graphic.visible = false;
        _isFixed = true;
    }

    public override function showListDialog():Void{
        _isDown = false;
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);
        nme.Lib.current.stage.addEventListener( Event.ENTER_FRAME , onEnterFrame);
        _graphic.visible = true;
        cacheBitmapData();
        //super.showListDialog();
        _isFixed = true;
        for ( i in _instancesByDisplayOrder){
            if ( Std.is( i, DrawEditDlg) == false  ){
                i.hide();
            }else{
                i.show();
            }
        }
    }

    public override function hideListDialog( ):Void{
        _isDown = false;
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_UP, onMouseUp);
        nme.Lib.current.stage.removeEventListener( Event.ENTER_FRAME, onEnterFrame);
        _graphic.visible = false;
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
        _graphic= null;
        _rect = null;
        _linesArr = null;
        _lines = null;
    }

    inline public function draw( data:Array<Bytes> ){
        _draw.graphics.lineStyle( _linePixel, _color, _alpha);

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
            if(  i.alpha == 1 && i.hitTestPoint(evt.stageX, evt.stageY)){
                if ( Std.is(i, LineThickScrollDlg) ){
                    var lt:LineThickScrollDlg = cast i;
                    lt.onMouseDown(evt);
                }
                if ( Std.is(i, AlphaScrollDlg) ){
                    var lt:AlphaScrollDlg = cast i;
                    lt.onMouseDown(evt);
                }
                if ( Std.is(i, ColorPanelDlg) ){
                    var lt:ColorPanelDlg= cast i;
                    lt.onMouseDown(evt);
                }
                return;
            }
        }

        _movex= 0;
        _movey= 0;
        _oldx = evt.stageX;
        _oldy = evt.stageY;

        if( _isFixed ){
            //_draw.graphics.lineStyle( _linePixel, _color, _alpha);
            _draw.graphics.lineStyle( _linePixel, _color, _alpha);
            //_draw.graphics.beginFill(0xf75544, 0.75);

            var x:Int = cast (evt.stageX - _graphic.x);
            var y:Int = cast (evt.stageY - _graphic.y);
            _draw.graphics.moveTo(x, y);

            x1 = x; y1 = y;
            x2 = x1; y2 = y1;
            x3 = x2; y3 = y2;
            //x4 = x3; y4 = y3;

            if ( _dispatchCallback != null){ storePoint( x, y); }

            var mw:Int = nme.Lib.current.stage.stageWidth - Std.int(_graphic.x);
            var mh:Int = nme.Lib.current.stage.stageHeight- Std.int(_graphic.y);
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
        for ( i in _instancesByDisplayOrder){
            if(  i.alpha == 1 && i.hitTestPoint(evt.stageX, evt.stageY)){
                if ( Std.is(i, LineThickScrollDlg) ){
                    var lt:LineThickScrollDlg = cast i;
                    lt.onMouseMove( evt);
                }
                if ( Std.is(i, AlphaScrollDlg) ){
                    var lt:AlphaScrollDlg = cast i;
                    lt.onMouseMove( evt);
                }
                if ( Std.is(i, ColorPanelDlg) ){
                    var lt:ColorPanelDlg= cast i;
                    lt.onMouseMove(evt);
                    continue;
                }
                return;
            }
        }
        if ( _isDown){
#if flash
            if( evt.stageX < 0 || evt.stageX > nme.Lib.current.stage.stageWidth || evt.stageY < 0 || evt.stageY > nme.Lib.current.stage.stageHeight ) {
                onMouseUp(evt);
                return;
            }
#end
            if ( !_isFixed){
                if ( _graphic.x >= -RightEdge || _graphic.y >= -BottomEdge){
                    _graphic.x += evt.stageX - _oldx;
                    if (_graphic.x <-RightEdge) _graphic.x = -RightEdge;
                    else if (_graphic.x >0) _graphic.x = 0;
                    _graphic.y += evt.stageY - _oldy;
                    if (_graphic.y <-BottomEdge) _graphic.y = -BottomEdge;
                    else if (_graphic.y > 0) _graphic.y = 0;
                    _oldx = evt.stageX;
                    _oldy = evt.stageY;

                    if( _maxWidth <  cast(- _graphic.x) + nme.Lib.current.stage.stageWidth){
                        _maxWidth = cast( - _graphic.x) + nme.Lib.current.stage.stageWidth;
                    }
                    if( _maxHeight < cast(- _graphic.y)+ nme.Lib.current.stage.stageHeight){
                        _maxHeight =  cast(- _graphic.y)+ nme.Lib.current.stage.stageHeight;
                    }

                }
                else{
                    trace("out range!");
                }

            }
            else {
                //trace("drawing: "+ evt.stageX + " "+ evt.stageY);

                var x:Int = cast (evt.stageX - _graphic.x);
                var y:Int = cast (evt.stageY - _graphic.y);

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
        _bmd = new BitmapData( _maxWidth, _maxHeight, true,#if neko {rgb:0, a:0} #else 0 #end ) ;
        _rect = new Rectangle( 0, 0, _maxWidth, _maxHeight);
    }
    public function toggleFixed( ):Void{
        if( _isFixed ){
            //_draw.graphics.moveTo( _oldx - _graphic.x, _oldy - _graphic.y);
            for ( i in _instancesByDisplayOrder){
                if ( Std.is( i, DrawEditDlg) == false  ){
                    i.show();
                }
            }
        }
        else {
            for ( i in _instancesByDisplayOrder){
                if ( Std.is( i, DrawEditDlg) == false  ){
                    i.hide();
                }
            }
        }
        _isFixed = !_isFixed;
    }

    public function onMouseUp(evt:MouseEvent){ 
        if ( isAnimating()  ) return;
        for ( i in _instancesByDisplayOrder){
            if( i.alpha == 1 && i.hitTestPoint(evt.stageX, evt.stageY)){
                if ( Std.is(i, LineThickScrollDlg) ){
                    var lt:LineThickScrollDlg = cast i;
                    lt.onMouseUp( evt);
                }
                if ( Std.is(i, AlphaScrollDlg) ){
                    var lt:AlphaScrollDlg = cast i;
                    lt.onMouseUp( evt);
                }
                if ( Std.is(i, ColorPanelDlg) ){
                    var lt:ColorPanelDlg= cast i;
                    lt.onMouseUp(evt);
                }
                if(  (evt.stageY - _downy) <50 && (evt.stageY - _downy ) > -50 &&  (evt.stageX - _downx) <50 && (evt.stageX - _downx ) > -50 ){
                    i.onMouseClick();
                }
            }
        }
        //for ( i in _instancesByDisplayOrder){
        //if( i.alpha == 1 && i.hitTestPoint(evt.stageX, evt.stageY)){
        //i.onMouseClick();
        //return;
        //}
        //}
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

    public function getImgBytes():Bytes{
        if( _pressTime > 0 ) cacheBitmapData();
        return base.common.Tools.converToPNGBytes( _bmd, _maxWidth, _maxHeight);
    }
    public function uploadImg():Void{
        var bytes  = getImgBytes();

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
        var tx = _graphic.x;
        var ty = _graphic.y;
        _graphic.x = 0;
        _graphic.y = 0;
        //trace("end drawing: "+ _maxWidth+ " "+ _maxHeight+" " + tx+" "+ty);
        _rect.height = _maxHeight;
        _rect.width = _maxWidth;
        if ( _maxWidth > _bmd.width || _maxHeight > _bmd.height){
            _bmd = new BitmapData( _maxWidth, _maxHeight, true, #if neko {rgb:0, a:0} #else 0 #end );
        }
        _bmd.draw(_graphic, _rect);
        if( _bm!=null && _bm.parent != null ) {
            _bm.parent.removeChild( _bm);
        }
        _bm = new Bitmap(_bmd);

        _graphic.addChild(_bm);
        _graphic.setChildIndex(_bm, 0);
        _draw.graphics.clear();
        _graphic.x = tx;
        _graphic.y = ty;
        trace("clear once");
    }

    public function returnCallback( ) :Void{
        //trace( _returnCallback);
        cacheBitmapData();
        //trace( _returnCallback);
        if ( _returnCallback != null ){
            _returnCallback();
        }
        //hideListDialog();
    }
}
