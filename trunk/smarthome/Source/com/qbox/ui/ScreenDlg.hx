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
import com.qbox.logic.Screen;

class ScreenDlg extends CommDialog{

    var _usrInput:EmbedTextField;
    var _iptext:EmbedTextField;
    var _porttext:EmbedTextField;
    var _portInput:EmbedTextField;
    var _connBtn:EmbedTextField;
    var _detail:EmbedTextField;
    var _delete:EmbedTextField;
    var _screen:Screen;

    public function new ( dm:ListDialogMgr, c:Screen){
        super(dm);
        _screen = c;
        addChild( createElement());
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();


        _iptext= new EmbedTextField();
        _iptext.selectable = false;
        _iptext.text = "screen:" + _screen._col+"|"+_screen._row;
        _iptext.scaleX = 3;
        _iptext.scaleY = 3;
        _iptext.width = 50;
        _iptext.height= 20;

        _usrInput= new EmbedTextField();
        _usrInput.text = "";
        _usrInput.type = INPUT;
        _usrInput.scaleX = 3;
        _usrInput.scaleY = 3;
        _usrInput.width = 60;
        _usrInput.height= 16;
        _usrInput.setBorder(true);
        _usrInput.x= 110;

        s.addChild( _iptext);
        s.addChild( _usrInput);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
