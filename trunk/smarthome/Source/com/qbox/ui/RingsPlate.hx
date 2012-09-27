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
import com.qbox.logic.WndMgr;

import com.pictionary.ui.DrawingDlgMgr;


class RingsPlate extends CommDialog{

    var _screens:Sprite;
    var _wnds:Sprite;
    var _isDown:Bool;
    var _downx:Int;
    var _downy:Int;
    var _movex:Int;
    var _movey:Int;

    var _RingWidth:Float;
    var _RingHeight:Float;

    public function new ( dm:CommDialogMgr ){
        super(dm);

        _screens = new Sprite();
        _wnds = new Sprite();
        addChild(_screens);
        addChild(_wnds);
        _isDown = false;
        //_isClose= false;
        _downx = 0;
        _downy = 0;
    }

    function createScreens(){
        var col = ScreenMgr.getInst()._col;
        var row = ScreenMgr.getInst()._row;
        if ( col == 0 && row == 0 ) {
            return;
        }
        var sw = ScreenMgr.getInst()._virtualWidth/col;
        var sh = ScreenMgr.getInst()._virtualHeight/row;


        _RingWidth = sw;
        _RingHeight= sh;


        removeChild(_screens);
        _screens = new Sprite();
        addChildAt( _screens, 0);
        for ( i in ScreenMgr.getInst()._screens){
            var s = new Sprite();
            i._virtualHeight = cast _RingHeight;
            i._virtualWidth = cast _RingWidth;
            s.graphics.lineStyle( 1, 0x000000, 1);
            s.graphics.moveTo( i._col * _RingWidth, i._row * _RingHeight );
            s.graphics.lineTo( (i._col+1) * _RingWidth, i._row * _RingHeight );
            s.graphics.lineTo( (i._col+1) * _RingWidth, (i._row+1) * _RingHeight );
            s.graphics.lineTo( i._col * _RingWidth, (i._row+1) * _RingHeight );
            s.graphics.beginFill(0x888888);
            //s.graphics.drawRect( (i._col+0.5) * _RingWidth, i._row * _RingHeight, _RingWidth*0.5, _RingHeight);
            s.graphics.drawRect( (i._col+0.5) * _RingWidth, i._row * _RingHeight, _RingWidth*0.5, _RingHeight);
            _screens.addChild(s);
        }

        _screens.x = Math.round( (width - _screens.width) /2);
        ScreenMgr.getInst()._virtualX= cast _screens.x;
        ScreenMgr.getInst()._virtualY= cast _screens.y;

    }

    function createWnds(){
        var ms = cast(_mgr, ListDialogMgr)._movableInstances;
        if ( ms.length > 0 ){
            var m = ms[0];
            var p = m.parent;
            var arr = new Array<WndGraphicDlg>();
            for ( i in 0...p.numChildren){
                var w = p.getChildAt( p.numChildren - i -1 );
                if ( Std.is(w, WndGraphicDlg) ){
                    var wgd:WndGraphicDlg = cast( w, WndGraphicDlg);
                    arr.push(wgd);
                }
            }
            for ( i in arr){
                i.clear();
            }
        }
        for ( i in WndMgr.getInst()._wnds){
            trace("create wnd");
            var win = new WndGraphicDlg(_mgr);
            win.resurrectWnd(i);
            win.show();
        }
    }

    override function show(){
        trace("Test");
        createScreens();
        createWnds();

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
        }
        if ( _screens.hitTestPoint( evt.stageX, evt.stageY)){
            //screen plate has been clicked.
            _isDown = true;
            _downx = cast evt.stageX;
            _downy = cast evt.stageY;
        }
    }
    function onThisMouseMove( evt:MouseEvent ):Void{ 
        if ( _isDown){
        }
    }
    function onThisMouseUp( evt:MouseEvent ):Void{ 
        if ( _isDown ){
        }
        _isDown = false;
        _downx = 0;
        _downy = 0;
        //_isClose = false;
    }
}
