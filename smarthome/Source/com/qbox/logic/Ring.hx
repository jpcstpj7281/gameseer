package com.qbox.logic;

import haxe.io.Bytes;


class RingNode{
    public var _col:Int;
    public var _row:Int;
    public var _next:RingNode;
    public var _pre:RingNode;
    public var _screen:Screen;
}

class Ring{
    //only support ring out port 1 or ring out port 2 currently
    public function new( ringPort:Int){
    }

    public function isAfterOf( s:Screen):Bool{
        return false;
    }

}
