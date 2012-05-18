package com.blueseer.ui;

import com.blueseer.ui.UIMgr;
import com.blueseer.cmd.CommandMgr;
import com.blueseer.cmd.Command;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;
import base.ui.CommDialog;
import base.ui.ComponentDlgMgr;
import base.ui.ListDialogMgr;
import base.ui.ComponentDlg;

class DeviceDialog extends CommDialog{

    public var _downx:Float;
    public var _downy:Float;
    public var _listDialogMgr:ComponentDlgMgr;
    public var _deviceID:Int;

    public function new ( mgr:ListDialogMgr, devicename:String, deviceid:Int ){
        _listDialogMgr = new ComponentDlgMgr(nme.Lib.current);
        _listDialogMgr._returnCallback = showParent;

        var str:String = devicename;
        _deviceID = deviceid;
        _uniqueId = str+_deviceID;
        var s:Sprite = mgr.createElement( str, deviceid);
        super(  mgr);
        addChild(s);
        createDlgs( deviceid);
    }

    public override function clear():Void{
        _listDialogMgr.clear();
        _listDialogMgr =null;
    }

    public function resetDlgs(){
        _listDialogMgr.removeAllMovables();
        createDlgs(_deviceID);
    }
    public function createDlgs( deviceid:Int){
        var arr:Array<Command> = CommandMgr.getInst().getCmdByDeviceID(deviceid);
        for( i in 0...arr.length){
            var d:CommDialog = new CMDComponentDlg( _listDialogMgr, arr[i]._commandName, arr[i]._commandID);
        }
    }

    override function onMouseClick( ):Void{
        resetDlgs();
        _listDialogMgr.showListDialog();
        hideParent();
    }
}

