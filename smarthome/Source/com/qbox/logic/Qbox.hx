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


    public var _inputs:Hash<String>;
    public var _outputs:Hash<String>;

    public var _version:String;
    public function new(){
        super( "127.0.0.1", 5000);

        _inputs = new Hash<String>();
        _outputs= new Hash<String>();
        _version = "1.0";
    }

    public function loadVersion(){
        clearData();
        startListening( 2, cbVersion, 1);
        setMsg( 1, 1);
        sendData();
    }

    function cbVersion( args:Dynamic){
        _version = args.get("protocal");
    }

    public function loadInput(){
        clearData();
        startListening( 4, cbLoadInput, 1);
        setMsg( 3, 1);
        sendData();
    }

    function cbLoadInput( args:Dynamic){
        var inputs:Hash<String> = cast args;
        var total:Int = Std.parseInt( inputs.get("total"));
        for ( i in 0...total ){
            _inputs.set( "in"+i, inputs.get("in"+i) );
        }
    }

    public function loadOutput(){
        clearData();
        startListening( 6, cbLoadOutput, 1);
        setMsg( 5, 1);
        sendData();
    }

    function cbLoadOutput( args:Dynamic){
        var outputs:Hash<String> = cast args;
        var total:Int = Std.parseInt( outputs.get("total"));
        for ( i in 0...total ){
            _outputs.set( "in"+i, outputs.get("in"+i) );
        }
    }

    public function loadInputResolution(){
        clearData();
        startListening( 8, cbLoadInputResolution, 1);
        setMsg( 7, 1);
        sendData();
    }

    function cbLoadInputResolution( args:Dynamic){
        trace(args);
        //var outputs:Hash<String> = cast args;
        //var total:Int = Std.parseInt( outputs.get("total"));
        //for ( i in 0...total ){
        //_outputs.set( "in"+i, outputs.get("in"+i) );
        //}
    }
    public function loadOutputResolution(){
        clearData();
        startListening( 10, cbLoadOutputResolution, 1);
        setMsg( 9, 1);
        sendData();
    }

    function cbLoadOutputResolution( args:Dynamic){
        trace(args);
        //var outputs:Hash<String> = cast args;
        //var total:Int = Std.parseInt( outputs.get("total"));
        //for ( i in 0...total ){
        //_outputs.set( "in"+i, outputs.get("in"+i) );
        //}
    }

    public function connectedInit():Bool{
        loadInput();
        //loadOutput();
        return true;
    }
}
