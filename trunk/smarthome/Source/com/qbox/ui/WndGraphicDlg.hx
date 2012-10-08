package com.qbox.ui;

import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.network.NetworkMgr;
import com.eclecticdesignstudio.motion.actuators.GenericActuator;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;
import base.ui.CommDialog;
import base.ui.CommDialogMgr;

import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Wnd;
import com.qbox.logic.WndMgr;
import com.qbox.logic.Channel;
import com.qbox.logic.Ring;

class WndGraphicDlg extends CommDialog{

    public var _downx:Float;
    public var _downy:Float;
    public var _isDown:Bool;


    public var _wnd:Wnd;
    public var _virtualWnd:Sprite;

    //public var _channel:Channel;
    //public var _ring:Ring;

    var _redrawW:Float;
    var _redrawH:Float;

    public function new ( mgr:CommDialogMgr ){
        super( mgr);

        _virtualWnd = new Sprite();
        addChild(_virtualWnd);
    }

    override function show (){
        //trace("test");
        return super.show();
    }

    public function shiftLeftUpWnd( isMax:Bool = true){
        if ( isMax){
            var rx = _wnd._virtualWidth + _wnd._virtualX;
            var dy = _wnd._virtualHeight + _wnd._virtualY;

            x=_wnd._virtualX = ScreenMgr.getInst()._virtualX;
            y=_wnd._virtualY = ScreenMgr.getInst()._virtualY;

            var w = _wnd._virtualWidth = rx -  _wnd._virtualX;
            var h = _wnd._virtualHeight = dy - _wnd._virtualY;

            redrawWnd(w,h);
            resizeWnd(w,h);
        }else{
        }
    }

    public function shiftRightDownWnd( isMax:Bool = true){
        if ( isMax){
            var w = _wnd._virtualWidth = ScreenMgr.getInst()._virtualWidth +ScreenMgr.getInst()._virtualX -  _wnd._virtualX;
            var h = _wnd._virtualHeight = ScreenMgr.getInst()._virtualHeight +ScreenMgr.getInst()._virtualY - _wnd._virtualY;

            redrawWnd(w,h);
            resizeWnd(w,h);
        }else{
        }
    }

    function redrawWnd( w:Float, h:Float){
        _redrawW = w;
        _redrawH = h;
        _virtualWnd.graphics.clear();
        _virtualWnd.graphics.lineStyle( 1, 0x121212, 1);
        _virtualWnd.graphics.beginFill(0xFFFFFF, 1);
        _virtualWnd.graphics.drawRect( 0,0, _redrawW, _redrawH);
        _virtualWnd.graphics.beginFill(0x808080, 1);
        _virtualWnd.graphics.drawRect( _redrawW-10,_redrawH-10, 10, 10);
        _virtualWnd.graphics.beginFill(0x808080, 1);
        _virtualWnd.graphics.drawRect( _redrawW-10,0, 10, 10);
        _virtualWnd.graphics.beginFill(0x808080, 1);
        _virtualWnd.graphics.drawRect( 0,0, 10, 10);
    }

    public function resizeWnd( w:Int, h:Int){
        //removeChild(_virtualWnd);
        //_virtualWnd = new Sprite();
        _wnd.resize( w,h);
        redrawWnd(w,h);
        //addChild(_virtualWnd);
    }

    public function resurrectWnd(wnd:Wnd){
        this.x = wnd._virtualX;
        this.y = wnd._virtualY;
        redrawWnd( wnd._virtualWidth, wnd._virtualHeight);
        _wnd = wnd;
    }

    public function openWnd( x:Int, y:Int, w:Int, h:Int, channel:Channel, ring:Ring){
        _wnd = WndMgr.getInst().createWnd();
        _wnd.open( x,y,w,h, channel, ring);
        redrawWnd(w,h);
        this.x = x;
        this.y = y;
        //_channel = channel;
        //_ring = ring;
    }

    public function closeWnd( ){
        _wnd.close();
        _virtualWnd.graphics.clear();
        removeChild(_virtualWnd);
        _virtualWnd = null;
    }

}

