package com.blueseer.device;

import base.network.SMConnection;
import base.network.NetworkMgr;
import com.blueseer.cmd.Command;

import nme.events.MouseEvent;
import nme.display.Sprite;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import com.blueseer.ui.UIMgr;
import base.data.DataLoader;
class Device {

    public var _deviceID:Int;
    public var _deviceName:String;

    public function new ( deviceID:Int, deviceName:String){
        _deviceID = deviceID;
        _deviceName = deviceName;
        DeviceMgr.getInst()._devices.set( deviceID, this);
    }

}

