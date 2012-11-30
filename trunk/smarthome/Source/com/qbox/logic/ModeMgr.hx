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
        while(true){
            var c = new Mode(_modes.length);
            if( c.hasData()){
                _modes.push( c);
            }
            else{
                break;
            }
        }
    }

    public function deleteMode( m:Mode):Void{
        for ( i in m._id..._modes.length){
            DataLoader.getInst().saveData( "mode"+_modes[i]._id, null);
            -- _modes[i]._id;
            _modes[i].save();
        }
        _modes.remove(m);
    }

    public function createMode():Mode{
        var data:String = null;
        if ( _modes.length>0){
            var m = _modes[_modes.length-1];
            data = DataLoader.getInst().getData( "mode"+ m._id );
        }
        var c = null;
        if ( data != null || _modes.length == 0){
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
