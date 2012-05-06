package base.state;

import base.state.State;
import haxe.Timer;
import base.state.StateMachine;
import com.pictionary.ui.MainStage;

import base.ui.CommDialog;

class InitSocialState extends State{

    public function new(){
        super("InitSocialState");
    }

    override function fromState(s:State):Void{
    }

    override function run():Bool{
        if( base.social.SocialMgr.getInst().isInitialized() ){
            return false;
        }
        return true;
    }

    override function toState(s:State):Void{
    }

}
