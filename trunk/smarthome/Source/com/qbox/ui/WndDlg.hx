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

    var _iptext:EmbedTextField;
    var _xt:EmbedTextField;
    var _yt:EmbedTextField;
    var _wt:EmbedTextField;
    var _ht:EmbedTextField;
    var _st:EmbedTextField;

    var _wnd:Wnd;

    public function new ( dm:ListDialogMgr, c:Wnd){
        super(dm);
        _wnd = c;
        addChild( createElement());
    }

    override function show(){
        _xt.text = "" +_wnd._virtualX;
        _yt.text = ""+_wnd._virtualY;
        _wt.text = ""+_wnd._virtualWidth;
        _ht.text = ""+_wnd._virtualHeight;
        return super.show();
    }

    public function createElement():Sprite{

        var s:Sprite = new Sprite();
        _iptext= new EmbedTextField();
        _iptext.selectable = false;
        _iptext.text = "wnd:";
        _iptext.scaleX = 3;
        _iptext.scaleY = 3;
        _iptext.width = 50;
        _iptext.height= 20;

        _xt= new EmbedTextField();
        _xt.type = INPUT;
        _xt.setBorder(true);
        _xt.text =""+ _wnd._virtualX;
        _xt.scaleX = 3;
        _xt.scaleY = 3;
        _xt.width = 30;
        _xt.height= 20;
        _xt.x = 150;

        _yt= new EmbedTextField();
        _yt.type = INPUT;
        _yt.setBorder(true);
        _yt.text =""+ _wnd._virtualY;
        _yt.scaleX = 3;
        _yt.scaleY = 3;
        _yt.width = 30;
        _yt.height= 20;
        _yt.x = 250;

        _wt= new EmbedTextField();
        _wt.type = INPUT;
        _wt.setBorder(true);
        _wt.text =""+ _wnd._virtualWidth;
        _wt.scaleX = 3;
        _wt.scaleY = 3;
        _wt.width = 30;
        _wt.height= 20;
        _wt.x = 350;

        _ht= new EmbedTextField();
        _ht.type = INPUT;
        _ht.setBorder(true);
        _ht.text =""+ _wnd._virtualHeight;
        _ht.scaleX = 3;
        _ht.scaleY = 3;
        _ht.width = 30;
        _ht.height= 20;
        _ht.x = 450;

        _st= new EmbedTextField();
        _st.setBorder(true);
        _st.text = "update";
        _st.selectable = false;
        _st.scaleX = 3;
        _st.scaleY = 3;
        _st.width = 30;
        _st.height= 20;
        _st.x = 550;
        _st.addEventListener( MouseEvent.CLICK, onUpdateBtnMouseClick);

        s.addChild( _iptext);
        s.addChild( _xt);
        s.addChild( _yt);
        s.addChild( _wt);
        s.addChild( _ht);
        s.addChild( _st);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }

    function onUpdateBtnMouseClick( evt:MouseEvent){
        var pw:Float = ScreenMgr.getInst()._resWidth/ScreenMgr.getInst()._virtualWidth;
        var ph:Float = ScreenMgr.getInst()._resHeight/ScreenMgr.getInst()._virtualHeight;
        _wnd.reset(Math.round( Std.parseInt( _xt.text )*pw),
                Math.round( Std.parseInt( _yt.text )*ph),
                Math.round( Std.parseInt( _wt.text )*pw),
                Math.round( Std.parseInt( _ht.text )*ph)
                );
    }
}
