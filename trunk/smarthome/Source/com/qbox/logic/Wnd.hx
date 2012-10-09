
package com.qbox.logic;

class InputSize{
    public var x:Int;
    public var y:Int;
    public var w:Int;
    public var h:Int;

    public function new ( x:Int, y:Int, w:Int, h:Int){ this.x = x; this.y=y;this.w=w;this.h=h;}
}

class Wnd{


    public var _inputSize:Array<InputSize>;
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
        _inputSize = new Array<InputSize>();
        _handles= new Array<String>();
        _opCounter= 0;
    }

    public function open(x:Int, y:Int, w:Int, h:Int, c:Channel, ring:Ring){
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualX = x;
        _virtualY = y;
        _virtualWidth = w;
        _virtualHeight = h;
        _channel =  c;
        _ring = ring;

        _screens = new Array<Screen>();
        _inputSize = new Array<InputSize>();
        var vs = new Array<Dynamic>();
        for (i in ScreenMgr.getInst()._screens){ 
            var obj = i.calcScreen( x,y,w,h);
            if ( obj.isOutScreen == false){
                _screens.push(i);
                vs.push(obj);
            }
        }

        if ( _screens.length > 1){
            calcInputSize( _inputSize, _screens, vs);
        }else{
            _inputSize.push( new InputSize( 0, 0, c._w,c._h) );
        }
        return true;
    }

    function calcInputSize( inputSizeArr:Array<InputSize>, ssArr:Array<Screen>, sizeArr:Array<Dynamic>){


        for ( i in  sizeArr){
            if ( i.cutLeft >= 0){
                if ( i.cutRight >= 0){
                }
            }else{
            }
        }

        /*
        var minCol:Int = 1024;
        var minRow:Int = 1024;
        var maxCol:Int = 0;
        var maxRow:Int = 0;
        for ( i in sizeArr){
            if ( i.col < minCol){
                minCol = i.col;
            }
            if ( i.row < minRow){
                minRow = i.row;
            }
            if ( i.col > maxCol){
                maxCol = i.col;
            }
            if ( i.row > maxRow){
                maxRow = i.row;
            }
        }

        for ( i in sizeArr){
            var diffMinCol = i.col - minCol;
            var diffMaxCol = maxCol - i.col;
            var diffMinRow = i.row - minRow;
            var diffMaxRow = maxRow - i.row;
            

        }


        trace( minCol);
        trace( minRow);
        trace( maxCol);
        trace( maxRow);
        */
    }


    function cbSetChannelArea( args:Dynamic, s:Screen){
        setWnd();
    }

    function setWnd(){
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
        _opCounter += _screens.length;
        for (i in _screens){
            i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbSetWnd, this);
        }
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
