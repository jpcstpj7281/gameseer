
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
    public var _newinputSize:Array<InputSize>;
    public var _newscreens:Array<Screen>;
    public var _closescreens:Array<Screen>;
    public var _createscreens:Array<Screen>;
    public var _keepscreens:Array<Screen>;

    //public var _handles:Array<String>;

    public var _virtualX:Float;
    public var _virtualY:Float;
    public var _virtualWidth:Float;
    public var _virtualHeight:Float;

    public var _virtualAreaX:Int;
    public var _virtualAreaY:Int;
    public var _virtualAreaW:Int;
    public var _virtualAreaH:Int;

    var _channel:Channel;
    public var _ring:Ring;

    public var _opCounter:Int;

    public var _layer:Int;

    public function new(){
        //_x = 0;
        //_y = 0;
        //_w = cast ScreenMgr.getInst()._width*0.6;
        //_h = cast ScreenMgr.getInst()._height*0.6;
        _screens= new Array<Screen>();
        _inputSize = new Array<InputSize>();
        _opCounter= 0;
    }

    public function setRealArea( x:Int, y:Int, w:Int, h:Int){
        if ( _channel == null) return;

    }

    public function setVirtualArea( x:Float, y:Float, w:Float, h:Float){
        _virtualAreaX = x;
        _virtualAreaY = y;
        _virtualAreaW = w;
        _virtualAreaH = h;
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
        calcInputSize( _inputSize, vs);

        setupChannel();
        return true;
    }

    public function setupChannel(){
        if ( _ring == null){
            if ( _channel._screen.has753Available() == true ){
                _channel._screen.set753Channel(_channel._inport, cbSetupChannel, this);
            }else{
                trace("dont have 753 port available!");
            }
        }else{
            if ( _ring.setup753( this, _screens,  _channel, cbSetup753RingChannel) == false){
                trace("resource error");
            }
        }
    }

    function cbSetup753RingChannel( args:Dynamic){
        //trace(args);
        setWnd();
    }
    function cbSetupChannel( args:Dynamic, s:Screen){
        trace(args);
        setWnd();
    }

    function calcInputSize( inputSizeArr:Array<InputSize>,  sizeArr:Array<Dynamic>){

        var xoffset = ScreenMgr.getInst()._virtualX;
        var yoffset = ScreenMgr.getInst()._virtualY;
        var inx = 0;
        var iny = 0;
        var inw = 0;
        var inh = 0;
        for ( i in  sizeArr){
            if ( i.cutLeft > 0){
                inx = Math.round( _channel._w * i.cutLeft / _virtualWidth);
                inw = Math.round( _channel._w * i.w/ _virtualWidth);
            }else{
                inx = 0;
                inw = Math.round( _channel._w * i.w / _virtualWidth);
            }
            if ( i.cutUp> 0){
                iny = Math.round( _channel._h * i.cutUp / _virtualHeight);
                inh = Math.round( _channel._h * i.h/ _virtualHeight);
            }else{
                iny = 0;
                inh = Math.round( _channel._h * i.h/ _virtualHeight);
            }
            inputSizeArr.push( new InputSize( inx,iny,inw,inh ) );
        }
    }


    function setWnd(){
#if !neko
        for ( i in _screens){
            if ( i.get753Port( this ) == null ){
                trace("screen: "+ i._ipv4 +" resource unexisted!");
                return ;
            }
        }

        if ( _ring != null && _ring._isRingSetup == false){
            //ScreenMgr.getInst().setRing(ring);
            //trace(ring);
            trace("test");
            trace(cbRingSetupToSetChannelArea);
            _ring.setupRing( _channel, this, cbRingSetupToSetChannelArea);
            return;
        }
#end
        cbRingSetupToSetChannelArea(null);
    }

    //set channel area after ring setup.
    function cbRingSetupToSetChannelArea( args:Dynamic):Void{
        _opCounter += _screens.length;
        for( i in 0..._screens.length){
            trace("set channel area: "+ _screens[i]._ipv4 + " x:"+_inputSize[i].x+",y:"+_inputSize[i].y+",w:"+_inputSize[i].w+",h:"+_inputSize[i].h);
            _screens[i].setChannelArea(this, _inputSize[i].x, _inputSize[i].y, _inputSize[i].w, _inputSize[i].h, _channel, cbSetChannelArea);
        }
    }

    function cbSetChannelArea( args:Dynamic, s:Screen){
        trace(args);
        --_opCounter;
        if ( _opCounter == 0){
            _opCounter+=_screens.length;
            for (i in _screens){
                i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbSetWnd, this);
            }
        }
    }


    function cbSetWnd( args:Dynamic, s:Screen):Void{
        var error = args.get("error" );
        if (error == "1") { trace( "There is a error occurred: "+s._ipv4+"!");return; }
        var handle = args.get("out" );
        if ( handle != "null"){
            ++_opCounter;
            s.showWnd( this, cbShowWnd );
        }
        --_opCounter;
    }

    function cbShowWnd( args:Dynamic){
        --_opCounter;
        trace("show window: "+ args);
    }

    public function move( x:Float, y:Float):Bool{
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualX = x;
        _virtualY = y;

        _newscreens = new Array<Screen>();
        _newinputSize = new Array<InputSize>();
        var vs = new Array<Dynamic>();
        for (i in ScreenMgr.getInst()._screens){ 
            var obj = i.calcScreen( _virtualX,_virtualY,_virtualWidth,_virtualHeight);
            if ( obj.isOutScreen == false){
                _newscreens.push(i);
                vs.push(obj);
            }
        }

        calcInputSize( _newinputSize, vs);

        _createscreens = new Array<Screen>();
        _closescreens = new Array<Screen>();
        _keepscreens = new Array<Screen>();

        var hasit:Bool = false;
        for ( i in _screens){
            hasit = false;
            for ( n in _newscreens){
                if ( i == n){
                    _keepscreens.push( i);
                    hasit = true;
                    break;
                }
            }
            if ( !hasit ){
                _closescreens.push(i);
            }
        }

        for ( i in _newscreens){
            hasit = false;
            for ( n in _keepscreens){
                if ( i == n){
                    hasit = true;
                    break;
                }
            }
            if ( !hasit){
                _createscreens.push(i);
            }
        }

        if ( _keepscreens.length > 0){
            _opCounter+=_keepscreens.length;
            for (i in 0..._keepscreens.length){
                _keepscreens[i].hideWnd( this, cbHideBeforeMoveWnd);
            }
        }else{
            ++_opCounter;
            cbHideBeforeMoveWnd(null);
        }
        return true;
    }

    function cbHideBeforeMoveWnd( args:Dynamic):Void{
        trace(args);
        --_opCounter;
        if ( _opCounter == 0){
            if ( _closescreens.length > 0){
                _opCounter+=_closescreens.length;
                for (i in 0..._closescreens.length){
                    _closescreens[i].closeWnd( this, cbCloseBeforeMoveWnd);
                }
            }else{
                ++_opCounter;
                cbCloseBeforeMoveWnd( null, null);
            }
        }
    }

    function cbCloseBeforeMoveWnd( args:Dynamic, s:Screen):Void{
        trace(args);
        --_opCounter;
        if ( _opCounter == 0){
            if ( _createscreens.length > 0 && _ring != null ){
                if ( _ring.setup753( this, _screens,  _channel, cbSetup753RingBeforMoveWnd) == false){
                    trace("resource error");
                }
            }else{
                _opCounter+=_screens.length;
                for (i in _screens){
                    i.resizeWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbSetWnd, this);
                }
            }
        }
    }

    function cbSetup753RingBeforMoveWnd( args){
        _screens = _newscreens;
        _inputSize = _newinputSize;

        if (  _ring != null){
            _opCounter += _screens.length;
            for( i in 0..._screens.length){
                trace("set channel area: "+ _screens[i]._ipv4 + " x:"+_inputSize[i].x+",y:"+_inputSize[i].y+",w:"+_inputSize[i].w+",h:"+_inputSize[i].h);
                _screens[i].setChannelArea(this, _inputSize[i].x, _inputSize[i].y, _inputSize[i].w, _inputSize[i].h, _channel, cbSetupChannelAreaBeforMoveWnd);
            }
        }
    }

    function cbSetupChannelAreaBeforMoveWnd( args, ss){
        --_opCounter;
        if ( _opCounter == 0){
            _opCounter+=_keepscreens.length;
            for (i in _keepscreens){
                i.resizeWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbResizeWndBeforMoveWnd, this);
            }
        }
    }

    function cbResizeWndBeforMoveWnd(args, ss){
        --_opCounter;
        if ( _opCounter == 0){
            _opCounter+=_createscreens.length;
            for (i in _createscreens){
                i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbSetWnd, this);
            }
        }
    }

    public function resize( w:Float, h:Float){
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualHeight = h;
        _virtualWidth = w;
        move( _virtualX, _virtualY);
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
            _screens[i].closeWnd( this, cbCloseWnd ); 
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
