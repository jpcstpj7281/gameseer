package com.qbox.logic;

import haxe.io.Bytes;


class Ring{

    public var _nodes:Array<RingNode>;
    public var _nodeIndex:Int;
    public var _isRingSetup:Bool;
    public var _count:Int;
    public var _cb:Dynamic->Void;


    //only support ring out port 1 or ring out port 2 currently
    public function new( ){
        _nodes = new Array<RingNode>();
        _nodeIndex = 0;
        _isRingSetup = false;
        _count = 0;
    }


    public function isAvailable():Bool{
        for ( i in _nodes){
        }

        return true;
    }

    public function setupRing( wnd:Wnd, cb:Dynamic->Void){
        for ( i in _nodes){
#if !neko
            if(i._screen.isConected() == false){
                trace("there is a qbox not yet connected: "+ i._screen._ipv4);
                break;
            }
#end

            i._screen.setChannel( i._outport[_nodeIndex], i._inport[_nodeIndex], cbSetupRing, wnd);
            ++_count;
        }
        _isRingSetup = true;
    }

    function cbSetupRing( args:Dynamic, s:Screen){
        _isRingSetup = true;
        if ( args.get("error") == "1") {
            trace("there is a error occurred at qbox: "+ s._ipv4);
            _cb("error");
            return;
        }
        --_count;
        if (_count == 0){
            _cb("");
        }
    }

    public function getScreens():Array<Screen>{
        var ss = new Array<Screen>();
        for ( i in _nodes){
            ss.push(i._screen);
        }
        return ss;
    }
}
