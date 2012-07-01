package com.qbox.logic;

import base.network.SMConnection;
import flash.utils.ByteArray;

import haxe.io.BytesBuffer;
import haxe.io.Bytes;

import nme.events.Event;
import haxe.Timer;
import base.network.NetworkMgr;
import base.state.StateMachine;

class Qbox extends SMConnection{


    public function new(){
        super( "127.0.0.1", 5000);
    }

    public function loadVersion(){
        clearData();
        startListening( 2, cbVersion, 1);
        setMsg( 1, 1);
        sendData();
    }

    function cbVersion( args:Dynamic){
        trace(args);
    }

}
