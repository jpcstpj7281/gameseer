package com.blueseer.state;
import com.blueseer.device.DeviceMgr;
import base.state.State;
import com.blueseer.ui.UIMgr;


class InitUIState extends State{


    public function new( ){
        super("InitUIState");
    }


    override function fromState(s:State):Void{
        //UIMgr.getInst();
    }


    override function run():Bool{
        //return !(DataLoader.getInst().loadcouter_ == DataLoader.getInst().totalItem_);
        return false;
    }

    override function toState(s:State):Void{
    }
    
}
