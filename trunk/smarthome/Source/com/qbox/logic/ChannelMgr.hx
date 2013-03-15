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
    }

    public function removeChannelByScreen( sn:Screen){
        var cs = new Array<Channel>();
        for ( i in _channels){
            if ( i._screen == sn ){
                cs.push( i );
            }
        }
        for ( i in cs){
            _channels.remove(i);
        }
    }
    public function removeChannelByScreenInport( sn:Screen, inport:String){
        for ( i in _channels){
            if ( i._screen == sn && i._inport == inport){
                _channels.remove(i);
                break;
            }
        }
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

    inline public function hasChannel( ip:String, inport:String, w:Int, h:Int, col:Int, row:Int):Bool{
        return getChannel( ip, inport, w, h, col, row) != null;
    }
    public function getChannel( ip:String, inport:String, w:Int, h:Int, col:Int, row:Int):Channel{
        for ( i in _channels){
            if( i._screen != null && i._screen._ipv4 == ip && i._screen._col == col && i._screen._row == row && i._inport == inport && i._w == w && i._h == h){
                return i;
            }
        }
        return null;
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
                        //if ( c._screen == n._screen ){
                        if ( n._pre[rg._nodeIndex] != null && c._screen == n._screen ){
                            for ( i in n._inport){
                                if ( c._inport == i){
                                    isRingPort = true;
                                    trace(n._screen._ipv4);
                                    trace(i);
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
