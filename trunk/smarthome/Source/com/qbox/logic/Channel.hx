package com.qbox.logic;


class Channel{

    public var _name:String;

    public var _nodes:Array<String>;

    public function new(name:String){
        _name = name;
        _nodes = new Array<String>();
    }

    public function addNode( q:Qbox, input:String){
        _nodes.push( q._ipv4 + ":" + input);
    }
}
