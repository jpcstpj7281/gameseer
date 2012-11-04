package com.qbox.logic;


class Channel{

    public var _w:Int;
    public var _h:Int;
    public var _inport:String;
    public var _screen:Screen;
    public var _ring:Ring;


    public function new(){
    }

    public function isRingOfChannel( rg:Ring, sn:Screen):Bool{
        var rn = _screen._ringNode;
        while( rn != null){
            if ( rn._screen == sn){
                return true;
            }

            rn = rn._next[rg._nodeIndex];
            if ( rn == _screen._ringNode){
                break;
            }
        }
        return false;
    }

}
