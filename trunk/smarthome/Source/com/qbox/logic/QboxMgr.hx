package com.qbox.logic;

import base.data.DataLoader;


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

    public function getQboxByIp( ip:String):Qbox{
        for ( i in _qboxes){
            if ( i._ipv4 == ip ){
                return i;
            }
        }
        return  null;
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

    public function connectQboxes(){
        for ( i in _qboxes){
            i.connect();
        }
    }

    public function isAllConnected():Bool{
        for ( q in _qboxes){
           if(q._isFailed && !q.isConected()){
               return false;
           }
        }
        return true;
    }

    public function checkVersion():Bool{
        for ( q in _qboxes){
            q.loadVersion();
        }
        return true;
    }

    public function loadInput():Void{
        for ( q in _qboxes){
            q.loadInput();
        }
    }
    public function loadOutput():Void{
        for ( q in _qboxes){
            q.loadOutput();
        }
    }
    public function loadInputResolution():Void{ 
        _qboxes[0].loadInputsResolution();
    }
    public function loadOutputResolution():Void{ 
        _qboxes[0].loadOutputsResolution("out0");
    }

    public function loadQbox(){
        var str:String = DataLoader.getInst().getData( "qboxes"); 
        if ( str == null || str.length <= 1) return false;
        var arr:Array<String> = str.split(";");
        for ( i in arr){
            if ( i.length == 0 ) continue;
            var a2 = i.split(":");
            //trace(a2[0]);
            //trace(a2[1]);
            var q = createQbox();
            q._ipv4 = a2[0];
            q._port = Std.parseInt(a2[1]);
        }
        return true;
    }

    public function saveQbox(){ 
        var buf:StringBuf = new StringBuf();
        for ( q in _qboxes){
            buf.add(q._ipv4);
            buf.add(":");
            buf.add(q._port);
            buf.add(";");
        }
        DataLoader.getInst().saveDynamicData( "qboxes", buf.toString()); 
    }

}
