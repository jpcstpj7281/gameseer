package com.qbox.logic;

import haxe.io.Bytes;


class RingNode{
    public var _col:Int;
    public var _row:Int;
    public var _next:RingNode;
    public var _pre:RingNode;
    public var _screen:Screen;

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

