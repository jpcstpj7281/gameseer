package com.qbox.logic;



class QboxMgr {

    public static var inst:QboxMgr;
    inline public static function getInst():QboxMgr{
        if ( inst == null) {
            inst = new QboxMgr();
        }
        return inst;
    }



    //Array< Qbox>, container of Qboxes.
    public var _qboxes:Array<Qbox>;


    public function new(){
        _qboxes =  new Array<Qbox>();
    }

    public function createQbox():Qbox{
        var q = new Qbox();
        _qboxes.push( q);
        return q;
    }

    public function removeQbox( q:Qbox){
        for ( i in _qboxes ){
            if ( q == i ){
                _qboxes.remove( i ) ;
                break;
            }
        }
    }

}
