package base.state;

import base.conf.Config;

class LoadConfState extends State{


    public function new( ){
        super("LoadConfState");
    }

    override function fromState(s:State):Void{
        Config.getInst().loadConf(null);
        _isRunning = true;

    }

    override function run():Bool{
        return !Config.getInst().isLoaded_;
    }

    override function toState(s:State):Void{
    }
    
}
