package com.qbox.state;

import base.state.State;
import base.network.NetworkMgr;

import base.network.Connection;

import haxe.io.Bytes;

import haxe.Timer;
import base.state.StateMachine;
import com.qbox.ui.MainStage;

import base.ui.CommDialog;

class InitMainState extends State{

    public function new(){
        super("InitMainState");
    }

    override function fromState(s:State):Void{
        MainStage.getInst().resetDlgs();

        //if( NetworkMgr.getInst().getConn() != null&& NetworkMgr.getInst().getConn().isConected()){
        //var d = MainStage.getInst().getSpecificDialog("连接",0);
        //if( d!= null){
        //var cd:CommDialog  = cast( d);
        //cd.onMouseClick();
        //trace("opened connection drawing");
        //return;
        //}
        //trace("failed opene connection drawing");
        //}
        MainStage.getInst().showListDialog();
    }

    override function run():Bool{
        return true;
    }

    override function toState(s:State):Void{
    }

}
