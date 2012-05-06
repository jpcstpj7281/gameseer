package com.blueseer.ui;

import com.blueseer.ui.UIMgr;
import com.blueseer.cmd.CommandMgr;
import com.blueseer.cmd.Command;
import com.blueseer.device.Device;
import com.blueseer.device.DeviceMgr;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;
import base.ui.CommDialog;
import base.ui.CommDialogMgr;
import base.ui.SubListDialogMgr;
import base.ui.ListDialogMgr;

class SelCmdDlg extends CommDialog{

    //public var _downx:Float;
    //public var _downy:Float;
    public var _cmdid:Int;
    public var _listDialogMgr:SubListDialogMgr;

    public function new ( mgr:ListDialogMgr, cmdName:String, cmdid:Int ){
        _listDialogMgr = new SubListDialogMgr(nme.Lib.current);
        _listDialogMgr._returnCallback = returnCallback;

        var str:String = cmdName;
        _cmdid = cmdid;
        _uniqueId = str+_cmdid;
        var s:Sprite = mgr.createElement( str, cmdid);
        super(  mgr);
        addChild(s);

        //this.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
        //this.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
        //this.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);
    }

    public function returnCallback():Void{
        var cmd:Command = CommandMgr.getInst()._commands.get(_cmdid);
        cmd.updateDeviceType();
        showParent();
    }

    public override function clear():Void{
        _listDialogMgr.clear();
        _listDialogMgr =null;
    }

    public function resetDlgs(){
        _listDialogMgr.clear();
        _listDialogMgr = new SubListDialogMgr(nme.Lib.current);
        _listDialogMgr._returnCallback = returnCallback;
        createDlgs();
    }

    public function createDlgs( ){
        var it:Iterator<Device> = DeviceMgr.getInst()._devices.iterator();
        while( it.hasNext() ){
            var d:Device = it.next();
            new SelectDeviceDialog(_listDialogMgr, d._deviceName, d._deviceID, _cmdid);
        }
    }

    override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            resetDlgs();
            _listDialogMgr.showListDialog();
            hideParent();
        }
    }

    //public function onMouseDown(evt:MouseEvent){ 
    //_downx = evt.stageX;
    //_downy = evt.stageY;
    //}
    //public function onMouseMove(evt:MouseEvent){ 
    //if( (evt.stageX- _downx) > 100 ){
    ////trace("move");
    //_downx = 10000;
    //_downy = 10000;
    //}else if ( (evt.stageY - _downy)  > 100 ){
    ////trace("move");
    //_downx = 10000;
    //_downy = 10000;
    //}
    //}
    //public function onMouseUp(evt:MouseEvent){ 
    //if( (evt.stageX - _downx) < 10 && (evt.stageX - _downx) > -10&& (evt.stageY - _downy) <10 && (evt.stageY - _downy) >-10 ){
    //onMouseClicked(evt);
    //}
    //else{
    //_downx = 10000;
    //_downy = 10000;
    ////trace("move up");
    //}
    //}
}

