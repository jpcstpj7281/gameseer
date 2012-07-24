
package com.qbox.logic;

import base.data.DataLoader;


class ScreenMgr {

    public static var inst:ScreenMgr;
    inline public static function getInst():ScreenMgr{
        if ( inst == null) {
            inst = new ScreenMgr();
        }
        return inst;
    }



    //Array< Qbox>, container of Qboxes.
    public var _screens:Array<Screen>;


    public function new(){
        _screens =  new Array<Screen>();
    }

    public function createScreen():Screen{
        var c = new Screen();
        _screens.push( c);
        return c;
    }

    public function removeQbox( c:Screen){
        for ( i in _screens){
            if ( c == i ){
                _screens.remove( i ) ;
                break;
            }
        }
    }
}
