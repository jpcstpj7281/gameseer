
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

    public var _col:Int;
    public var _row:Int;

    public var _width:Int;
    public var _height:Int;

    public var _resWidth:Int;
    public var _resHeight:Int;

    function new(){
        _screens =  new Array<Screen>();
        _col = 0;
        _row = 0;
        _width = _resWidth = 1024;
        _height = _resHeight = 768;
    }


    public function createColScreen( ):Array<Screen>{
        ++_col;
        if ( _col == 1  && _row == 0 ) _row = 1;
        _height = _resHeight * _row;
        _width = _resWidth*_col;

        var arr:Array<Screen> = new Array<Screen>();
        for ( i in 0..._row ){
            var c = new Screen( _col-1, i);
            _screens.push(c);
            arr.push(c);
        }

        return arr;
    }

    public function createRowScreen( ):Array<Screen>{
        ++_row;
        if ( _col == 0  && _row == 1 ) _col = 1;
        _height = _resHeight * _row;
        _width = _resWidth*_col;

        var arr:Array<Screen> = new Array<Screen>();
        for ( i in 0..._col ){
            var c = new Screen( i, _row-1);
            _screens.push(c);
            arr.push(c);
        }
        return arr;
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
