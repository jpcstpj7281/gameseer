
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

    var _channel:Channel;
    public var _ring:Ring;

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

    public function open(x:Int, y:Int, w:Int, h:Int, channel:Channel, ring:Ring){
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualX = x;
        _virtualY = y;
        _virtualWidth = w;
        _virtualHeight = h;
        _channel =  channel;
        _ring = ring;

        _screens = new Array<Screen>();
        for (i in ScreenMgr.getInst()._screens){ 
            if ( ! i.isOutOfScreen( x,y,w,h)){ 
                _screens.push(i);
            }
        }

#if !neko
        for ( i in _screens){
            if ( ! i.isConected() ){
                trace("screen: " + i._ipv4 +" not yet connect");
                return false;
            }
            if ( ! i.has753Available()){
                trace("screen: "+ i._ipv4 +" dont have resource to open window!");
                return false;
            }
        }

        if ( ring != null && ring._isRingSetup == false){
            //ScreenMgr.getInst().setRing(ring);
            //trace(ring);
            ring.setupRing( this, cbRingSetup);
        }else{
            _opCounter+=_screens.length;
            for (i in _screens){
                i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbSetWnd, this);
            }
        }
#else
        //trace(screens.length);
        //trace(_screens.length);
        //trace(channel == null);
        //trace(ring == null);
        _opCounter += _screens.length;
        for (i in _screens){
            i.setWnd( x,y,w,h, cbSetWnd, this);
        }
        //trace(screens.length);
#end
        return true;
    }

    function cbRingSetup( args:Dynamic){
        //var screens:Array<Screen> = new Array<Screen>();
        //for (i in ScreenMgr.getInst()._screens){ 
        //if ( ! i.isOutOfScreen( _virtualX,_virtualY,_virtualWidth,_virtualHeight)){ 
        //screens.push(i);
        //}
        //}
        _opCounter+=_screens.length;
        for (i in _screens){
            i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbSetWnd, this);
        }
    }

    function cbSetWnd( args:Dynamic, s:Screen):Void{
        var error = args.get("error" );
        if (error == "1") { trace( "There is a error occurred: "+s._ipv4+"!");return; }
        var handle = args.get("winHandle" );
        //trace(s._col);
        //trace(handle);
        //trace(_screens.length);
        //_screens.push( s);
        //_handles.push( handle);
        //if ( handle != "null"){
        //++_opCounter;
        //s.setChannel( handle, _channel,  cbSetChannel);
        //for ( i in 0..._screens.length){
        //if ( _screens[i] == s ){
        if ( handle != "null"){
            //trace(_screens[i]);
            //trace(_handles[i]);
            ++_opCounter;
            s.showWnd( handle, cbShowWnd );
        }
        //}
        //}
        //}
        //trace(_screens.length);
        --_opCounter;
    }

    //function cbSetChannel( args:Dynamic, s:Screen):Void{
    //var error = args.get("error");
    //if (error == "1") { return; }
    //for ( i in 0..._screens.length){
    //if ( _screens[i] == s ){
    //if ( _handles[i] != "null"){
    //++_opCounter;
    //s.showWnd( _handles[i], cbShowWnd );
    //}
    //}
    //}
    //--_opCounter;
    //}

    function cbShowWnd( args:Dynamic){
        --_opCounter;
        trace("show window: "+ args);
    }

    public function move( x:Int, y:Int):Bool{
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualX = x;
        _virtualY = y;
        //trace(_screens.length);
        //trace(_handles.length);
        _opCounter+=_screens.length;
        for (i in 0..._screens.length){
            //trace(_screens);
            //trace(_screens[i]);
            _screens[i].closeWnd( _handles[i], cbCloseBeforeOpenWnd, this);
            //trace(_screens.length);
        }
        return true;
    }

    function cbCloseBeforeOpenWnd( args:Dynamic, s:Screen):Void{
        //trace(args);
        //trace(_opCounter);
        --_opCounter;
        if ( _opCounter == 0){
            //_screens = new Array<Screen>();
            //_handles= new Array<String>();
            //trace("test");
            open(_virtualX, _virtualY, _virtualWidth, _virtualHeight, _channel, _ring);
            //trace("test");
        }
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
        _opCounter+=_screens.length;
        for (i in 0..._screens.length){ 
            _screens[i].closeWnd( _handles[i], cbCloseBeforeOpenWnd , this); 
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
        _opCounter+=_screens.length;
        for (i in 0..._screens.length){ 
            _screens[i].closeWnd( _handles[i], cbCloseWnd , this); 
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
