package com.qbox.logic;

class InputSize{
    public var x:Float;
    public var y:Float;
    public var w:Float;
    public var h:Float;

    public function new ( x:Float, y:Float, w:Float, h:Float){ this.x = x; this.y=y;this.w=w;this.h=h;}
}

class Wnd{


    public var _inputSize:Array<InputSize>;
    public var _screens:Array<Screen>;
    //public var _newinputSize:Array<InputSize>;
    public var _newscreens:Array<Screen>;
    public var _closescreens:Array<Screen>;
    public var _createscreens:Array<Screen>;
    public var _keepscreens:Array<Screen>;

    //public var _handles:Array<String>;

    public var _virtualX:Float;
    public var _virtualY:Float;
    public var _virtualWidth:Float;
    public var _virtualHeight:Float;

    public var _virtualAreaX:Float;
    public var _virtualAreaY:Float;
    public var _virtualAreaW:Float;
    public var _virtualAreaH:Float;

    public var _channel:Channel;
    public var _ring:Ring;

    public var _opCounter:Int;

    public var _layer:Int;

    public var _isSelected:Bool;

    public function new(){
        //_x = 0;
        //_y = 0;
        //_w = cast ScreenMgr.getInst()._width*0.6;
        //_h = cast ScreenMgr.getInst()._height*0.6;
        _screens= new Array<Screen>();
        _inputSize = new Array<InputSize>();
        _opCounter= 0;
        _layer = 10;
        _virtualAreaX = _virtualAreaY = _virtualAreaW = _virtualAreaH = 0;
        _isSelected = false;
    }

    public function setLayer( l:Int){
        _layer = l;
        _opCounter += _screens.length;
        for ( i in _screens){
            i.setLayer(_layer, cbSetLayer, this);
        }
    }

    public function cbSetLayer( args, ss){
        --_opCounter;
        trace(args);
    }

    public function toFront():Bool{
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        if ( _layer == WndMgr.getInst()._maxLayer) return true;
        _layer = ++WndMgr.getInst()._maxLayer ;
#if !neko
        setLayer(_layer);
#end
        return true;
    }

    public function setRealArea( x:Int, y:Int, w:Int, h:Int):Bool{
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        if ( _channel == null) {trace("null channel!");return false;}

        _virtualAreaW = (w / _channel._w) * _virtualWidth;
        _virtualAreaH = (h / _channel._h) * _virtualHeight;
        _virtualAreaX = (x / _channel._w) * _virtualWidth;
        _virtualAreaY = (y / _channel._h) * _virtualHeight;

        resizeWndChannelArea();
        return true;
    }

    public function setVirtualArea( x:Float, y:Float, w:Float, h:Float):Bool{
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        if ( _channel == null) {trace("null channel!");return false;}

        _virtualAreaX = x;
        _virtualAreaY = y;
        _virtualAreaW = w;
        _virtualAreaH = h;
#if !neko
        resizeWndChannelArea();
#end
        return true;
    }

    function resizeWndChannelArea(){
        _inputSize = new Array<InputSize>();
        var vs = new Array<Dynamic>();
        for (i in _screens){ 
            var obj = i.calcScreen( _virtualX,_virtualY,_virtualWidth,_virtualHeight);
            if ( obj.isOutScreen == false){
                vs.push(obj);
            }
        }
        calcInputSize( _inputSize, vs);

        _opCounter += _screens.length;
        for( i in 0..._screens.length){
            trace("set channel area: "+ _screens[i]._ipv4 + " x:"+_inputSize[i].x+",y:"+_inputSize[i].y+",w:"+_inputSize[i].w+",h:"+_inputSize[i].h);
            _screens[i].setChannelArea(this, 
                    Math.round(_inputSize[i].x), 
                    Math.round(_inputSize[i].y), 
                    Math.round(_inputSize[i].w), 
                    Math.round(_inputSize[i].h), _channel, cbSetupChannelArea);
        }
    }

    public function changeChannel( c:Channel){
        if ( _channel != null && _channel !=c ){
            _channel = c;
            _opCounter+=_screens.length;
            for (i in 0..._screens.length){
                _screens[i].hideWnd( this, cbChangeChannel1);
            }
        }
    }
    public function cbChangeChannel1(a1):Void{
        --_opCounter;
        if ( _opCounter == 0){
            ++_opCounter;
            _channel._screen.set753Channel(_channel._inport, cbChangeChannel2, this);
        }
    }

    function cbChangeChannel2( a1, a2):Void{
        --_opCounter;
        if (_opCounter == 0){
            setVirtualArea( _virtualAreaX, _virtualAreaY, _virtualAreaW, _virtualAreaH);
        }
    }

    function cbSetupChannelArea( args, ss){
        --_opCounter;
        showWnd( cbDescCountFunc1);
    }

    function cbDescCountFunc2( a1:Dynamic, a2:Dynamic):Void{
        --_opCounter;
        if (_opCounter == 0){
            trace("finish operation!");
        }
    }

    function cbDescCountFunc1( args:Dynamic):Void{
        --_opCounter;
        if (_opCounter == 0){
            trace("finish operation!");
        }
    }

    function showWnd( cb:Dynamic->Void ){
        _opCounter += _screens.length;
        for (i in _screens){
            i.showWnd( this, cb);
        }
    }



    public function open(x:Int, y:Int, w:Int, h:Int, c:Channel, ring:Ring){
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _virtualX = x;
        _virtualY = y;
        _virtualWidth = w;
        _virtualHeight = h;
        _channel =  c;
        _ring = ring;

        setRealArea( 0, 0, _channel._w, _channel._h);

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
        //trace("test");

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
        var inx:Float = 0;
        var iny:Float = 0;
        var inw:Float = 0;
        var inh:Float = 0;
        var pw = _channel._w / _virtualWidth;
        var ph = _channel._h / _virtualHeight;
        var rx = _virtualAreaX * pw;
        var ry = _virtualAreaY * ph;
        var rw = _virtualAreaW * pw;
        var rh = _virtualAreaH * ph;
        var rpw = rw / _virtualWidth;
        var rph = rh / _virtualHeight;

        for ( i in  sizeArr){
            if ( i.cutLeft > 0){
                inx = rx + ( i.cutLeft * rpw);
                inw = ( i.w * rpw);
            }else{
                inx = rx;
                inw = ( i.w * rpw);
            }
            if ( i.cutUp> 0){
                iny = ry + ( i.cutUp * rph);
                inh = ( i.h * rph);
            }else{
                iny = ry;
                inh = ( i.h * rph);
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
            _screens[i].setChannelArea(this, 
                    Math.round(_inputSize[i].x), 
                    Math.round(_inputSize[i].y), 
                    Math.round(_inputSize[i].w), 
                    Math.round(_inputSize[i].h), _channel, cbSetChannelAreaBeforeCreateWnd);
        }
    }

    function cbSetChannelAreaBeforeCreateWnd( args:Dynamic, s:Screen){
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
        //var error = args.get("error" );
        //if (error == "1") { trace( "There is a error occurred: "+s._ipv4+"!");return; }
        //var handle = args.get("out" );
        //if ( handle != "null"){
        //++_opCounter;
        //s.showWnd( this, cbShowWnd );
        //}
        --_opCounter;
        if (_opCounter == 0){
            _opCounter += _screens.length;
            for (i in _screens){
                i.setLayer( _layer, cbSetLayerAfterSetWnd, this);
            }
        }
    }

    function cbSetLayerAfterSetWnd( args, ss){
        --_opCounter;
        if (_opCounter == 0){
            _opCounter += _screens.length;
            for (i in _screens){
                i.showWnd( this, cbShowWnd);
            }
        }
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
        _inputSize = new Array<InputSize>();
        var vs = new Array<Dynamic>();
        for (i in ScreenMgr.getInst()._screens){ 
            var obj = i.calcScreen( _virtualX,_virtualY,_virtualWidth,_virtualHeight);
            if ( obj.isOutScreen == false){
                _newscreens.push(i);
                vs.push(obj);
            }
        }

        calcInputSize( _inputSize, vs);

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


#if !neko
        if ( _keepscreens.length > 0){
            _opCounter+=_keepscreens.length;
            for (i in 0..._keepscreens.length){
                _keepscreens[i].hideWnd( this, cbHideBeforeMoveWnd);
            }
        }else{
            ++_opCounter;
            cbHideBeforeMoveWnd(null);
        }
#end
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
        //trace(args);
        --_opCounter;
        if ( _opCounter == 0){
            if ( _createscreens.length > 0 && _ring != null ){
                if ( _ring.setup753( this, _screens,  _channel, cbSetup753RingBeforMoveWnd) == false){
                    trace("resource error");
                }
            }else{
                _opCounter+=_screens.length;
                for (i in _screens){
                    i.resizeWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbResizeWnd, this);
                }
            }
        }
    }
    function cbResizeWnd( args, ss){
        --_opCounter;
        if ( _opCounter == 0){
            cbSetup753RingBeforMoveWnd(args);
        }
    }

    function cbSetup753RingBeforMoveWnd( args){
        _screens = _newscreens;
        //_inputSize = _newinputSize;

        if (  _ring != null){
            _opCounter += _screens.length;
            for( i in 0..._screens.length){
                trace("set channel area: "+ _screens[i]._ipv4 + " x:"+_inputSize[i].x+",y:"+_inputSize[i].y+",w:"+_inputSize[i].w+",h:"+_inputSize[i].h);
                _screens[i].setChannelArea(this, 
                        Math.round(_inputSize[i].x), 
                        Math.round(_inputSize[i].y), 
                        Math.round(_inputSize[i].w), 
                        Math.round(_inputSize[i].h), _channel, cbSetupChannelAreaBeforMoveWnd);
            }
        }else{
            ++_opCounter;
            cbSetupChannelAreaBeforMoveWnd(null, null);
        }
    }

    function cbSetupChannelAreaBeforMoveWnd( args, ss){
        --_opCounter;
        if ( _opCounter == 0){
            if ( _keepscreens.length > 0){
                _opCounter+=_keepscreens.length;
                for (i in _keepscreens){
                    i.resizeWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbResizeWndBeforMoveWnd, this);
                }
            }else{
                ++_opCounter;
                cbResizeWndBeforMoveWnd(null,null);
            }
        }
    }

    function cbResizeWndBeforMoveWnd(args, ss){
        --_opCounter;
        if ( _opCounter == 0){
            if ( _createscreens.length > 0){
                _opCounter+=_createscreens.length;
                for (i in _createscreens){
                    i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbSetWnd, this);
                }
            }
            else{
                ++_opCounter;
                cbSetWnd(null, null);
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
