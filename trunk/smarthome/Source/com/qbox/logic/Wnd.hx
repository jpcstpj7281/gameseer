
package com.qbox.logic;


class Wnd{

    //var _x:Int;
    //var _y:Int;
    //var _w:Int;
    //var _h:Int;

    public var _screens:Array<Screen>;
    public var _handles:Array<String>;

    public var _virtualX:Int;
    public var _virtualY:Int;
    public var _virtualWidth:Int;
    public var _virtualHeight:Int;

    public var _channel:Channel;

    public var _opCounter:Int;

    public function new(){
        //_x = 0;
        //_y = 0;
        //_w = cast ScreenMgr.getInst()._width*0.6;
        //_h = cast ScreenMgr.getInst()._height*0.6;
        _screens= new Array<Screen>();
        _handles= new Array<String>();
        _opCounter= 0;
    }

    public function open(x:Int, y:Int, w:Int, h:Int, channel:Channel){
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualX = x;
        _virtualY = y;
        _virtualWidth = w;
        _virtualHeight = h;
        _channel =  channel;
        for (i in ScreenMgr.getInst()._screens){ 
            ++_opCounter;
            i.setWnd( x,y,w,h, cbSetWnd); 
        }
        return true;
    }

    function cbSetWnd( args:Dynamic, s:Screen):Void{
        var error = args.get("error" );
        if (error == "1") { return; }
        var handle = args.get("winHandle" );
        //trace(s);
        //trace(handle);
        _screens.push( s);
        _handles.push( handle);
        if ( handle != "null"){
            ++_opCounter;
            s.setChannel( handle, _channel,  cbSetChannel);
        }
        --_opCounter;
    }

    function cbSetChannel( args:Dynamic, s:Screen):Void{
        var error = args.get("error");
        if (error == "1") { return; }
        for ( i in 0..._screens.length){
            if ( _screens[i] == s ){
                if ( _handles[i] != "null"){
                    ++_opCounter;
                    s.showWnd( _handles[i], cbShowWnd );
                }
            }
        }
        --_opCounter;
    }

    function cbShowWnd( args:Dynamic){
        --_opCounter;
        trace("show window: "+ args);
    }

    public function move( x:Int, y:Int){
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualX = x;
        _virtualY = y;
        for (i in 0..._screens.length){ 
            //trace(_screens[i]);
            ++_opCounter;
            _screens[i].closeWnd( _handles[i], cbCloseBeforeOpenWnd); 
        }
        return true;
    }

    function cbCloseBeforeOpenWnd( args:Dynamic, s:Screen){
        _screens = new Array<Screen>();
        _handles= new Array<String>();
        --_opCounter;
        open(_virtualX, _virtualY, _virtualWidth, _virtualHeight, _channel);
    }

    //function cbMoveWnd( args:Dynamic, s:Screen){
    //var error = args.get("error" );
    //if (error == "1") { return; }
    //var handle = args.get("winHandle" );
    ////trace(handle);
    //_screens.push( s);
    //_handles.push( handle);
    //s.showWnd( handle, cbShowWnd);
    //}

    public function resize( w:Int, h:Int){
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualHeight = h;
        _virtualWidth = w;
        for (i in 0..._screens.length){ 
            ++_opCounter;
            _screens[i].closeWnd( _handles[i], cbCloseBeforeOpenWnd); 
        }
        return true;
    }

    //WndDlg will invoke this
    public function reset(x:Int, y:Int, w:Int, h:Int){
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualX = x;
        _virtualY = y;
        resize(w, h);
        return true;
    }
    public function close(){
        //var ss = ScreenMgr.getInst()._screens;
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        for (i in 0..._screens.length){ 
            ++_opCounter;
            _screens[i].closeWnd( _handles[i], cbCloseWnd); 
        }
        return true;
    }
    function cbCloseWnd( args:Dynamic, s:Screen){
        var error = args.get("error" );
        if (error == "1") { trace("close wnd failed");return; }
        else trace("close wnd succeed");
        --_opCounter;
    }

}
