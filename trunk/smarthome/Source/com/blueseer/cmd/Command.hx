package com.blueseer.cmd;

import com.blueseer.ui.UIMgr;
import base.network.SMConnection;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.network.NetworkMgr;

import nme.events.MouseEvent;
import nme.display.Sprite;
import com.blueseer.cmd.CommandMgr;
import haxe.io.BytesBuffer;
import haxe.io.Bytes;
class Command {

    //every Command has a type.
    public var _commandID:Int;
    public var _commandName:String;
    //public var _deviceType(default, setDeviceType):Int;
    public var _deviceType:Int;


    public function new ( commandID:Int, commandName:String = null, deviceType:Int = 0){
        _commandID= commandID;
        _commandName = commandName;
        _deviceType = deviceType;

        CommandMgr.getInst().setCmd( this);

        //UIMgr.getInst().createCMDDialog(this);
    }


    private function setCmd( ):Void{
        var conn:SMConnection = cast( NetworkMgr.inst.getConn());
        conn.setMsg(_commandID, 0);
        //conn.setData("开1231231关");
    }

    public function flush():Void{
        var conn:SMConnection = cast( NetworkMgr.inst.getConn() );
        setCmd();
        conn.sendData();
    }

    public function updateDeviceType():Void{
        var conn:SMConnection = cast( NetworkMgr.inst.getConn() );
        if( conn.startListening( 12, onResponse) == false) return;
        conn.clearData();
        conn.setMsg(11);
        conn.addKeyVal( "__OP__", Bytes.ofString("modify_cmd_type"));
        conn.addKeyVal( "_CMD_ID", NetworkMgr.int2Bytes(_commandID) );
        //trace("str: " + str.length);
        conn.addKeyVal( "_CMD_TYPE", NetworkMgr.int2Bytes(_deviceType) );
        conn.sendData();
    }

    public function fire():Void{
        var conn:SMConnection = cast( NetworkMgr.inst.getConn() );
        if( conn.startListening( 12, onResponse) == false) return;
        conn.clearData();
        conn.setMsg(11);
        conn.addKeyVal( "__OP__", Bytes.ofString("fire_cmd"));
        conn.addKeyVal( "_CMD_ID", NetworkMgr.int2Bytes(_commandID) );
        conn.sendData();
    }

    function onResponse( datas:Hash<String>):Void{
        trace("update device type of cmd: " + _commandName);

    }

}

