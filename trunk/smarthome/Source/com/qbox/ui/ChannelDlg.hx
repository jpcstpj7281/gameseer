package com.qbox.ui;

import com.qbox.logic.QboxMgr;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import base.ui.ListDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;

import com.qbox.logic.Qbox;
import com.qbox.logic.Channel;

class ChannelDlg extends ListDialog{

    var _usrInput:EmbedTextField;
    var _iptext:EmbedTextField;
    var _editBtn:EmbedTextField;
    var _channel:Channel;

    public function new ( dm:ListDialogMgr, c:Channel){
        super(dm);
        _channel = c;
        addChild( createElement());

        new PlusItemFixedDlg(_listDialogMgr, cbPlus);
    }

    public function cbPlus( ):Void{
        if ( QboxMgr.getInst()._qboxes.length == 0 ) return;
        var qd = new ChannelNodeDlg(_listDialogMgr, QboxMgr.getInst()._qboxes[0]._ipv4 + ":" + "in0" );
        qd.show();
    }

    function onConnBtnMouseClick( evt:MouseEvent ):Void{
        for ( i in _channel._nodes){
            new ChannelNodeDlg(_listDialogMgr, i);
        }
    }

    public override function showParent():Void{
        if ( _listDialogMgr._movableInstances.length >0 ){
            var arr:Array<String> = new Array<String>();
            for ( l in _listDialogMgr._movableInstances){
                if ( Std.is( l , ChannelNodeDlg) ){
                    arr.push( cast(l, ChannelNodeDlg)._node);
                }
            }
            _channel._nodes = arr;
        }
        super.showParent();
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        _iptext= new EmbedTextField();
        _iptext.selectable = false;
        _iptext.text = "Channel:";
        _iptext.scaleX = 3;
        _iptext.scaleY = 3;
        _iptext.width = 50;
        _iptext.height= 20;

        _usrInput= new EmbedTextField();
        _usrInput.text = _channel._name;
        _usrInput.type = INPUT;
        _usrInput.scaleX = 3;
        _usrInput.scaleY = 3;
        _usrInput.width = 60;
        _usrInput.height= 16;
        _usrInput.setBorder(true);
        _usrInput.x= 100;

        _editBtn= new EmbedTextField();
        _editBtn.selectable = false;
        _editBtn.text = "Edit";
        _editBtn.scaleX = 3;
        _editBtn.scaleY = 3;
        _editBtn.width = 20;
        _editBtn.height= 18;
        _editBtn.setBorder(true);
        _editBtn.x = nme.Lib.current.stage.stageWidth - 80;
        _editBtn.addEventListener( MouseEvent.CLICK, onConnBtnMouseClick);

        s.addChild( _iptext);
        s.addChild( _usrInput);
        s.addChild( _editBtn);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
