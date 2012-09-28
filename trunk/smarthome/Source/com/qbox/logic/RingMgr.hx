package com.qbox.logic;

import base.data.DataLoader;


class RingMgr{

    public static var inst:RingMgr;
    inline public static function getInst():RingMgr{
        if ( inst == null) {
            inst = new RingMgr();
        }
        return inst;
    }

    //Array< Qbox>, container of Qboxes.
    public var _rings:Array<Ring>;

    function new(){
        _rings=  new Array<Ring>();
    }

}
