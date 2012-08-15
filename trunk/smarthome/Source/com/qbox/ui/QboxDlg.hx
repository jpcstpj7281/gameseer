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

class QboxDlg extends CommDialog{

    var _usrInput:EmbedTextField;
    var _iptext:EmbedTextField;
    var _porttext:EmbedTextField;
    var _portInput:EmbedTextField;
    var _connBtn:EmbedTextField;
    var _detail:EmbedTextField;
    var _delete:EmbedTextField;
    var _qbox:Qbox;

    var _s:Sprite;

    public function new ( dm:ListDialogMgr, q:Qbox){
        super(dm);
        _qbox = q;
        addChild( createElement());
    }

    function onConnBtnMouseClick( evt:MouseEvent ):Void{
        if ( _connBtn.text == "disconnect"){
            _qbox.close();
            _connBtn.text = "connect";
            trace("disconnect");
        }else{
            _qbox._ipv4 = _usrInput.text;
            _qbox._port= Std.parseInt(_portInput.text);
            trace("connect");
            _qbox.connect();
            trace("connect");
            if (_qbox._isFailed == false && _qbox.isConected() ){
                _qbox.connectedInit();
                _connBtn.text = "disconnect";
            }
        }
    }

    override function show(){
        if ( _s != null) {
            if ( _iptext!= null){
                _s.removeChild( _iptext);
                _s.removeChild( _usrInput);
                _s.removeChild( _porttext);
                _s.removeChild( _portInput);
                _s.removeChild( _connBtn);
                _s.removeChild( _detail);
                _s.removeChild( _delete);
            }
            _iptext= new EmbedTextField();
            _iptext.selectable = false;
            _iptext.text = "IP:";
            _iptext.scaleX = 3;
            _iptext.scaleY = 3;
            _iptext.width = 50;
            _iptext.height= 20;

            _usrInput= new EmbedTextField();
            _usrInput.text = _qbox._ipv4;
            _usrInput.type = INPUT;
            _usrInput.scaleX = 3;
            _usrInput.scaleY = 3;
            _usrInput.width = 60;
            _usrInput.height= 16;
            _usrInput.setBorder(true);
            _usrInput.x= 40;

            _porttext= new EmbedTextField();
            _porttext.selectable = false;
            _porttext.text = "PORT:";
            _porttext.scaleX = 3;
            _porttext.scaleY = 3;
            _porttext.width = 50;
            _porttext.height= 20;
            _porttext.x = 220;

            _portInput= new EmbedTextField();
            _portInput.text = ""+_qbox._port;
            _portInput.type = INPUT;
            _portInput.scaleX = 3;
            _portInput.scaleY = 3;
            _portInput.width = 20;
            _portInput.height= 16;
            _portInput.setBorder(true);
            _portInput.x= 300;

            _connBtn= new EmbedTextField();
            _connBtn.setBorder(true);
            _connBtn.selectable = false;
            if ( _qbox._isFailed || !_qbox.isConected() ){
                _connBtn.text = "connect";
            }else{
                _connBtn.text = "disconnect";
            }
            _connBtn.scaleX = 3;
            _connBtn.scaleY = 3;
            _connBtn.width = 40;
            _connBtn.height= 16;
            _connBtn.x = 370;
            _connBtn.addEventListener( MouseEvent.CLICK, onConnBtnMouseClick);

            _detail= new EmbedTextField();
            _detail.setBorder(true);
            _detail.selectable = false;
            _detail.text = "detail";
            _detail.scaleX = 3;
            _detail.scaleY = 3;
            _detail.width = 40;
            _detail.height= 16;
            _detail.x = 530;

            _delete= new EmbedTextField();
            _delete.setBorder(true);
            _delete.selectable = false;
            _delete.text = "delete";
            _delete.scaleX = 3;
            _delete.scaleY = 3;
            _delete.width = 40;
            _delete.height= 16;
            _delete.x = 690;

            _s.addChild( _iptext);
            _s.addChild( _usrInput);
            _s.addChild( _porttext);
            _s.addChild( _portInput);
            _s.addChild( _connBtn);
            _s.addChild( _detail);
            _s.addChild( _delete);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _iptext!= null) {
            _connBtn.removeEventListener( MouseEvent.CLICK, onConnBtnMouseClick);
            _s.removeChild( _iptext);
            _s.removeChild( _usrInput);
            _s.removeChild( _porttext);
            _s.removeChild( _portInput);
            _s.removeChild( _connBtn);
            _s.removeChild( _detail);
            _s.removeChild( _delete);
            _iptext= null;
            _usrInput= null;
            _portInput= null;
            _connBtn= null;
            _detail= null;
            _delete= null;
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();


        return _s;
    }
}
