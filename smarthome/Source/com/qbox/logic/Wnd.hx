
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
        for (i in ScreenMgr.getInst()._screens){ i.setWnd( x,y,w,h, cbSetWnd); }
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
        for (i in 0..._screens.length){ 
            //trace(_screens[i]);
            _screens[i].closeWnd( _handles[i], cbCloseBeforeOpenWnd); 
        }
    }

    function cbCloseBeforeOpenWnd( args:Dynamic, s:Screen){
        _screens = new Array<Screen>();
        _handles= new Array<String>();
        open(_virtualX, _virtualY, _virtualWidth, _virtualHeight, _channel);
    }

    function cbMoveWnd( args:Dynamic, s:Screen){
        var error = args.get("error" );
        if (error == "1") { return; }
        var handle = args.get("winHandle" );
        trace(handle);
        _screens.push( s);
        _handles.push( handle);
        s.showWnd( handle, cbShowWnd);
    }

    public function resize( w:Int, h:Int){
        _virtualHeight = h;
        _virtualWidth = w;
        for (i in 0..._screens.length){ _screens[i].closeWnd( _handles[i], cbCloseBeforeOpenWnd); }
    }

    public function reset(x:Int, y:Int, w:Int, h:Int){
        _virtualX = x;
        _virtualY = y;
        _virtualHeight = h;
        _virtualWidth = w;
        for (i in 0..._screens.length){ _screens[i].closeWnd( _handles[i], cbCloseBeforeOpenWnd); }
    }
    public function close(){
        //var ss = ScreenMgr.getInst()._screens;
        for (i in 0..._screens.length){ _screens[i].closeWnd( _handles[i], cbCloseWnd); }
    }
    function cbCloseWnd( args:Dynamic, s:Screen){
        var error = args.get("error" );
        if (error == "1") { trace("close wnd failed");return; }
        else trace("close wnd succeed");
    }

}
