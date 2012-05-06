package com.pictionary.state;

import base.state.State;
import base.network.NetworkMgr;

import base.network.Connection;

import haxe.io.Bytes;

import haxe.Timer;
import base.state.StateMachine;
import com.pictionary.ui.MainStage;

class InitSocialState extends State{

    var _now:Float;
    var _pre:Float;

    public function new(){
        super("InitSocialState");
    }

    override function fromState(s:State):Void{

    }

    override function run():Bool{
        return true;
    }

    override function toState(s:State):Void{
    }

}
