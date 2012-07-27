package com.qbox.ui;
import nme.events.MouseEvent;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;

import com.qbox.logic.Qbox;
import com.qbox.logic.Screen;
import com.qbox.logic.QboxMgr;

class ScreenDlg extends CommDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;
    var _screen:Screen;

    var _qboxid:EmbedTextField;
    var _output:EmbedTextField;

    public function new ( dm:ListDialogMgr, c:Screen){
        super(dm);
        _screen = c;
        addChild( createElement());
    }

    function onQboxMouseClick( evt:MouseEvent ):Void{ 
        var arr = QboxMgr.getInst()._qboxes;
        for (i in 0...arr.length){
            if ( _qboxid.text == arr[i]._ipv4){
                var next = i+1;
                if ( next == arr.length ){
                    next=0;
                }
                _screen._qboxid = _qboxid.text = arr[next]._ipv4;
                break;
            }
        }
    }
    function onOutputMouseClick( evt:MouseEvent ):Void{ 
        var arr = QboxMgr.getInst()._qboxes;
        for (i in 0...arr.length){
            if ( _qboxid.text == arr[i]._ipv4){
                var output:Int = Std.parseInt( _output.text.substr( 3, _output.text.length -2) );
                ++output;
                if ( output == Lambda.count(arr[i]._outputs)){
                    output = 0;
                }
                _screen._output = _output.text = "out"+output;
                break;
            }
        }
    }
    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        _qboxid= new EmbedTextField();
        _qboxid.selectable = false;
        _qboxid.text = _screen._qboxid;
        _qboxid.scaleX = 3;
        _qboxid.scaleY = 3;
        _qboxid.width = 50;
        _qboxid.height= 20;
        _qboxid.x = 150;
        _qboxid.addEventListener( MouseEvent.CLICK, onQboxMouseClick);

        _output= new EmbedTextField();
        _output.selectable = false;
        _output.text = _screen._output;
        _output.scaleX = 3;
        _output.scaleY = 3;
        _output.width = 50;
        _output.height= 20;
        _output.x = 300;
        _output.addEventListener( MouseEvent.CLICK, onOutputMouseClick);

        _pos= new EmbedTextField();
        _pos.selectable = false;
        _pos.text = "screen:" + _screen._col+"|"+_screen._row;
        _pos.scaleX = 3;
        _pos.scaleY = 3;
        _pos.width = 50;
        _pos.height= 20;

        s.addChild( _pos);
        s.addChild( _qboxid);
        s.addChild( _output);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
