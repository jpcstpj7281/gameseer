package com.qbox.logic;

import base.data.DataLoader;


class WndMgr {

    public static var inst:WndMgr;
    inline public static function getInst():WndMgr{
        if ( inst == null) {
            inst = new WndMgr();
        }
        return inst;
    }



    //Array< Qbox>, container of Qboxes.
    public var _wnds:Array<Wnd>;


    public function new(){
        _wnds =  new Array<Wnd>();
    }

    public function createWnd():Wnd{
        var c = new Wnd();
        _wnds.push( c);
        return c;
    }

    public function removeQbox( c:Wnd){
        for ( i in _wnds){
            if ( c == i ){
                _wnds.remove( i ) ;
                break;
            }
        }
    }
}
