package com.blueseer.cmd;


import nme.Lib;
import nme.events.Event;
import base.network.SMConnection;
import base.network.NetworkMgr;
import haxe.io.Bytes;

class CommandMgr{

    //public var _devices:Hash<Device>;
    public var _commands:IntHash<Command>;

    public function new (){
        _commands= new IntHash<Command>();
        //trace("device mamager init");
    }

    public function clear(){ _commands= new IntHash<Command>(); }

    public function setCmd( cmd:Command):Void{

        var c = _commands.get(cmd._commandID);
        if ( c != null ){
            trace( "" + cmd._commandID + " cmd already existed");
        }

        _commands.set( cmd._commandID, cmd);
    }

    public function getCmd( id:Int):Command{
        return _commands.get( id);
    }


    public function getTyped( ):Array<Command>{
        var it:Iterator<Command> = _commands.iterator();
        var cmds:Array<Command> = new Array<Command>();
        while( it.hasNext()){
            var cmd:Command  = it.next();
            if ( cmd._deviceType != 0 ){
                cmds.push(cmd);
                //trace(cmd._commandName);
            }
        }
        return cmds;
    }
    public function getCmdByDeviceID( id:Int):Array<Command>{
        var it:Iterator<Command> = _commands.iterator();
        var cmds:Array<Command> = new Array<Command>();

        if ( id == 0 ){
            while( it.hasNext()){
                var cmd:Command  = it.next();
                if ( cmd._deviceType == 0 ){
                    cmds.push(cmd);
                    trace("getCmdByDeviceID: " + cmd._commandName);
                }
            }
            return cmds;
        }

        var flag:Int = 0x1 << (id -1);
        while( it.hasNext()){
            var cmd:Command  = it.next();
            if ( ( cmd._deviceType & flag ) != 0 ) {
                cmds.push(cmd);
            }
        }
        return cmds;
    }

    public function createCmd( cmdName:String):Void{
        //trace("CommandMgr"+ cmdName+" len: "+cmdName.length);

        var conn:SMConnection  = cast(NetworkMgr.getInst().getConn());
        conn.clearData();
        conn.setMsg(11);
        conn.addKeyVal( "__OP__", Bytes.ofString("add_cmd"));
        conn.addKeyVal( "CMD", Bytes.ofString(cmdName));
        conn.sendData();
        conn.startListening( 12, onCreatedCmd);
    }

    function onCreatedCmd( datas:Hash<Bytes>):Void{
        if (NetworkMgr.responseTrue( datas) ){

            var ks:Iterator<String> = datas.keys();
            var id:Int = 0;
            var deviceType:Int= 0;
            var cmdName:String = "";
            while( ks.hasNext() ){
                var key:String = ks.next();
                //if ( key != "_result"){
                    if ( key.substr(0, 7) == "_CMD_ID"){
                        var sv:Bytes= datas.get( key);
                        id= NetworkMgr.bytes2Int(sv);
                        cmdName = key.substr( 7, key.length - 7 );
                        trace("key: "+key+ " val: "+id);
                    }
                    else if ( key.substr(0, 9) == "_CMD_TYPE"){
                        var sv:Bytes= datas.get( key);
                        deviceType = NetworkMgr.bytes2Int(sv);
                        trace("key: "+key+ " val: "+deviceType);
                    }
                    //}
            }
            new Command( id, cmdName, deviceType);
        }
    }

    static var inst:CommandMgr;
    inline public static function getInst():CommandMgr{
        if ( inst == null) {
            inst = new CommandMgr();
        }
        return inst;
    }
}

