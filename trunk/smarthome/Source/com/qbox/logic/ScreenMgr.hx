package com.qbox.logic;

import base.data.DataLoader;


class ScreenMgr extends QboxMgr {

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

    public var _width:Int;//real resolution
    public var _height:Int;//real resolution

    public var _resWidth:Int;
    public var _resHeight:Int;

    //virtual ui screen size;
    public var _virtualWidth:Int;//all screen virtual width
    public var _virtualHeight:Int;//all screen virtual height
    public var _virtualX:Int;
    public var _virtualY:Int;


    public var _circleCount:Int;

    function new(){
        _screens =  new Array<Screen>();
        _col = 0;
        _row = 0;
        _width = _resWidth = 1024;
        _height = _resHeight = 768;

        _circleCount = 0;

        super();
        //#if neko
        //++_col;
        //++_row;
        //var s = new Screen(0, 0);
        //s._resWidth = _resWidth;
        //s._resHeight= _resHeight;
        //insertToScreens(s);
        //#end
    }

    public function getFirstScreenByIP( ip:String):Screen{
        for ( i in _screens){
            if ( ip == i._ipv4){
                return i;
            }
        }
        return null;
    }

    public function getScreen( col:Int, row:Int, ip:String):Screen{
        for ( i in _screens){
            if ( col == i._col && row == i._row && ip == i._ipv4){
                return i;
            }
        }
        return null;
    }
    public function hasScreen( col:Int, row:Int, ip:String):Bool{
        return getScreen( col, row, ip) != null;
    }

    public function createSpecificScreen( col:Int, row:Int, ip:String ):Screen{
        if ( _col <= col) _col = col + 1;
        if ( _row <= row) _row = row + 1;

        var c = new Screen(col, row);
        c._resWidth = _resWidth;
        c._resHeight = _resHeight;
        c._ipv4 = ip;
        insertToScreens( c);
        RingMgr.getInst().refreshRingNode();
        return c;
    }

    public function createColScreen( ):Array<Screen>{
        ++_col;
        if ( _col == 1  && _row == 0 ) _row = 1;
        _height = _resHeight * _row;
        _width = _resWidth*_col;

        var arr:Array<Screen> = new Array<Screen>();
        for ( i in 0..._row ){
            var c = new Screen( _col-1, i);
            c._resWidth = _resWidth;
            c._resHeight = _resHeight;
            //_screens.push(c);
            insertToScreens( c);
            arr.push(c);
        }
        RingMgr.getInst().refreshRingNode();
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
            c._resHeight= _resHeight;
            //_screens.push(c);
            insertToScreens( c);
            arr.push(c);
        }
        RingMgr.getInst().refreshRingNode();
        return arr;
    }

    public function insertToScreens( s:Screen){
        for ( i in 0..._screens.length){
            var t = _screens[i];
            if ( s.isAfterOf( t) ){
                continue;
            }else{
                _screens.insert(i, s);
                return;
            }
        }
        _screens.push(s);

        recalcScreens();
    }

    public function recalcScreens(){
        var width:Int = nme.Lib.current.stage.stageWidth ;
        var height:Int = nme.Lib.current.stage.stageHeight - 180;

        var screenWidth = width/_col;
        var screenHeight = height/_row;
        if ( screenHeight > screenWidth *6/9){
            screenHeight = screenWidth *6/9;
        }
        if ( screenWidth> screenHeight *9/6){
            screenWidth= screenHeight *9/6;
        }
        _virtualWidth = cast screenWidth* _col;
        _virtualHeight = cast screenHeight* _row;

        for ( i in _screens){
            i._virtualHeight = cast screenHeight;
            i._virtualWidth = cast screenWidth;
        }
        _virtualX = Math.round( (width - screenWidth * _col) /2);
        _virtualY = 0;
    }

    //public function removeQbox( c:Screen){
    //for ( i in _screens){
    //if ( c == i ){
    //_screens.remove( i ) ;
    //break;
    //}
    //}
    //}

    //public function getScreenByQbox( qbox:Qbox){
    //for ( i in _screens){
    //if ( i._qbox == qbox){
    //return i;
    //}
    //}
    //return null;
    //}
}
