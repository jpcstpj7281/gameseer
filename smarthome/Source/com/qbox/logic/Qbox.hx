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

    var _initCounter:Int;
    var _cbInited:Void->Void;

    public function new(){
        super( "192.168.67.101", 5000);
        _version = "1.0";

        _inputs = new Hash<String>();
        _outputs = new Hash<String>();
        _initCounter = 0;
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
        _inputs = new Hash<String>();
        for ( i in 1...7){
            _inputs.set( ""+i, inputs.get("in"+i) );
            //trace("input: "+ inputs.get("in"+i));
        }
        loadInputsResolution();
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
        _outputs = new Hash<String>();
        for ( i in 1...5){
            _outputs.set( ""+i, outputs.get("out"+i) );
        }
        cbConnectedInit();
    }

    public function loadInputsResolution(){
        for ( i in 1...7){
            var tmp = _inputs.get( ""+i);
            if (tmp != "default"){
                clearData();
                startListening( 8, cbLoadInputsResolution, 1);
                setMsg( 7, 1);
                addKeyVal("in", Bytes.ofString(""+i));
                sendData();
                break;
            }
        }
    }

    function cbLoadInputsResolution( args:Dynamic){
        trace(args);
        var input = Std.parseInt(args.get("in") );
        while( input < 6){ 
            ++input;
            var tmp = _inputs.get( ""+input);
            if (tmp != "default"){
                clearData();
                startListening( 8, cbLoadInputsResolution, 1);
                setMsg( 7, 1);
                addKeyVal("in", Bytes.ofString(""+ input) );
                sendData();
                break;
            }
        }
        cbConnectedInit();
    }
    public function loadOutputsResolution( out:String){
        clearData();
        startListening( 10, cbLoadOutputsResolution, 1);
        setMsg( 9, 1);
        addKeyVal("out", Bytes.ofString(out));
        sendData();
    }

    function cbLoadOutputsResolution( args:Dynamic){
        trace(args);
        //var outputs:Hash<String> = cast args;
        //var total:Int = Std.parseInt( outputs.get("total"));
        //for ( i in 0...total ){
        //_outputs.set( "in"+i, outputs.get("in"+i) );
        //}
    }

    function cbConnectedInit():Void{
        --_initCounter;
        if (_initCounter==0){
            var tmp = _cbInited;
            _cbInited = null;
            tmp();
        }
    }

    public function connectedInit( cb:Void->Void):Bool{
        if (_initCounter>0){trace("_initCounter > 0");return false;}
        _cbInited = cb;

        _initCounter +=3;
        loadInput();
        loadOutput();
        closeAllWnd();
        return true;
    }

    function closeAllWnd(){
        clearData();
        startListening( 16, cbCloseAllWnd, 2);
        setMsg( 15, 2);
        sendData();
    }

    function cbCloseAllWnd( args:Dynamic){
        cbConnectedInit();
        trace(args);
    }

}
