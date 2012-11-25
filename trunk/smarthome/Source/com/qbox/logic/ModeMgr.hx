package com.qbox.logic;

import base.data.DataLoader;


class ModeMgr{

    public static var inst:ModeMgr;
    inline public static function getInst():ModeMgr{
        if ( inst == null) {
            inst = new ModeMgr();
        }
        return inst;
    }

    //Array< Qbox>, container of Qboxes.
    public var _modes:Array<Mode>;

    public function new(){
        _modes =  new Array<Mode>();
        //trace(data);
        var count:Int = 0;
        while(true){
            var data = DataLoader.getInst().getData( "mode"+count++ );
            if ( data != null){
                var c = new Mode(_modes.length);
                _modes.push( c);
                c.load(data);
            }else{
                break;
            }
        }
    }

    public function createMode():Mode{
        var data:String = null;
        if ( _modes.length>0){
            var m = _modes[_modes.length-1];
            data = DataLoader.getInst().getData( "mode"+ m._id );
        }
        var c = null;
        if ( data != null){
            c = new Mode(_modes.length);
            _modes.push( c);
        }
        return c;
    }
    public function saveData(){
        for ( i in _modes){
            i.save();
        }
    }

    inline public function removeMode( Mode:Mode):Void{ _modes.remove(Mode); }
    public function closeAll( ):Void{ 
        for ( i in _modes){
            i.close();
            removeMode(i);
        }
    }

    public function removeQbox( c:Mode){
        for ( i in _modes){
            if ( c == i ){
                _modes.remove( i ) ;
                break;
            }
        }
    }
}
