
package com.qbox.ui;

import base.ui.FixedDlg;
import nme.events.MouseEvent;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.CommDialog;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Wnd;
import com.qbox.logic.ChannelMgr;
import com.qbox.logic.Channel;

import com.pictionary.ui.DrawingDlgMgr;


class ScreenPlate extends CommDialog{

    var _screens:Sprite;
    var _wnds:Sprite;
    var _isDown:Bool;
    var _downx:Int;
    var _downy:Int;
    var _movex:Int;
    var _movey:Int;
    var _isMoving:Bool;
    var _isResize:Bool;
    //var _isClose:Bool;
    var _movingWnd:WndGraphicDlg;

    var _screenWidth:Float;
    var _screenHeight:Float;

    public function new ( dm:CommDialogMgr ){
        super(dm);

        _screens = new Sprite();
        _wnds = new Sprite();
        addChild(_screens);
        addChild(_wnds);
        _isDown = false;
        _isMoving = false;
        _isResize= false;
        //_isClose= false;
        _downx = 0;
        _downy = 0;
    }


    override function show(){
        var col = ScreenMgr.getInst()._col;
        var row = ScreenMgr.getInst()._row;
        if ( col != 0 && row != 0 ) {

            var width:Int = nme.Lib.current.stage.stageWidth ;
            var height:Int = nme.Lib.current.stage.stageHeight - 100;

            _screenWidth = width/col;
            _screenHeight = height/row;
            if ( _screenHeight > _screenWidth *6/9){
                _screenHeight = _screenWidth *6/9;
            }
            if ( _screenWidth> _screenHeight *9/6){
                _screenWidth= _screenHeight *9/6;
            }

            //trace(_screenHeight);
            //trace(_screenWidth);
            removeChild(_screens);
            _screens = new Sprite();
            addChildAt( _screens, 0);
            for ( i in ScreenMgr.getInst()._screens){
                var s = new Sprite();
                i._virtualHeight = cast _screenHeight;
                i._virtualWidth = cast _screenWidth;
                s.graphics.lineStyle( 1, 0x000000, 1);
                s.graphics.moveTo( i._col * _screenWidth, i._row * _screenHeight );
                s.graphics.lineTo( (i._col+1) * _screenWidth, i._row * _screenHeight );
                s.graphics.lineTo( (i._col+1) * _screenWidth, (i._row+1) * _screenHeight );
                s.graphics.lineTo( i._col * _screenWidth, (i._row+1) * _screenHeight );
                s.graphics.beginFill(0x888888);
                s.graphics.drawRect( i._col * _screenWidth, i._row * _screenHeight, _screenWidth, _screenHeight);
                _screens.addChild(s);
            }

            _screens.x = (width - _screens.width) /2;
        }

        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onThisMouseDown);
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onThisMouseMove);
        nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onThisMouseUp);

        return super.show();
    }
    override function hide(){
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_DOWN, onThisMouseDown);
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_MOVE, onThisMouseMove);
        nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_UP, onThisMouseUp);
        return super.hide();
    }

    function onThisMouseDown( evt:MouseEvent ):Void{
        var ms = cast(_mgr, ListDialogMgr)._movableInstances;
        if ( ms.length > 0 ){
            var m = ms[0];
            var p = m.parent;
            for ( i in 0...p.numChildren){
                var w = p.getChildAt( p.numChildren - i -1 );
                if ( Std.is(w, WndGraphicDlg) && w.hitTestPoint( evt.stageX, evt.stageY) ){
                    //p.setChildIndex(w, p.numChildren -1 );
                    _movingWnd = cast (w, WndGraphicDlg);
                    _movex = cast evt.stageX - w.x;
                    _movey = cast evt.stageY - w.y;
                    break;
                }
            }
        }
        if ( _screens.hitTestPoint( evt.stageX, evt.stageY)){
            _isDown = true;
            _isMoving = false;
            _downx = cast evt.stageX;
            _downy = cast evt.stageY;
        }
    }
    function onThisMouseMove( evt:MouseEvent ):Void{ 
        if ( _isDown){
            if ( _movingWnd != null){
                if (_isResize ||( evt.stageX > _movingWnd.x + _movingWnd.width -10 && evt.stageY > _movingWnd.y + _movingWnd.height -10 )){
                    //trace("_isResize");
                    _isResize = true;
                }else if (!_isResize && (evt.stageX - _downx > 5 || evt.stageY - _downy > 5 || evt.stageX - _downx < -5 || evt.stageY - _downy <-5)){
                    //trace("_isMoving");
                    _isMoving = true;
                }
            }
            if ( _screens.hitTestPoint( evt.stageX, evt.stageY)){
            }else{
                onThisMouseUp(evt);
            }
        }
    }
    function onThisMouseUp( evt:MouseEvent ):Void{ 
        if ( _isDown ){
            if ( _isMoving ){
                _movingWnd.x = evt.stageX - _movex;
                _movingWnd.y = evt.stageY - _movey;
                _movingWnd._wnd.move( cast _movingWnd.x, cast _movingWnd.y);
            }else if ( _isResize){
                var w:Int = cast _movingWnd.width + evt.stageX - _movingWnd.x - _movex;
                var h:Int = cast _movingWnd.height + evt.stageY - _movingWnd.y - _movey;
                _movingWnd.resizeWnd( w , h);
            }else{

                var upx = evt.stageX;
                var upy = evt.stageY;

                if (upx < _screens.x ) {
                    upx = _screens.x;
                }else if ( upx > (_screens.x +_screens.width)){
                    upx = _screens.x + _screens.width;
                }
                if (upy < _screens.y ) {
                    upy = _screens.y;
                }else if ( upy > (_screens.y +_screens.height)){
                    upy = _screens.y+_screens.height;
                }

                //_wnds.graphics.beginFill( 0x111111);
                //_wnds.graphics.drawRect( _downx, _downy, upx - _downx, upy - _downy);
                if ( upx - _downx > 90  && upy - _downy > 60 ) {
                    if ( ChannelMgr.getInst()._channels.length > 0){
                        var win = new WndGraphicDlg(_mgr);
                        win.openWnd( _downx, _downy, cast upx - _downx, cast upy - _downy, ChannelMgr.getInst()._channels[0]);
                        win.show();
                    }
                    else{
                        trace("channel not yet select.");
                    }
                }
                else if ( upx - _downx < 5  && upy - _downy <5 ) {
                    var ms = cast(_mgr, ListDialogMgr)._movableInstances;
                    if ( ms.length > 0 ){
                        var m = ms[0];
                        var p = m.parent;
                        for ( i in 0...p.numChildren){
                            var w = p.getChildAt( i );
                            if ( Std.is(w, WndGraphicDlg) && w.hitTestPoint( evt.stageX, evt.stageY) ){
                                p.setChildIndex(w, p.numChildren -1 );
                            }
                        }
                    }
                    if ( _movingWnd != null && evt.stageX > _movingWnd.x + _movingWnd.width -10 && evt.stageY < _movingWnd.y +10 ){
                        _movingWnd.closeWnd();
                        _movingWnd.parent.removeChild(_movingWnd);
                        cast(_mgr, ListDialogMgr)._movableInstances.remove(_movingWnd);
                    }
                }
            }
        }
        _isDown = false;
        _downx = 0;
        _downy = 0;
        _isMoving = false;
        _isResize= false;
        //_isClose = false;
        _movingWnd = null;
    }
}
