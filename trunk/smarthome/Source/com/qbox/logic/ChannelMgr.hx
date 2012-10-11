package com.qbox.logic;

import base.data.DataLoader;


class ChannelMgr {

    public static var inst:ChannelMgr;
    inline public static function getInst():ChannelMgr{
        if ( inst == null) {
            inst = new ChannelMgr();
        }
        return inst;
    }



    //Array< Qbox>, container of Qboxes.
    public var _channels:Array<Channel>;
    public var _currSelected:Channel;


    public function new(){
        _channels =  new Array<Channel>();
#if neko
        var c = createChannel();
        c._w = 1024;
        c._h = 768;
        c._screen = ScreenMgr.getInst()._screens[0];
        c._inport = "3";
#end
    }

    public function createChannel():Channel{
        var c = new Channel(  );
        _channels.push( c);
        return c;
    }

    public function removeChannel( c:Channel){
        for ( i in _channels){
            if ( c == i ){
                _channels.remove( i ) ;
                break;
            }
        }
    }

    public function getChannelsWithOutRingPort( ):Array<Channel>{
        var isRingPort:Bool = false;
        var cs = new Array<Channel>();
        for ( c in _channels){
            isRingPort = false;
            for ( rg in RingMgr.getInst()._rings){
                for ( rn in rg._heads){
                    var n = rn;
                    while( n != null ){
                        if ( c._screen == n._screen ){
                            for ( i in n._inport){
                                if ( c._inport == i){
                                    isRingPort = true;
                                }
                            }
                        }
                        n = n._next[rg._nodeIndex];
                        if ( n == rn){
                            break;
                        }
                    }
                }
            }
            if ( isRingPort == false){
                cs.push( c);
            }
        }
        return cs;
    }
}
