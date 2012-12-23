package com.qbox.ui;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;

import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Qbox;
import com.qbox.logic.Wnd;

class WndDlg extends CommDialog{

    var _wndtext:EmbedTextField;
    var _xt:EmbedTextField;
    var _yt:EmbedTextField;
    var _wt:EmbedTextField;
    var _ht:EmbedTextField;
    var _st:EmbedTextField;

    var _axt:EmbedTextField;
    var _ayt:EmbedTextField;
    var _awt:EmbedTextField;
    var _aht:EmbedTextField;
    var _ct:EmbedTextField;

    var _s:Sprite;

    var _wnd:Wnd;

    public function new ( dm:ListDialogMgr, c:Wnd){
        super(dm);
        _wnd = c;
        addChild( createElement());
    }

    public function cbDone(args):Void{
    }

    override function show(){
        if ( _s != null) {
            if (_wndtext!= null) _s.removeChild(_wndtext);
            if (_xt!= null)_s.removeChild(_xt);
            if (_yt!= null)_s.removeChild(_yt);
            if (_wt!= null)_s.removeChild(_wt);
            if (_ht!= null)_s.removeChild(_ht);
            if (_axt!= null)_s.removeChild(_axt);
            if (_ayt!= null)_s.removeChild(_ayt);
            if (_awt!= null)_s.removeChild(_awt);
            if (_aht!= null)_s.removeChild(_aht);
            if (_st!= null)_s.removeChild(_st);
            if (_ct!= null)_s.removeChild(_ct);

            _wndtext= new EmbedTextField();
            _wndtext.selectable = false;
#if !neko
            _wndtext.text = "窗口:";
#else
            _wndtext.text = "wnd:";
#end
            _wndtext.scaleX = 3;
            _wndtext.scaleY = 3;
            _wndtext.width = 50;
            _wndtext.height= 16;

            var offset = 550;
            _xt= new EmbedTextField();
            _xt.type = INPUT;
            _xt.setBorder(true);
            _xt.scaleX = 3;
            _xt.scaleY = 3;
            _xt.width = 24;
            _xt.height= 16;
            _xt.x = 110;

            _yt= new EmbedTextField();
            _yt.type = INPUT;
            _yt.setBorder(true);
            _yt.scaleX = 3;
            _yt.scaleY = 3;
            _yt.width = 24;
            _yt.height= 16;
            _yt.x = 190;

            _wt= new EmbedTextField();
            _wt.type = INPUT;
            _wt.setBorder(true);
            _wt.scaleX = 3;
            _wt.scaleY = 3;
            _wt.width = 24;
            _wt.height= 16;
            _wt.x = 270;

            _ht= new EmbedTextField();
            _ht.type = INPUT;
            _ht.setBorder(true);
            _ht.scaleX = 3;
            _ht.scaleY = 3;
            _ht.width = 24;
            _ht.height= 16;
            _ht.x = 350;

            _axt= new EmbedTextField();
            _axt.type = INPUT;
            _axt.setBorder(true);
            _axt.scaleX = 3;
            _axt.scaleY = 3;
            _axt.width = 24;
            _axt.height= 16;
            _axt.x = offset;

            _ayt= new EmbedTextField();
            _ayt.type = INPUT;
            _ayt.setBorder(true);
            _ayt.scaleX = 3;
            _ayt.scaleY = 3;
            _ayt.width = 24;
            _ayt.height= 16;
            _ayt.x = offset+80;

            _awt= new EmbedTextField();
            _awt.type = INPUT;
            _awt.setBorder(true);
            _awt.scaleX = 3;
            _awt.scaleY = 3;
            _awt.width = 24;
            _awt.height= 16;
            _awt.x = offset+160;

            _aht= new EmbedTextField();
            _aht.type = INPUT;
            _aht.setBorder(true);
            _aht.scaleX = 3;
            _aht.scaleY = 3;
            _aht.width = 24;
            _aht.height= 16;
            _aht.x = offset+240;


            _st= new EmbedTextField();
            _st.setBorder(true);
#if !neko
            _st.text = "更新";
#else
            _st.text = "update";
#end
            _st.selectable = false;
            _st.scaleX = 3;
            _st.scaleY = 3;
            _st.width = 30;
            _st.height= 16;
            _st.x = 430;
            _st.addEventListener( MouseEvent.CLICK, onUpdateBtnMouseClick);

            _ct= new EmbedTextField();
            _ct.setBorder(true);
#if !neko
            _ct.text = "更新";
#else
            _ct.text = "update";
#end
            _ct.selectable = false;
            _ct.scaleX = 3;
            _ct.scaleY = 3;
            _ct.width = 30;
            _ct.height= 16;
            _ct.x = offset+320;
            _ct.addEventListener( MouseEvent.CLICK, onUpdateAreaBtnMouseClick);

            var pw:Float = ScreenMgr.getInst()._resWidth/ScreenMgr.getInst()._virtualWidth;
            var ph:Float = ScreenMgr.getInst()._resHeight/ScreenMgr.getInst()._virtualHeight;
            var x = Math.round( (_wnd._virtualX - ScreenMgr.getInst()._virtualX) *pw);
            var y = Math.round( (_wnd._virtualY - ScreenMgr.getInst()._virtualY) *ph);
            var w = Math.round( _wnd._virtualWidth*pw);
            var h = Math.round( _wnd._virtualHeight*ph);
            var apw:Float = _wnd._channel._w / _wnd._virtualWidth;
            var aph:Float = _wnd._channel._h / _wnd._virtualHeight;
            var ax = Math.round(_wnd._virtualAreaX *apw );
            var ay = Math.round(_wnd._virtualAreaY *aph );
            var aw = Math.round(_wnd._virtualAreaW *apw);
            var ah = Math.round(_wnd._virtualAreaH *aph);
            _xt.text = ""+x;
            _yt.text = ""+y;
            _wt.text = ""+w;
            _ht.text = ""+h;
            _axt.text = ""+ax;
            _ayt.text = ""+ay;
            _awt.text = ""+aw;
            _aht.text = ""+ah;
            _s.addChild( _wndtext);
            _s.addChild( _xt);
            _s.addChild( _yt);
            _s.addChild( _wt);
            _s.addChild( _ht);
            _s.addChild( _axt);
            _s.addChild( _ayt);
            _s.addChild( _awt);
            _s.addChild( _aht);
            _s.addChild( _st);
            _s.addChild( _ct);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }

        return super.show();
    }

    override function hide(){
        if ( _s != null ) {
            if ( _wndtext!= null) {_s.removeChild(_wndtext);_wndtext= null;}
            if ( _xt!= null){ _s.removeChild(_xt);_xt= null;}
            if ( _yt!= null){ _s.removeChild(_yt);_yt= null;}
            if ( _wt!= null){ _s.removeChild(_wt);_wt= null;}
            if ( _ht!= null){ _s.removeChild(_ht);_ht= null;}
            if ( _axt!= null){ _s.removeChild(_axt);_axt= null;}
            if ( _ayt!= null){ _s.removeChild(_ayt);_ayt= null;}
            if ( _awt!= null){ _s.removeChild(_awt);_awt= null;}
            if ( _aht!= null){ _s.removeChild(_aht);_aht= null;}

            if ( _st!= null){ 
                _st.removeEventListener(  MouseEvent.CLICK, onUpdateBtnMouseClick);
                _s.removeChild(_st);
                _st= null;
            }
            if ( _ct!= null){ 
                _ct.removeEventListener(  MouseEvent.CLICK, onUpdateAreaBtnMouseClick);
                _s.removeChild(_ct);
                _ct= null;
            }
        }
        return super.hide();
    }
    public function createElement():Sprite{

        _s= new Sprite();
        return _s;
    }

    function onUpdateAreaBtnMouseClick( evt:MouseEvent){
        var ax = Math.round( Std.parseInt( _axt.text) );
        var ay = Math.round( Std.parseInt( _ayt.text) );
        var aw = Math.round( Std.parseInt( _awt.text) );
        var ah = Math.round( Std.parseInt( _aht.text) );
        if (ax >=_wnd._channel._w){ _axt.text = ""+(ax = _wnd._channel._w - 1); }
        if (ay >=_wnd._channel._h){ _ayt.text = ""+(ay = _wnd._channel._h - 1); }
        if (aw + ax >_wnd._channel._w){ _awt.text = ""+(aw = _wnd._channel._w - ax); }
        if (ah + ay >_wnd._channel._h){ _aht.text = ""+(ah = _wnd._channel._h - ay); }
        _wnd.setRealArea(ax, ay, aw, ah);
    }
    function onUpdateBtnMouseClick( evt:MouseEvent){
        var pw:Float = ScreenMgr.getInst()._resWidth/ScreenMgr.getInst()._virtualWidth;
        var ph:Float = ScreenMgr.getInst()._resHeight/ScreenMgr.getInst()._virtualHeight;
        var x = Math.round( Std.parseInt( _xt.text )/pw + ScreenMgr.getInst()._virtualX);
        var y = Math.round( Std.parseInt( _yt.text )/ph+ ScreenMgr.getInst()._virtualY);
        var w = Math.round( Std.parseInt( _wt.text )/pw);
        var h = Math.round( Std.parseInt( _ht.text )/ph);

        var ax = Math.round( Std.parseInt( _axt.text) );
        var ay = Math.round( Std.parseInt( _ayt.text) );
        var aw = Math.round( Std.parseInt( _awt.text) );
        var ah = Math.round( Std.parseInt( _aht.text) );
        if (ax >=_wnd._channel._w){ _axt.text = ""+(ax = _wnd._channel._w - 1); }
        if (ay >=_wnd._channel._h){ _ayt.text = ""+(ay = _wnd._channel._h - 1); }
        if (aw + ax >_wnd._channel._w){ _awt.text = ""+(aw = _wnd._channel._w - ax); }
        if (ah + ay >_wnd._channel._h){ _aht.text = ""+(ah = _wnd._channel._h - ay); }
        _wnd._virtualAreaX = (ax / _wnd._channel._w) * _wnd._virtualWidth;
        _wnd._virtualAreaY = (ay / _wnd._channel._h) * _wnd._virtualHeight;
        _wnd._virtualAreaW = (aw / _wnd._channel._w) * _wnd._virtualWidth;
        _wnd._virtualAreaH = (ah / _wnd._channel._h) * _wnd._virtualHeight;
        //trace( x);
        //trace( y);
        //trace( w);
        //trace( h);
        _wnd.reset(x,y, w,h ,cbDone);
    }
}
