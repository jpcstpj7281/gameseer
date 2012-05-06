package com.blueseer.state;

import com.blueseer.device.DeviceMgr;
import com.blueseer.cmd.CommandMgr;
import base.network.SMConnection;
import base.state.State;
import base.network.NetworkMgr;

import base.network.Connection;

import com.blueseer.cmd.Command;
import com.blueseer.device.Device;
import com.blueseer.ui.UIMgr;
import haxe.io.Bytes;

import haxe.Timer;
import base.state.StateMachine;

class InitDeviceState extends State{

    var _now:Float;
    var _pre:Float;
    var _waitForPong:Bool;
    var _isDataLoaded:Bool;

    public function new(){
        super("InitDeviceState");
        //_now = _pre = Timer.stamp();
        _waitForPong = false;
        _isDataLoaded = false;
    }

    override function fromState(s:State):Void{
        CommandMgr.getInst().clear();
        DeviceMgr.getInst().clear();
        _isDataLoaded = false;

        var conn:SMConnection  = cast(NetworkMgr.getInst().getConn());
        conn.startListening( 12, onLoadDevices);
        conn.clearData();
        conn.setMsg(11);
        conn.addKeyVal( "__OP__", Bytes.ofString("load_all_devices"));
        conn.sendData();
        //var datas:Hash<String> = conn.response();

        //var conn:SMConnection  = cast(NetworkMgr.getInst().getConn());
        //var datas:Hash<String> =  conn.response() ;

        //trace("test1");
        //trace("test3");
        //_now = Timer.stamp();
        //_pre = _now - 30;
    }

    function onLoadDevices( datas:Hash<String> ):Void{
        if ( datas != null ){
            var ks:Iterator<String> = datas.keys();
            while( ks.hasNext() ){
                var key:String = ks.next();
                if ( key.substr(0, 1) != "_" ){
                    var sv:String = datas.get( key);
                    var val:Int = NetworkMgr.str2Int(sv);
                    new Device( val, key);
                    //trace("key: "+key+ " val: "+val);
                }
            }
        }

        var conn:SMConnection  = cast(NetworkMgr.getInst().getConn());
        conn.startListening( 12, onLoadCmds);
        conn.clearData();
        conn.setMsg(11);
        conn.addKeyVal( "__OP__", Bytes.ofString("load_all_cmds"));
        conn.sendData();
    }
    function onLoadCmds( datas:Hash<String> ):Void{
        if ( datas != null && datas.get("_result") == "true" ){

            var ks:Iterator<String> = datas.keys();
            var cmdName:String;
            var id:Int = 0;
            var deviceType:Int= 0;
            while( ks.hasNext() ){
                var key:String = ks.next();
                if ( key.substr(0, 2) != "__" && key != "_result" ){
                    if ( key.substr(0, 7) == "_CMD_ID"){
                        cmdName = key.substr( 7, key.length);
                        var sv:String = datas.get( key);
                        id= NetworkMgr.str2Int(sv);
                        //trace("key: "+key+ " val: "+id);
                        var devTypeid:String = "_CMD_TYPE"+cmdName;
                        sv = datas.get( devTypeid);
                        deviceType = NetworkMgr.str2Int(sv);
                        //trace("devType: "+devTypeid+ " val: "+deviceType);
                        new Command( id, cmdName, deviceType);
                    }
                }
            }
        }
        //trace("loaded all");
        UIMgr.getInst().resetDlgs();
        UIMgr.getInst().showListDialog();
        //trace("inited ui");
        _isDataLoaded = true;
    }
    
    function onPong( datas:Hash<String>):Void{
        trace( "pong");
    }

    override function run():Bool{
        if (_isDataLoaded == false) return true;
        if(!NetworkMgr.inst.getConn()._isFailed && NetworkMgr.inst.getConn().isConected()){

            var conn:SMConnection  = cast(NetworkMgr.getInst().getConn());
            if ( Timer.stamp() - conn._sendTime >= 60){
                conn.ping( onPong);
            }
        }
        else if ( !NetworkMgr.inst.getConn().isConected() ){
            trace("connection broken: " + NetworkMgr.inst.getConn()._ipv4+ " try to reconnect!" );
            StateMachine.getInst().toState( "InitBaseState");
            if ( NetworkMgr.getInst().getConn() != null && NetworkMgr.getInst().getConn().isConected() ){
                var conn:Connection = NetworkMgr.getInst().getConn() ;
                conn.close();
                NetworkMgr.getInst().setConn(null);
            }
            return false;
        }
        return true;
    }

    override function toState(s:State):Void{
    }

}
