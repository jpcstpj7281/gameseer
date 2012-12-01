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

import com.qbox.logic.ModeMgr;
import com.qbox.logic.TaskMgr;

class InitMainState extends State{

    var q:Qbox;

    public function new(){
        super("InitMainState");
    }

    override function fromState(s:State):Void{
        ModeMgr.getInst();
        TaskMgr.getInst();
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
        /*
        if ( QboxMgr.getInst().loadQbox() == false){
            q = QboxMgr.getInst().createQbox();
            q._ipv4 = "127.0.0.1";
            q._port = 5000;
            QboxMgr.getInst().saveQbox();
        }
#if !neko
        QboxMgr.getInst().connectQboxes();
#end
*/
    }

    override function run():Bool{
        /*
#if !neko
        if ( QboxMgr.getInst().isAllConnected() ){
            //trace("connected: " + q._ipv4+ ":"+ q._port);
            QboxMgr.getInst().checkVersion();
            QboxMgr.getInst().loadInput();
            QboxMgr.getInst().loadOutput();
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
#end
*/
        return true;
    }

    override function toState(s:State):Void{
    }

}
