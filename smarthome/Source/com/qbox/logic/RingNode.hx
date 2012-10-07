package com.qbox.logic;

import haxe.io.Bytes;


class RingNode{
    public var _col:Int;
    public var _row:Int;
    public var _next:Array<RingNode>;
    public var _pre:Array<RingNode>;
    public var _inport:Array<String>;
    public var _outport:Array<String>;
    public var _screen:Screen;

    public function new ( col:Int, row:Int, screen:Screen){
        _col = col;
        _row = row;
        _screen = screen;
        _next = new Array<RingNode>();
        _pre = new Array<RingNode>();
        _inport = new Array<String>();
        _outport = new Array<String>();
    }

    public function isAfter( s:RingNode):Bool{
        if (_col >= s._col){
            if ( _row>= s._row){
                return true;
            }
        }else if ( _row> s._row){
            return true;
        }
        return false;
    }
}

