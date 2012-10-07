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
    public var _ringNodes:Array<RingNode>;
    public var _currRing:Ring;

    function new(){
        _rings=  new Array<Ring>();
        _ringNodes = new Array<RingNode>();
    }

    public function refreshRingNode(){
        for ( i in ScreenMgr.getInst()._screens){
            if ( ! hasRingNode( i._col, i._row) ){
                createRingNode( i._col, i._row , i );
            }
        }

        /////////////////////for test ring of out port 1////////
        if ( _rings.length == 0 ){
            _rings.push( new Ring() );
        }

        trace( _rings[0]._nodes.length);
        for ( i in _rings[0]._nodes.length..._ringNodes.length){
            _rings[0]._nodes.push( _ringNodes[i] );
            _ringNodes[i]._inport[0] = "1";
            _ringNodes[i]._outport[0] = "1";
            if ( i < _ringNodes.length -1){
                _ringNodes[i]._next[0] = _ringNodes[i+1];
            }else{
                _ringNodes[i]._next[0] = _ringNodes[0];
            }
        }
        _currRing = _rings[0];
        trace( _rings[0]._nodes.length);
        ///////////////////////////////////////////////////////
    }

    public function createRingNode( col:Int, row:Int, s:Screen){
        var r = new RingNode( col, row, s);
        s._ringNode = r;
        _ringNodes.push(r );
    }

    public function hasRingNode( col:Int, row:Int){
        for ( i in _ringNodes){
            if(i._col == col&& i._row == row){
                return true;
            }
        }
        return false;
    }

    public function isIncludedScreens(ss:Array<Screen>){
        var count:Int = 0;
        for ( i in _currRing._nodes){
            for ( s in ss){
                if ( i._col == s._col && i._row == s._row){
                    ++count;
                    break;
                }
            }
        }
        if ( count == ss.length) return true;
        else return false;
    }

    public function getCurrRingByScreens( s:Array<Screen>):Ring{
        if ( isIncludedScreens(s)){
            return _rings[0];
        }
        return null;
    }

    public function isRingInport( inport:String, s:Screen):Bool{
        for ( i in _ringNodes){
            if ( i._col == s._col && i._row == s._row){
                for ( p in i._inport){
                    if ( inport == p){
                        return true;
                    }
                }
            }
        }
        return false;
    }

}
