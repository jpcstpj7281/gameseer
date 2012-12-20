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

    var _isPossessd:Bool;

    public function new ( mgr:CommDialogMgr ){
        super( mgr);

        _virtualWnd = new Sprite();
        addChild(_virtualWnd);
        _ax = _ay = _aw = _ay = 0;

    }

    public function switchSelect(){
        _wnd._isSelected = !_wnd._isSelected;
        redrawWnd(_redrawW, _redrawH);
    }

    override function show (){
        //trace("test");
        return super.show();
    }


    public function shiftLeftUpWnd( isMax:Bool = true){
        if (_isPossessd ) return false;
        if ( isMax){
            //calculate whether is this width already left up max of current screen;
            var px = this.x - ScreenMgr.getInst()._virtualX;
            var py = this.y - ScreenMgr.getInst()._virtualY;
            var totalcol = ScreenMgr.getInst()._col;
            var totalrow = ScreenMgr.getInst()._row;
            var vw = ScreenMgr.getInst()._virtualWidth/totalcol;
            var vh = ScreenMgr.getInst()._virtualHeight/totalrow;
            var minCol:Float = ScreenMgr.getInst()._virtualX;
            var minRow:Float = ScreenMgr.getInst()._virtualY;

            for ( i in 0...totalcol){
                var cw = vw * (totalcol - i-1) ;
                if ( px > cw){
                    minCol = cw;
                    break;
                }
            }
            for ( i in 0...totalrow){
                var ch = vh * (totalrow - i -1);
                if ( py > ch){
                    minRow= ch;
                    break;
                }
            }

            var rx = _wnd._virtualWidth + _wnd._virtualX;
            var dy = _wnd._virtualHeight + _wnd._virtualY;

            this.x=_wnd._virtualX = ScreenMgr.getInst()._virtualX + minCol;
            this.y=_wnd._virtualY = ScreenMgr.getInst()._virtualY + minRow;

            _wnd._virtualWidth =  rx -  _wnd._virtualX;
            _wnd._virtualHeight =  dy - _wnd._virtualY;

            return resizeWnd(_wnd._virtualWidth,_wnd._virtualHeight);
        }
        return false;
    }

    public function shiftRightDownWnd( isMax:Bool = true){
        if (_isPossessd ) return false;
        if ( isMax){

            //calculate whether is this width already right down max of current screen;
            var px = this.x + _redrawW;
            var py = this.y + _redrawH;
            var totalcol = ScreenMgr.getInst()._col;
            var totalrow = ScreenMgr.getInst()._row;
            var vw = ScreenMgr.getInst()._virtualWidth/totalcol;
            var vh = ScreenMgr.getInst()._virtualHeight/totalrow;
            var maxCol:Float = vw *totalcol;
            var maxRow:Float = vh *totalrow;

            for ( i in 0...totalcol){
                var cw = vw * (i+1) ;
                if ( px < cw){
                    maxCol = cw;
                    break;
                }
            }
            for ( i in 0...totalrow){
                var ch = vh * (i+1);
                if ( py < ch){
                    maxRow= ch;
                    break;
                }
            }
            //trace(px);
            //trace(py);
            //trace( maxCol);
            //trace( maxRow);

            var w = maxCol - _wnd._virtualX;
            var h = maxRow - _wnd._virtualY;
            return resizeWnd(w,h);
        }
        return false;
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
        if ( _wnd._isSelected ) {
            _virtualWnd.graphics.beginFill(0x0000FF, 1);
        }
        else {
            _virtualWnd.graphics.beginFill(0x000050, 1);
        }
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
        if (_isPossessd ) return false;
        _isPossessd = true;

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

        _redrawW = w;
        _redrawH = h;
#if !neko
        _wnd.resize( w,h, cbDone);
#else
        cbDone();
#end
        return true;
    }

    public function resurrectWnd(wnd:Wnd){
        this.x = wnd._virtualX;
        this.y = wnd._virtualY;
        _wnd = wnd;
        redrawWnd( wnd._virtualWidth, wnd._virtualHeight);
    }

    public function moveWnd( x:Float, y:Float){
        if (_isPossessd ) return false;
        _isPossessd = true;

        var w:Float= _wnd._virtualWidth;
        var h:Float= _wnd._virtualHeight;
        var wx = ScreenMgr.getInst()._virtualX +ScreenMgr.getInst()._virtualWidth;
        var hy = ScreenMgr.getInst()._virtualY +ScreenMgr.getInst()._virtualHeight;
        if ( x < ScreenMgr.getInst()._virtualX){
            //_wnd._virtualWidth = w = w - (ScreenMgr.getInst()._virtualX - x);
            x = this.x = ScreenMgr.getInst()._virtualX;
        }else if ( x < wx ){
            if ( wx < x+w) {
                x = this.x = wx - w;
                //trace("Test");
            }else{
                this.x = x;
            }
        }else{
            return false;
        }
        if ( y < ScreenMgr.getInst()._virtualY){
            //_wnd._virtualHeight = h = h - (ScreenMgr.getInst()._virtualY - y);
            y = this.y = ScreenMgr.getInst()._virtualY;
        }else if ( y < hy) {
            if ( hy < y+h) {
                y = this.y = hy - h;
                //trace("Test");
            }else{
                this.y = y;
            }
        }else{
            return false;
        }
        _wnd.move( x, y, cbDone);
        _redrawW = w;
        _redrawH = h;
        return true;
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

    function cbDone():Void{ 
        _isPossessd = false; 
        redrawWnd(_redrawW,_redrawH);
    }

    public function openWnd( x:Float, y:Float, w:Float, h:Float, channel:Channel, ring:Ring){
        if (_isPossessd ) return false;
        _isPossessd = true;

        _wnd = WndMgr.getInst().createWnd();
        //calculate the wnd size in screen.
        var wx = ScreenMgr.getInst()._virtualX +ScreenMgr.getInst()._virtualWidth;
        var hy = ScreenMgr.getInst()._virtualY +ScreenMgr.getInst()._virtualHeight;
        if ( x < ScreenMgr.getInst()._virtualX){
            _wnd._virtualWidth = w = w - (ScreenMgr.getInst()._virtualX - x);
            this.x = ScreenMgr.getInst()._virtualX;
        }else if ( x < wx ){
            this.x = x;
            if ( x+w > wx) _wnd._virtualWidth = w = wx - x;
        }else {
            WndMgr.getInst().removeWnd(_wnd);
            return false;
        }
        if ( y < ScreenMgr.getInst()._virtualY){
            _wnd._virtualHeight = h = h - (ScreenMgr.getInst()._virtualY - y);
            this.y = ScreenMgr.getInst()._virtualY;
        }else if ( y < hy) {
            this.y = y;
            if ( y+h > hy) _wnd._virtualHeight = h = hy - y;
        }else {
            WndMgr.getInst().removeWnd(_wnd);
            return false;
        }

        _redrawW = w;
        _redrawH = h;
        _wnd.open( x,y,w,h, channel, ring, cbDone);

        return true;
    }

    function cbCloseWnd():Void{}
    public function closeWnd( ){
        _wnd.close(cbCloseWnd);
        _virtualWnd.graphics.clear();
        removeChild(_virtualWnd);
        _virtualWnd = null;
    }

}
