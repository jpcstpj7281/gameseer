package com.qbox.ui;

import com.qbox.logic.Channel;
import com.qbox.logic.QboxMgr;

import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;
import base.ui.CommDialog;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import base.ui.SubListDialogMgr;

class ChannelNodeDlg extends CommDialog{

    var _qboxid:EmbedTextField;
    var _input:EmbedTextField;
    public var _node:String;

    public function new ( cmdDlgMgr:ListDialogMgr, node:String){
        super(  cmdDlgMgr );
        _node= node;
        var s:Sprite = createElement( );
        addChild(s);
        show();
    }

    function onQboxMouseClick( evt:MouseEvent ):Void{ 
        var arr = QboxMgr.getInst()._qboxes;
        for (i in 0...arr.length){
            if ( _qboxid.text == arr[i]._ipv4){
                var next = i+1;
                if ( next == arr.length ){
                    next=0;
                }
                _qboxid.text = arr[next]._ipv4;
                _node = _qboxid.text +":"+_input.text;
                break;
            }
        }
    }
    function onInputMouseClick( evt:MouseEvent ):Void{ 
        var arr = QboxMgr.getInst()._qboxes;
        for (i in 0...arr.length){
            if ( _qboxid.text == arr[i]._ipv4){
                if ( _input.text != "null"){
                    var str:String = _input.text.substr( 2, _input.text.length -2);
                    var input = Std.parseInt( str );
                    ++input;
                    if ( input == Lambda.count(arr[i]._inputs)){
                        input = 0;
                    }
                    _input.text = "in"+input;
                }
                else{
                    if ( Lambda.count(arr[i]._inputs) == 0){
                        _input.text = "null";
                    }else{
                        _input.text = arr[i]._inputs.iterator().next();
                    }
                }

                _node = _qboxid.text +":"+_input.text;
                break;
            }
        }
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var arr = _node.split(":");
        if ( arr.length != 2 ) return s;

        _qboxid= new EmbedTextField();
        _qboxid.selectable = false;
        _qboxid.text = arr[0];
        _qboxid.scaleX = 3;
        _qboxid.scaleY = 3;
        _qboxid.width = 50;
        _qboxid.height= 20;
        _qboxid.addEventListener( MouseEvent.CLICK, onQboxMouseClick);

        _input= new EmbedTextField();
        _input.selectable = false;
        _input.text = arr[1];
        _input.scaleX = 3;
        _input.scaleY = 3;
        _input.width = 50;
        _input.height= 20;
        _input.x = 200;
        _input.addEventListener( MouseEvent.CLICK, onInputMouseClick);

        s.addChild( _qboxid);
        s.addChild( _input);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }

}

