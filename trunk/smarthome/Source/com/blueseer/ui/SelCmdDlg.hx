package com.blueseer.ui;

import com.blueseer.ui.UIMgr;
import com.blueseer.cmd.CommandMgr;
import com.blueseer.cmd.Command;
import com.blueseer.device.Device;
import com.blueseer.device.DeviceMgr;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.display.Sprite;
import base.ui.CommDialog;
import base.ui.CommDialogMgr;
import base.ui.SubListDialogMgr;
import base.ui.ListDialogMgr;

class SelCmdDlg extends CommDialog{

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
}

