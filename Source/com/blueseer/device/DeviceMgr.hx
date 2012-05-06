package com.blueseer.device;


import nme.Lib;
import nme.events.Event;
import base.network.SMConnection;
import base.network.NetworkMgr;
import haxe.io.Bytes;

class DeviceMgr{

    //public var _devices:Hash<Device>;
    public var _devices:IntHash<Device>;

    public function new (){
        _devices = new IntHash<Device>();
        //trace("device mamager init");
    }

    public function clear(){ _devices = new IntHash<Device>(); }

    public function createDevice( deviceName:String):Void{
        //trace("DeviceMgr "+ deviceName+" len: "+deviceName.length);

        var conn:SMConnection  = cast(NetworkMgr.getInst().getConn());
        if( conn.startListening( 12, onCreatedDevice)){
            conn.clearData();
            conn.setMsg(11);
            conn.addKeyVal( "__OP__", Bytes.ofString("add_device"));
            conn.addKeyVal( "DEVICE", Bytes.ofString(deviceName));
            conn.sendData();
        }
    }

    function onCreatedDevice( datas:Hash<Bytes>):Void{
        var val:Int = 0;
        var deviceName:String = "";
        if ( NetworkMgr.responseTrue( datas) ){
            var ks:Iterator<String> = datas.keys();
            while( ks.hasNext() ){
                var key:String = ks.next();
                if ( key.substr(0, 10) == "_DEVICE_ID"){
                    val = NetworkMgr.bytes2Int( datas.get(key) );
                    deviceName = key.substr( 10, key.length - 10 );
                    //deviceName = key;
                    trace("key: "+key+ " name: "+deviceName + " val: "+val);
                }
            }
        }
        new Device( val, deviceName);

        com.blueseer.ui.UIMgr.getInst().resetDlgs();
        com.blueseer.ui.UIMgr.getInst().showListDialog();
    }

    static var inst:DeviceMgr;
    inline public static function getInst():DeviceMgr{
        if ( inst == null) {
            inst = new DeviceMgr();
        }
        return inst;
    }
}

