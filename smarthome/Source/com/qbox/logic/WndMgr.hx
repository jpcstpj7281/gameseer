package com.qbox.logic;

import base.data.DataLoader;


class WndMgr {

    public static var inst:WndMgr;
    var _cbDone:Void->Void;
    inline public static function getInst():WndMgr{
        if ( inst == null) {
            inst = new WndMgr();
        }
        return inst;
    }



    //Array< Qbox>, container of Qboxes.
    public var _wnds:Array<Wnd>;

    public var _maxLayer:Int;
    public var _minLayer:Int;

    public function new(){
        _wnds =  new Array<Wnd>();
        _minLayer = 10;
        _maxLayer = 10;
    }

    public function setIfBiggerLayer( l:Int){
        if ( l > _maxLayer){
            _maxLayer = l;
        }
    }

    public function setExistedWndLayerMax(wnd:Wnd){
        if( wnd._layer < _maxLayer ){
            wnd._layer = _maxLayer+=1;
            _wnds.remove(wnd);
            _wnds.push(wnd);
        }
    }

    public function getWndsByChannel( c:Channel):Array<Wnd>{
        var wnds = new Array<Wnd>();
        for ( i in _wnds){
            if ( i._channel == c){
                wnds.push( i);
            }
        }
        return wnds;
    }

    public function createWnd( layer:Int = 0):Wnd{
        var c = new Wnd();
        if ( layer == 0) c._layer = _maxLayer+=1;
        else {
            c._layer = layer;
            for ( i in 0..._wnds.length){
                if ( layer < _wnds[i]._layer){
                    _wnds.insert( i, c);
                    trace("test");
                    return c;
                }
            }
        }
        trace("test");
        _wnds.push( c);
        return c;

        //var c = new Wnd();
        //c._layer = _maxLayer+=1;
        //_wnds.push( c);
        //return c;
    }

    inline public function removeWnd( wnd:Wnd):Void{ _wnds.remove(wnd); }
    public function closeAll( cb:Void->Void ):Void{ 
        _cbDone = cb;
        cbCloseAll(true);
    }

    function cbCloseAll( args):Void{
        var wnd:Wnd= null;
        if (_wnds!= null && _wnds.length > 0){
            wnd= _wnds[0];
            _wnds.remove(wnd);
        }

        if ( wnd==  null){
            var tmp = _cbDone;
            _cbDone = null;
            tmp();
            trace("closed all wnds");
            return;
        }

        trace("close wnd screen..."+ _wnds.length);
        wnd.close(cbCloseAll);
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
