package com.blueseer.state;

import com.blueseer.device.DeviceMgr;
import base.network.SMConnection;
import base.state.State;
import base.network.NetworkMgr;


import com.blueseer.cmd.Command;
import com.blueseer.device.Device;
import com.blueseer.ui.UIMgr;
import haxe.Timer;

class InitUnconnectedState extends State{


    var _now:Float;
    var _pre:Float;

    public function new(){
        super("InitUnconnectedState");
        _now = _pre = Timer.stamp();
    }

    override function fromState(s:State):Void{
        UIMgr.getInst().resetDlgs();
        UIMgr.getInst().showListDialog();
    }


    override function run():Bool{

        if(NetworkMgr.inst.getConn().isConected()){
            trace("connected!");
            base.state.StateMachine.getInst().toState( "InitDeviceState");
            return false;
        }
        /*
        else {
            _now = Timer.stamp();
            if ( _now - _pre < 60){
                return true;
            }
            _pre = _now;
            trace("connecting..." + NetworkMgr.inst.getConn()._ipv4);
            if ( NetworkMgr.inst.getConn()._isFailed ){
                trace("failed to connect " + NetworkMgr.inst.getConn()._ipv4);
                trace("try again");
                var conn = new SMConnection(NetworkMgr.inst.getConn()._ipv4);
                conn.connect();
                NetworkMgr.inst.setConn(conn );
                //if(NetworkMgr.inst.getConn().isConected()){
                //trace("connected!");
                //return false;
                //}
                return true;
            }
        }
        */
        return true;
    }

    override function toState(s:State):Void{
    }

}
