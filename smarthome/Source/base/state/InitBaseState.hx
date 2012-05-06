package base.state;
import base.state.State;

import base.network.NetworkMgr;
import base.network.Connection;
import base.network.SMConnection;

class InitBaseState extends State{


    public function new( ){
        super("InitBaseState");
    }


    override function fromState(s:State):Void{

        if ( NetworkMgr.inst.getConn() == null || NetworkMgr.getInst().getConn().isConected() == false ){
            var conn:SMConnection = new SMConnection( base.conf.Config.connIP);
            conn.connect();
            NetworkMgr.inst.setConn( conn);
        }
    }


    override function run():Bool{
        if(!NetworkMgr.inst.getConn()._isFailed && NetworkMgr.inst.getConn().isConected()){
            trace("connected: " + NetworkMgr.getInst().getConn()._ipv4+ ":"+ NetworkMgr.getInst().getConn()._port);
            return false;
        }
        else if ( !NetworkMgr.inst.getConn().isConected() ){
            trace("connecting..." + NetworkMgr.inst.getConn()._ipv4);
            if ( NetworkMgr.inst.getConn()._isFailed ){
                trace("failed to connect " + NetworkMgr.inst.getConn()._ipv4);
                StateMachine.getInst().toState( "InitUnconnectedState");
                return false;
            }
        }
        return true;
        //return false;
    }

    override function toState(s:State):Void{
    }



}
