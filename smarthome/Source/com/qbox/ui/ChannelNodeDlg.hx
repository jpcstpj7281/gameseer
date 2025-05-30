package com.qbox.ui;

import com.qbox.logic.Channel;
import com.qbox.logic.ScreenMgr;

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

    var _qboxip:EmbedTextField;
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
        var arr = ScreenMgr.getInst()._qboxes;
        for (i in 0...arr.length){
            if ( _qboxip.text == arr[i]._ipv4){
                var next = i+1;
                if ( next == arr.length ){
                    next=0;
                }
                _qboxip.text = arr[next]._ipv4;
                _node = _qboxip.text +":"+_input.text;
                break;
            }
        }
    }
    function onInputMouseClick( evt:MouseEvent ):Void{ 
        var arr = ScreenMgr.getInst()._qboxes;
        for (i in 0...arr.length){
            if ( _qboxip.text == arr[i]._ipv4){
                if ( _input.text != "null"){
                    var iter = arr[i]._inputs.iterator();
                    while ( iter.hasNext()){
                        var input = iter.next();
                        if ( _input.text == input){
                            if ( iter.hasNext()){
                                _input.text = iter.next();
                                break;
                            }else{
                                _input.text = arr[i]._inputs.iterator().next();
                            }
                        }
                    }
                    //var str:String = _input.text.substr( 2, _input.text.length -2);
                    //var input = Std.parseInt( str );
                    //++input;
                    //if ( input == Lambda.count(arr[i]._inputs)){
                    //input = 0;
                    //}
                    //_input.text = "in"+input;
                }
                else{
                    if ( Lambda.count(arr[i]._inputs) == 0){
                        _input.text = "null";
                    }else{
                        var key = arr[i]._inputs.keys().next();
                        _input.text = key + "("+ arr[i]._inputs.get(key)+")";
                    }
                }
                _node = _qboxip.text +":"+_input.text;
                break;
            }
        }
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var arr = _node.split(":");
        if ( arr.length != 2 ) return s;

        _qboxip= new EmbedTextField();
        _qboxip.selectable = false;
        _qboxip.text = arr[0];
        _qboxip.scaleX = 3;
        _qboxip.scaleY = 3;
        _qboxip.width = 60;
        _qboxip.height= 20;
        _qboxip.addEventListener( MouseEvent.CLICK, onQboxMouseClick);

        _input= new EmbedTextField();
        _input.selectable = false;
        _input.text = arr[1];
        _input.scaleX = 3;
        _input.scaleY = 3;
        _input.width = 50;
        _input.height= 20;
        _input.x = 200;
        _input.addEventListener( MouseEvent.CLICK, onInputMouseClick);

        s.addChild( _qboxip);
        s.addChild( _input);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }

}

