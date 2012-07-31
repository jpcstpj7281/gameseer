
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


    public function new(){
        //_x = 0;
        //_y = 0;
        //_w = cast ScreenMgr.getInst()._width*0.6;
        //_h = cast ScreenMgr.getInst()._height*0.6;
        _screens= new Array<Screen>();
        _handles= new Array<String>();
    }

    public function open(x:Int, y:Int, w:Int, h:Int, channel:Channel){
        _virtualX = x;
        _virtualY = y;
        _virtualWidth = w;
        _virtualHeight = h;
        _channel =  channel;

        for (i in ScreenMgr.getInst()._screens){ 
            i.setWnd( x,y,w,h, cbSetWnd); 
        }
    }

    function cbSetWnd( args:Dynamic, s:Screen):Void{
        var error = args.get("error" );
        if (error == "1") { return; }
        var handle = args.get("winHandle" );
        //trace(s);
        //trace(handle);
        _screens.push( s);
        _handles.push( handle);
        //trace("setChannel:"+handle);
        if ( handle != "null"){
            s.setChannel( handle, _channel,  cbSetChannel);
        }
    }

    function cbSetChannel( args:Dynamic, s:Screen):Void{
        var error = args.get("error");
        if (error == "1") { return; }
        for ( i in 0..._screens.length){
            if ( _screens[i] == s ){
                if ( _handles[i] != "null"){
                    s.showWnd( _handles[i], cbShowWnd );
                }
            }
        }
    }

    function cbShowWnd( args:Dynamic){
        trace(args);
    }

    public function move( x:Int, y:Int){
        _virtualX = x;
        _virtualY = y;
        //var ss = ScreenMgr.getInst()._screens;
        //for (i in 0...ss.length){ 
        //_screensWnd[i] = ss[i].moveWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight,_screensWnd[i]);
        //}
        for ( i in 0..._screens.length){
            _handles[i] = _screens[i].moveWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight,_handles[i]);
        }
    }
    public function resize( w:Int, h:Int){

        _virtualHeight = h;
        _virtualWidth = w;
        //var ss = ScreenMgr.getInst()._screens;
        for (i in 0..._screens.length){ 
            _handles[i] = _screens[i].resizeWnd( _virtualX,_virtualY,w,h,_handles[i]);
        }
    }

    public function close(){
        //var ss = ScreenMgr.getInst()._screens;
        for (i in 0..._screens.length){ 
            _screens[i].closeWnd( _handles[i]);
        }
    }

}
