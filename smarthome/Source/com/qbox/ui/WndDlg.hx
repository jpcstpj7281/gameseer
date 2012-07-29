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

import com.qbox.logic.Qbox;
import com.qbox.logic.Wnd;

class WndDlg extends CommDialog{

    var _iptext:EmbedTextField;
    var _xt:EmbedTextField;
    var _yt:EmbedTextField;
    var _wt:EmbedTextField;
    var _ht:EmbedTextField;
    var _wnd:Wnd;

    public function new ( dm:ListDialogMgr, c:Wnd){
        super(dm);
        _wnd = c;
        addChild( createElement());
    }

    override function show(){
        _xt.text = "X:" +_wnd._virtualX;
        _yt.text = "Y:"+_wnd._virtualY;
        _wt.text = "W:"+_wnd._virtualWidth;
        _ht.text = "H:"+_wnd._virtualHeight;
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
        _xt.selectable = false;
        _xt.text = "X:" +_wnd._virtualX;
        _xt.scaleX = 3;
        _xt.scaleY = 3;
        _xt.width = 50;
        _xt.height= 20;
        _xt.x = 150;

        _yt= new EmbedTextField();
        _yt.selectable = false;
        _yt.text = "Y:"+_wnd._virtualY;
        _yt.scaleX = 3;
        _yt.scaleY = 3;
        _yt.width = 50;
        _yt.height= 20;
        _yt.x = 250;

        _wt= new EmbedTextField();
        _wt.selectable = false;
        _wt.text = "W:"+_wnd._virtualWidth;
        _wt.scaleX = 3;
        _wt.scaleY = 3;
        _wt.width = 50;
        _wt.height= 20;
        _wt.x = 350;

        _ht= new EmbedTextField();
        _ht.selectable = false;
        _ht.text = "H:"+_wnd._virtualHeight;
        _ht.scaleX = 3;
        _ht.scaleY = 3;
        _ht.width = 50;
        _ht.height= 20;
        _ht.x = 450;

        s.addChild( _iptext);
        s.addChild( _xt);
        s.addChild( _yt);
        s.addChild( _wt);
        s.addChild( _ht);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
