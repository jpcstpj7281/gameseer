package com.qbox.logic;

import haxe.io.Bytes;


class Ring{

    public var _heads:Array<RingNode>;
    public var _nodeIndex:Int;
    public var _isRingSetup:Bool;
    public var _count:Int;
    public var _cbRingSetup:Dynamic->Void;
    public var _cb753Setup:Dynamic->Void;


    //only support ring out port 1 or ring out port 2 currently
    public function new( index:Int){
        _heads = new Array<RingNode>();
        _nodeIndex = index;
        _isRingSetup = false;
        _count = 0;
    }

    public function setupRing(c:Channel, wnd:Wnd, cb:Dynamic->Void){
        if ( _count > 0) {trace("_count:"+_count);return ;}
        if ( _cbRingSetup != null) { trace("_cbRingSetup not null!");return;}

        var rns = new Array<RingNode>();
        for ( i in _heads){
            //trace( "test");
            var n = i;
            while (n !=null ){
                rns.push( n);
                n = n._next[_nodeIndex];
                if ( n == i){
                    break;
                }
            }
        }
        _cbRingSetup = cb;
        _count += rns.length;
        //trace(_count);
        for ( n in rns){
            trace( "set ring of qbox: "+ n._screen._ipv4);
            if ( c._screen == n._screen){
                n._screen.setRingChannel( n._outport[_nodeIndex], c._inport, cbSetupRing, wnd);
            }else{
                n._screen.setRingChannel( n._outport[_nodeIndex], n._inport[_nodeIndex], cbSetupRing, wnd);
            }
        }
        _isRingSetup = true;
    }

    function cbSetupRing( args:Dynamic, s:Screen){
        if ( args.get("error") == "1") {
            trace("there is a error occurred at qbox: "+ s._ipv4);
            trace( args);
            _cbRingSetup("error");
            _cbRingSetup = null;
            return;
        }
        --_count;
        if (_count == 0){
            var tmp = _cbRingSetup;
            _cbRingSetup = null;
            tmp(null);
        }
    }

    public function setup753( wnd:Wnd, ss:Array<Screen>, c:Channel,  cb:Dynamic->Void):Bool{
        if ( _count > 0) {trace("_count:"+_count);return false ;}
        if ( _cb753Setup!= null) { trace("_cb753Setup not null!");return false;}

        for ( i in ss){
            if ( isInRing(i) == false )  {
                trace("not in ring: "+ i._ipv4);
                return false;
            }
            if ( !i.has753Available() ){
                trace("not 753 available: "+ i._ipv4);
                return false;
            }
        }

        _cb753Setup= cb;
        _count += ss.length;
        for (i in ss){
            if ( i == c._screen){
                i.set753Channel( c._inport, cbSetup753, wnd);
            }else{
                i.set753Channel( i._ringNode._inport[_nodeIndex] , cbSetup753, wnd);
            }
        }
        return true;
    }

    function cbSetup753( args:Dynamic, s:Screen){
        if ( args.get("error") == "1") {
            trace("there is a error occurred at qbox: "+ s._ipv4);
            trace( args);
            _cb753Setup("error");
            _cb753Setup= null;
            return;
        }
        --_count;
        if (_count == 0){
            var tmp = _cb753Setup;
            _cb753Setup= null;
            tmp(null);
        }
    }
    public function getScreens( c:Channel):Array<Screen>{
        var ss = new Array<Screen>();
        for ( i in _heads){
            var n = i;
            var circlePoint:RingNode =  null;
            while ( n != circlePoint){
                if ( n._screen == c._screen){
                    circlePoint = n;
                }
                if ( circlePoint != null) ss.push(i._screen);
                n = n._next[_nodeIndex];
                if ( n == i && circlePoint == null ) break;
            }
        }
        return ss;
    }

    public function isHead( rn:RingNode){
        for ( i in _heads){
            if (rn == i){
                return true;
            }
        }
        return false;
    }

    public function getRingHead( col:Int, row:Int):RingNode{
        for ( i in _heads){
            if ( col == i._col && row == i._row){
                return i;
            }
        }
        return null;
    }

    public function isInRing( s:Screen):Bool{
        if ( _heads.length == 0 ) return false;
        //trace(_heads.length);
        for ( rn in _heads){
            var n = rn;
            while (n !=null ){
                //trace(n._col);
                //trace(n._row);
                if ( n._screen == s){
                    return true;
                }
                n = n._next[_nodeIndex];
                if ( n == rn){
                    break;
                }
            }
        }
        //trace("done");
        return false;
    }

    public function newHead( rn:RingNode){
        //trace( rn._col);
        //trace( rn._row);
        var tmp = rn._pre[_nodeIndex];
        while(tmp != rn){
            if ( tmp == null){ tmp = rn;break; }
            tmp = tmp._pre[_nodeIndex];
        }
        eatHead( tmp);
        _heads.push( tmp);
        //trace( _heads.length);
    }

    public function eatHead( rn:RingNode){
        var ate = new Array<RingNode>();
        for ( i in _heads){
            var next = rn;
            while( next != null ){
                if ( i == next){
                    ate.push(i);
                    break;
                }
                next = next._next[_nodeIndex];
                if (next == rn){
                    break;
                }
            }
        }

        for ( i in ate){
            _heads.remove(i);
        }
    }

    public function isCircled( head:RingNode):Bool{
        var tmp = head._next[_nodeIndex];
        var isCir= true;
        while( tmp != head){
            if ( tmp == null){
                isCir= false;
                break;
            }
            tmp = tmp._next[_nodeIndex];
        }
        return isCir;
    }
}
