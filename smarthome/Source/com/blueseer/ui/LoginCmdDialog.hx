
package com.blueseer.ui;

import com.blueseer.ui.UIMgr;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import base.network.SMConnection;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.network.NetworkMgr;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;
import nme.display.DisplayObject;
import haxe.io.Bytes;
import base.ui.CommDialog;
import base.ui.ListDialogMgr;

class LoginCmdDialog extends CommDialog{
    var _usrInput:EmbedTextField ;
    var _pswInput:EmbedTextField ;
    var _hint:EmbedTextField ;
    var _OK:EmbedTextField ;
    var _reg:EmbedTextField ;
    var _cancel:EmbedTextField ;
    var _pswShow:EmbedTextField ;


    public function new (mgr:ListDialogMgr ){
        var str:String = "登录";
        var id:Int = 0;
        _uniqueId = str+id;
        var s:Sprite = mgr.createElement( str, id);
        super( mgr);
        addChild(s);
    }

    override function onMouseClick(){
        if ( _mgr.isAnimating()) return;

        if ( _usrInput == null ){
            _usrInput= new EmbedTextField();
            _pswInput= new EmbedTextField();
            _hint= new EmbedTextField();
            _OK= new EmbedTextField();
            _cancel= new EmbedTextField();
            _reg = new EmbedTextField();
            _pswShow= new EmbedTextField();
            _pswShow.text = "psw";
            _pswShow.scaleX = 3;
            _pswShow.scaleY = 3;
            _pswShow.y = 260;
            _pswShow.x = 300;
            _pswShow.height = 20;
            _pswShow.width = 20;
            _pswShow.setBorder(true);
            _pswShow.selectable = false;

            _reg.text = "reg";
            _reg.scaleX = 3;
            _reg.scaleY = 3;
            _reg.y = 260;
            _reg.x = 0;
            _reg.height = 20;
            _reg.width = 20;
            _reg.setBorder(true);
            _reg.selectable = false;

            _OK.text = "OK";
            _OK.scaleX = 3;
            _OK.scaleY = 3;
            _OK.y = 260;
            _OK.x = 100;
            _OK.height = 20;
            _OK.width = 20;
            _OK.setBorder(true);
            _OK.selectable = false;
            _cancel.text = "cancel";
            _cancel.scaleX = 3;
            _cancel.scaleY = 3;
            _cancel.y = 260;
            _cancel.x = 200;
            _cancel.setBorder(true);
            _cancel.height = 20;
            _cancel.width = 20;
            _cancel.selectable = false;
            _OK.setBorder(true);
            _hint.selectable = false;
            _hint.text = "Input your account and psw";
            _hint.scaleX = 3;
            _hint.scaleY = 3;
            _hint.width = nme.Lib.current.stage.stageWidth;
            _hint.height= 20;
            _usrInput.type = INPUT;
            _usrInput.scaleX = 3;
            _usrInput.scaleY = 3;
            _usrInput.width = nme.Lib.current.stage.stageWidth;
            _usrInput.height= 20;
            _usrInput.setBorder(true);
            _usrInput.y= 100;

            _pswInput.type = INPUT;
            _pswInput.scaleX = 3;
            _pswInput.scaleY = 3;
            _pswInput.width = nme.Lib.current.stage.stageWidth;
            _pswInput.height= 20 ;
            _pswInput.setBorder(true);
            _pswInput.y= 180;
            _pswInput.displayAsPassword  = true;
            

            _OK.addEventListener( MouseEvent.CLICK, onOK);
            _reg.addEventListener( MouseEvent.CLICK, onReg);
            _cancel.addEventListener( MouseEvent.CLICK, onCancel);
            _pswShow.addEventListener( MouseEvent.CLICK, onPswShow);

            _elements.push( _OK);
            _elements.push( _reg);
            _elements.push( _cancel);
            _elements.push( _hint);
            _elements.push( _usrInput);
            _elements.push( _pswInput);
            _elements.push( _pswShow);
        }

        showElements();
        nme.Lib.current.stage.focus = _usrInput;
        cast(_mgr, ListDialogMgr).hideListDialog();
    }

    override function clear():Void{
        hideElements();
    }

    private function swichBackToCMDView():Void{
        hideElements();
        cast(_mgr, ListDialogMgr).showListDialog();
    }

    public function onReg(evt:MouseEvent){
        trace("usr: "+ _usrInput.text);
        trace("psw: "+ _pswInput.text);

        var conn:SMConnection  = cast(NetworkMgr.getInst().getConn());
        conn.startListening( 2, onLogin);
        conn.setMsg(5);
        conn.addKeyVal( "user", Bytes.ofString(_usrInput.text));
        conn.addKeyVal( "psw", Bytes.ofString(_pswInput.text));
        conn.sendData();
    }

    public function onOK(evt:MouseEvent){
        swichBackToCMDView();
        trace("usr: "+ _usrInput.text);
        trace("psw: "+ _pswInput.text);
        var conn:SMConnection  = cast(NetworkMgr.getInst().getConn());
        conn.startListening( 2, onLogin);
        conn.setMsg(1);
        conn.addKeyVal( "user", Bytes.ofString(_usrInput.text));
        conn.addKeyVal( "psw", Bytes.ofString(_pswInput.text));
        conn.sendData();

    }

    public function onLogin( datas:Hash<Bytes>):Void{
    }

    public function onCancel(evt:MouseEvent){
        swichBackToCMDView();
    }
    public function onPswShow(evt:MouseEvent){
        _pswInput.displayAsPassword = !_pswInput.displayAsPassword;
    }
}

