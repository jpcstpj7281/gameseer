package com.qbox.ui;

import com.qbox.logic.QboxMgr;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import base.ui.ListDialog;
import base.ui.CommDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;

import com.qbox.logic.Qbox;
import com.qbox.logic.Channel;

class ChannelDlg extends ListDialog{

    var _s:Sprite;
    //var _input:EmbedTextField;
    var _iptext:EmbedTextField;
    //var _editBtn:EmbedTextField;
    var _channel:Channel;

    public function new ( dm:ListDialogMgr, c:Channel){
        super(dm);
        _channel = c;
        addChild( createElement());
    }


    //public function onEditBtnMouseClick( evt:MouseEvent ):Void{
    //for ( i in _channel._nodes){
    //new ChannelNodeDlg(_listDialogMgr, i);
    //}
    //super.onMouseClick();
    //}
    //override function onMouseClick():Void{}
    //public override function showParent():Void{
    //if ( _listDialogMgr._movableInstances.length >0 ){
            //var arr:Array<String> = new Array<String>();
            //for ( l in _listDialogMgr._movableInstances){
            //if ( Std.is( l , ChannelNodeDlg) ){
            //arr.push( cast(l, ChannelNodeDlg)._node);
            //}
            //}
            //_channel._nodes = arr;
            //}
            //super.showParent();
            //}

    override function show(){
        if ( _s != null) {
            if ( _iptext!= null){
                _s.removeChild(_iptext);
                //_s.removeChild(_input);
                //_s.removeChild(_editBtn);
            }
            _iptext= new EmbedTextField();
            _iptext.selectable = false;
            _iptext.text = "Channel:"+ _channel._screen._ipv4+" col:"+_channel._screen._col+" row:"+_channel._screen._row+" in port:"+_channel._inport+" w:"+_channel._w+" h:"+_channel._h;
            _iptext.scaleX = 3;
            _iptext.scaleY = 3;
            _iptext.width = nme.Lib.current.stage.stageWidth;
            _iptext.height= 20;

            //_input= new EmbedTextField();
            //_input.text = "channel";//_channel._name;
            //_input.type = INPUT;
            //_input.scaleX = 3;
            //_input.scaleY = 3;
            //_input.width = 60;
            //_input.height= 16;
            //_input.setBorder(true);
            //_input.x= 100;

            //_editBtn= new EmbedTextField();
            //_editBtn.selectable = false;
            //_editBtn.text = "Edit";
            //_editBtn.scaleX = 3;
            //_editBtn.scaleY = 3;
            //_editBtn.width = 20;
            //_editBtn.height= 18;
            //_editBtn.setBorder(true);
            //_editBtn.x = nme.Lib.current.stage.stageWidth - 80;
            //_editBtn.addEventListener( MouseEvent.CLICK, onEditBtnMouseClick);

            _s.addChild( _iptext);
            //_s.addChild( _input);
            //_s.addChild( _editBtn);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null ) {
            if ( _iptext != null) {_s.removeChild(_iptext);_iptext= null;}
            //if ( _input != null){ _s.removeChild(_input);_input= null;}
            //if ( _editBtn != null){
            //_s.removeChild(_editBtn);
                //_editBtn.removeEventListener(  MouseEvent.CLICK, onEditBtnMouseClick); 
                //_editBtn= null;
                //}
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s = new Sprite();

        return _s;
    }
}
