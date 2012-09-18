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
    var _s:Sprite;

    var _wnd:Wnd;

    public function new ( dm:ListDialogMgr, c:Wnd){
        super(dm);
        _wnd = c;
        addChild( createElement());
    }

    override function show(){
        if ( _s != null) {
            if (_wndtext!= null) _s.removeChild(_wndtext);
            if (_xt!= null)_s.removeChild(_xt);
            if (_yt!= null)_s.removeChild(_yt);
            if (_wt!= null)_s.removeChild(_wt);
            if (_ht!= null)_s.removeChild(_ht);
            if (_st!= null)_s.removeChild(_st);

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

            _xt= new EmbedTextField();
            _xt.type = INPUT;
            _xt.setBorder(true);
            _xt.scaleX = 3;
            _xt.scaleY = 3;
            _xt.width = 30;
            _xt.height= 16;
            _xt.x = 150;

            _yt= new EmbedTextField();
            _yt.type = INPUT;
            _yt.setBorder(true);
            _yt.scaleX = 3;
            _yt.scaleY = 3;
            _yt.width = 30;
            _yt.height= 16;
            _yt.x = 250;

            _wt= new EmbedTextField();
            _wt.type = INPUT;
            _wt.setBorder(true);
            _wt.text =""+ _wnd._virtualWidth;
            _wt.scaleX = 3;
            _wt.scaleY = 3;
            _wt.width = 30;
            _wt.height= 16;
            _wt.x = 350;

            _ht= new EmbedTextField();
            _ht.type = INPUT;
            _ht.setBorder(true);
            _ht.scaleX = 3;
            _ht.scaleY = 3;
            _ht.width = 30;
            _ht.height= 16;
            _ht.x = 450;

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
            _st.x = 550;
            _st.addEventListener( MouseEvent.CLICK, onUpdateBtnMouseClick);

            var pw:Float = ScreenMgr.getInst()._resWidth/ScreenMgr.getInst()._virtualWidth;
            var ph:Float = ScreenMgr.getInst()._resHeight/ScreenMgr.getInst()._virtualHeight;
            var x = Math.round( (_wnd._virtualX - ScreenMgr.getInst()._virtualX) *pw);
            var y = Math.round( (_wnd._virtualY - ScreenMgr.getInst()._virtualY) *ph);
            var w = Math.round( _wnd._virtualWidth*pw);
            var h = Math.round( _wnd._virtualHeight*ph);
            _xt.text = ""+x;
            _yt.text = ""+y;
            _wt.text = ""+w;
            _ht.text = ""+h;
            _s.addChild( _wndtext);
            _s.addChild( _xt);
            _s.addChild( _yt);
            _s.addChild( _wt);
            _s.addChild( _ht);
            _s.addChild( _st);
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
            if ( _st!= null){ 
                _st.removeEventListener(  MouseEvent.CLICK, onUpdateBtnMouseClick);
                _s.removeChild(_st);
                _st= null;
            }
        }
        return super.hide();
    }
    public function createElement():Sprite{

        _s= new Sprite();
        return _s;
    }

    function onUpdateBtnMouseClick( evt:MouseEvent){
        var pw:Float = ScreenMgr.getInst()._resWidth/ScreenMgr.getInst()._virtualWidth;
        var ph:Float = ScreenMgr.getInst()._resHeight/ScreenMgr.getInst()._virtualHeight;
        var x = Math.round( Std.parseInt( _xt.text )/pw + ScreenMgr.getInst()._virtualX);
        var y = Math.round( Std.parseInt( _yt.text )/ph)+ ScreenMgr.getInst()._virtualY;
        var w = Math.round( Std.parseInt( _wt.text )/pw);
        var h = Math.round( Std.parseInt( _ht.text )/ph);
        trace( x);
        trace( y);
        trace( w);
        trace( h);
        _wnd.reset(x,y, w,h );
    }
}
