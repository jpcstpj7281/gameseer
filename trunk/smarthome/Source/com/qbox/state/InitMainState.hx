package com.qbox.state;

import base.state.State;
import com.qbox.logic.QboxMgr;
import com.qbox.logic.Qbox;

import base.network.Connection;

import haxe.io.Bytes;

import haxe.Timer;
import base.state.StateMachine;
import com.qbox.ui.MainStage;
import com.qbox.logic.QboxMgr;

import base.ui.CommDialog;

class InitMainState extends State{

    var q:Qbox;

    public function new(){
        super("InitMainState");
    }

    override function fromState(s:State):Void{
        MainStage.getInst().resetDlgs();

        //if( q != null&& q.isConected()){
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


        q = QboxMgr.getInst().createQbox();
        q._ipv4 = "127.0.0.1";
        q._port = 5000;
        q.connect();
    }

    override function run():Bool{
        if(!q._isFailed && q.isConected()){
            trace("connected: " + q._ipv4+ ":"+ q._port);
#if !neko
            q.loadVersion();
#end
            return false;
        }
        else if ( !q.isConected() ){
            trace("connecting..." + q._ipv4);
            if ( q._isFailed ){
                trace("failed to connect " + q._ipv4 + ":" + q._port);
                //StateMachine.getInst().toState( "InitUnconnectedState");
                return false;
            }
        }
        return true;
    }

    override function toState(s:State):Void{
    }

}
