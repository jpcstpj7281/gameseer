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
    var _ax:Float;
    var _ay:Float;
    var _aw:Float;
    var _ah:Float;

    public function new ( mgr:CommDialogMgr ){
        super( mgr);

        _virtualWnd = new Sprite();
        addChild(_virtualWnd);
        _ax = _ay = _aw = _ay = 0;
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

            var w =  rx -  _wnd._virtualX;
            var h =  dy - _wnd._virtualY;

            resizeWnd(w,h);
            //redrawWnd(w,h);
        }else{
        }
    }

    public function shiftRightDownWnd( isMax:Bool = true){
        if ( isMax){
            var w =  ScreenMgr.getInst()._virtualWidth +ScreenMgr.getInst()._virtualX -  _wnd._virtualX;
            var h =  ScreenMgr.getInst()._virtualHeight +ScreenMgr.getInst()._virtualY - _wnd._virtualY;

            //redrawWnd(w,h);
            resizeWnd(w,h);
        }else{
        }
    }

    function redrawWnd( w:Float, h:Float){
        _redrawW = w;
        _redrawH = h;
        _ax = _wnd._virtualAreaX;
        _ay = _wnd._virtualAreaY;
        _aw = _wnd._virtualAreaW;
        _ah = _wnd._virtualAreaH;

        _virtualWnd.graphics.clear();
        _virtualWnd.graphics.lineStyle( 1, 0x121212, 1);
        //window
        _virtualWnd.graphics.beginFill(0xFFFFFF, 1);
        _virtualWnd.graphics.drawRect( 0,0, _redrawW, _redrawH);

        if ( _aw > 0 && _ah > 0 ){
            //area
            _virtualWnd.graphics.beginFill(0x00FF00, 1);
            _virtualWnd.graphics.drawRect( _ax,_ay, _aw, _ah);
        }

        //bar
        _virtualWnd.graphics.beginFill(0x000080, 1);
        _virtualWnd.graphics.drawRect( 10,0, _redrawW - 20, 10);

        //close
        _virtualWnd.graphics.beginFill(0x808080, 1);
        _virtualWnd.graphics.drawRect( _redrawW-10,_redrawH-10, 10, 10);

        //right down resize
        _virtualWnd.graphics.beginFill(0x808080, 1);
        _virtualWnd.graphics.drawRect( _redrawW-10,0, 10, 10);

        //left up resize
        _virtualWnd.graphics.beginFill(0x808080, 1);
        _virtualWnd.graphics.drawRect( 0,0, 10, 10);
    }

    public function resizeWnd( w:Float, h:Float){

        if ( ScreenMgr.getInst()._virtualWidth +ScreenMgr.getInst()._virtualX -  this.x - w < 0){
            w = ScreenMgr.getInst()._virtualWidth + ScreenMgr.getInst()._virtualX - this.x;
        }
        if ( ScreenMgr.getInst()._virtualHeight +ScreenMgr.getInst()._virtualY - this.y - h < 0 ){
            h = ScreenMgr.getInst()._virtualHeight + ScreenMgr.getInst()._virtualY - this.y;
        }

        var pw = w / _wnd._virtualWidth;
        var ph = h / _wnd._virtualHeight;
        //trace(_wnd._virtualAreaW);
        //trace(_wnd._virtualAreaH);
        _wnd._virtualAreaX = _wnd._virtualAreaX * pw;
        _wnd._virtualAreaY = _wnd._virtualAreaY * ph;
        _wnd._virtualAreaW = _wnd._virtualAreaW * pw;
        _wnd._virtualAreaH = _wnd._virtualAreaH * ph;

        //trace(_wnd._virtualAreaW);
        //trace(_wnd._virtualAreaH);

        _wnd.resize( w,h);
        redrawWnd(w,h);
    }

    public function resurrectWnd(wnd:Wnd){
        this.x = wnd._virtualX;
        this.y = wnd._virtualY;
        _wnd = wnd;
        redrawWnd( wnd._virtualWidth, wnd._virtualHeight);
    }

    public function moveWnd( x:Int, y:Int){
        var w:Float= _wnd._virtualWidth;
        var h:Float= _wnd._virtualHeight;
        var wx = ScreenMgr.getInst()._virtualX +ScreenMgr.getInst()._virtualWidth;
        var hy = ScreenMgr.getInst()._virtualY +ScreenMgr.getInst()._virtualHeight;
        if ( x < ScreenMgr.getInst()._virtualX){
            _wnd._virtualWidth = w = w - (ScreenMgr.getInst()._virtualX - x);
            this.x = ScreenMgr.getInst()._virtualX;
        }else if ( x < wx ){
            this.x = x;
            if ( x+w > wx) _wnd._virtualWidth = w = wx - x;
        }else{
            return;
        }
        if ( y < ScreenMgr.getInst()._virtualY){
            _wnd._virtualHeight = h = h - (ScreenMgr.getInst()._virtualY - y);
            this.y = ScreenMgr.getInst()._virtualY;
        }else if ( y < hy) {
            this.y = y;
            if ( y+h > hy) _wnd._virtualHeight = h = hy - y;
        }else{
            return;
        }
        redrawWnd(w,h);
        _wnd.move( cast x, cast y);
    }

    public function moveArea( x:Int, y:Int){
        var ax:Float = 0;
        var ay:Float = 0;
        var aw = _wnd._virtualAreaW;
        var ah = _wnd._virtualAreaH;

        if ( x < this.x){
            ax = 0;
        }
        else{
            if ( x + aw > _wnd._virtualWidth + this.x){
                ax = _wnd._virtualWidth - aw;
            }
            else{
                ax = x - this.x;
            }
        }
        if ( y < this.y){
            ay = 0;
        }else{
            if ( y + ah > _wnd._virtualHeight + this.y){
                ay = _wnd._virtualHeight - ah;
            }
            else{
                ay = y - this.y;
            }
        }


        if ( _wnd.setVirtualArea( ax, ay, aw, ah) ){
            redrawWnd(_redrawW, _redrawH);
            return true;
        }
        return false;
    }

    public function createArea( ix:Float, iy:Float, iw:Float,ih:Float){
        var ax:Float = ix - this.x;
        var ay:Float = iy - this.y;
        var aw:Float = iw;
        var ah:Float = ih;
        var wx:Float = _wnd._virtualWidth + this.x;
        var wy:Float = _wnd._virtualHeight + this.y;
        if ( ix + iw > wx) {
            aw = _wnd._virtualWidth - ax;
        }

        if ( iy + ih > wy){
            ah = _wnd._virtualHeight - ay;
        }

        if ( _wnd.setVirtualArea( ax, ay, aw, ah) ){
            redrawWnd(_redrawW, _redrawH);
            return true;
        }
        return false;
    }

    public function openWnd( x:Int, y:Int, w:Int, h:Int, channel:Channel, ring:Ring){
        _wnd = WndMgr.getInst().createWnd();
        _wnd.open( x,y,w,h, channel, ring);
        var wx = ScreenMgr.getInst()._virtualX +ScreenMgr.getInst()._virtualWidth;
        var hy = ScreenMgr.getInst()._virtualY +ScreenMgr.getInst()._virtualHeight;
        if ( x < ScreenMgr.getInst()._virtualX){
            _wnd._virtualWidth = w = w - (ScreenMgr.getInst()._virtualX - x);
            this.x = ScreenMgr.getInst()._virtualX;
        }else if ( x < wx ){
            this.x = x;
            if ( x+w > wx) _wnd._virtualWidth = w = wx - x;
        }else{
            return;
        }
        if ( y < ScreenMgr.getInst()._virtualY){
            _wnd._virtualHeight = h = h - (ScreenMgr.getInst()._virtualY - y);
            this.y = ScreenMgr.getInst()._virtualY;
        }else if ( y < hy) {
            this.y = y;
            if ( y+h > hy) _wnd._virtualHeight = h = hy - y;
        }else{
            return;
        }
        redrawWnd(w,h);
        //trace(x);
        //trace(y);
    }

    public function closeWnd( ){
        _wnd.close();
        _virtualWnd.graphics.clear();
        removeChild(_virtualWnd);
        _virtualWnd = null;
    }

}
