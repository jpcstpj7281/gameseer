package base.state;

import base.data.DataLoader;
import base.network.NetworkMgr;
import base.network.Connection;

class InitNetworkState extends State{


    public function new( ){
        super("InitNetworkState");
    }

    override function fromState(s:State):Void{

        if ( NetworkMgr.getInst().getConn() != null && NetworkMgr.getInst().getConn().isConected() ){
            var conn:Connection = NetworkMgr.getInst().getConn() ;
            conn.close();
            NetworkMgr.getInst().setConn(null);
        }
    }


    override function run():Bool{
        //return !(DataLoader.getInst().loadcouter_ == DataLoader.getInst().totalItem_);
        return false;
    }

    override function toState(s:State):Void{
    }
    
}
