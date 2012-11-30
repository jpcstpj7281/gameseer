package com.merry.state;

import base.state.State;

import haxe.io.Bytes;

import haxe.Timer;
import base.state.StateMachine;

import base.ui.CommDialog;
import com.merry.ui.MainStage;

class InitMainState extends State{


    public function new(){
        super("InitMainState");
    }

    override function fromState(s:State):Void{
        MainStage.getInst().resetDlgs();
        MainStage.getInst().showListDialog();
    }

    override function run():Bool{
        return true;
    }

    override function toState(s:State):Void{
    }

}
