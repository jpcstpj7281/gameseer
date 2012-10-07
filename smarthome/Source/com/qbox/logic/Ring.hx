package com.qbox.logic;

import haxe.io.Bytes;


class Ring{

    public var _nodes:Array<RingNode>;
    public var _nodeIndex:Int;


    //only support ring out port 1 or ring out port 2 currently
    public function new( ){
        _nodes = new Array<RingNode>();
        _nodeIndex = 0;
    }

    public function getScreens():Array<Screen>{
        return null;
    }

    public function isAvailable():Bool{
        for ( i in _nodes){
        }

        return true;
    }
}
