﻿package com.qbox.logic;

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

    var _cbDone:Dynamic->Void;

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

    public function isPossessd():Bool{
        return _opCounter > 0;
    }

    function setLayer( l:Int):Bool{
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        _layer = l;
        _opCounter += _screens.length;
        for ( i in _screens){
            i.setLayer(_layer, cbSetLayer, this);
        }
        return true;
    }

    public function cbSetLayer( args, ss){
        --_opCounter;
    }

    public function toFront():Bool{
        if ( _layer == WndMgr.getInst()._maxLayer) return true;
        _layer = ++WndMgr.getInst()._maxLayer ;
#if !neko
        setLayer(_layer);
#end
        return true;
    }

    public function setRealAreaOnly( x:Float, y:Float, w:Float, h:Float){
        _virtualAreaW = (w / _channel._w) * _virtualWidth;
        _virtualAreaH = (h / _channel._h) * _virtualHeight;
        _virtualAreaX = (x / _channel._w) * _virtualWidth;
        _virtualAreaY = (y / _channel._h) * _virtualHeight;
    }

    public function setRealArea( x:Float, y:Float, w:Float, h:Float):Bool{
        if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
        if ( _channel == null) {trace("null channel!");return false;}

        setRealAreaOnly(x,y,w,h);

        resizeChannelArea();
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
        resizeChannelArea();
#end
        return true;
    }

    function resizeChannelArea(){
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
        showWnd(cbDescCountFunc1);
    }

    function cbSetupChannelArea( args, ss){
        --_opCounter;
        if (_opCounter == 0){
        }
    }

    public function fastChangeChannel( c:Channel):Bool{
        if ( _channel !=c ){
            var wnds = WndMgr.getInst().getWndsByChannel(c);
            if (wnds.length == 1){
                _channel = c;
                ++_opCounter;

                if( _ring != null && _ring.getRingNodeIfRingAvailable(_channel, this) != null){
                    _ring.checkAndSetupRing( _channel, this);
                    _ring.setup753NoCB( this, _screens,  _channel);
                }else{
                    _channel._screen.set753ChannelNoCB(_channel._inport, this);
                }

                setRealArea( 0,0,_channel._w, _channel._h);

                return true;
            }
        }
        return false;
    }

    /*
    public function changeChannel( c:Channel):Bool{
        if ( _channel !=c ){
            var wnds = WndMgr.getInst().getWndsByChannel(c);
            if (wnds.length == 1){
                _channel = c;
                ++_opCounter;
                cbChangeChannel1( null);
                return true;
            }
        }
        return false;
    }

    public function cbChangeChannel1(a1):Void{
        --_opCounter;
        if (_opCounter == 0){
            if( _ring != null && _ring.getRingNodeIfRingAvailable(_channel, this) != null){
                if(! _ring.checkAndSetupRing( _channel, this)){
                    cbChangeChannel2(null);
                    trace("failed to setup ring");
                }
            }else{
                trace("test");
                _channel._screen.set753Channel(_channel._inport, cbChangeChannel4, this);
            }
        }
    }

    function cbChangeChannel2( a1):Void{
        if (_ring != null){
            trace("test");
            _ring.setup753( this, _screens,  _channel, cbChangeChannel3);
        }
    }

    function cbChangeChannel4( a1,a2):Void{
        cbChangeChannel3(a1);
    }
    function cbChangeChannel3( a1):Void{
        setRealArea( 0,0,_channel._w, _channel._h);
    }


    function cbDescCountFunc2( a1:Dynamic, a2:Dynamic):Void{
        --_opCounter;
        if (_opCounter == 0){
            trace("finish operation!");
        }
    }
    */

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


    inline public function resurrectWnd(cb:Dynamic->Void){
        return fastOpen( _virtualX, _virtualY, _virtualWidth, _virtualHeight, _channel, _ring, cb);
    }

    /*
       public function open(x:Float, y:Float, w:Float, h:Float, c:Channel, ring:Ring, cb:Dynamic->Void ){
       if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
       if ( _cbDone != null) {trace("_cbDone not null"); return false; }
       _cbDone = cb;

       _virtualX = x;
       _virtualY = y;
       _virtualWidth = w;
       _virtualHeight = h;
       _channel =  c;
       _ring = ring;

#if !neko
setRealAreaOnly( 0, 0, _channel._w, _channel._h);

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
////trace("test");
return setupChannel();
#else
++_opCounter ;
cbShowWnd(null);
return true;
#end
}
     */

/*
public function setupChannel():Bool{
    if ( _ring == null){
        if ( _channel._screen.has753Available()){
            return _channel._screen.set753Channel(_channel._inport, cbSetupChannel, this);
        }
        else{
            trace("dont have 753 port available!");
            return false;
        }
    }else{
        if ( _ring.getRingNodeIfRingAvailable( _channel, this) != null){
            return _ring.setup753( this, _screens,  _channel, cbSetup753RingChannel);
        }else{
            trace("ring: "+_ring._nodeIndex+" not available!");
            return false;
        }
    }
}

function cbSetup753RingChannel( args:Dynamic){
    trace("wnd 753 ring channel setted!");
    setWnd();
}
function cbSetupChannel( args:Dynamic, s:Screen){
    trace("wnd channel setted!");
    setWnd();
}
*/

function calcInputSize( inputSizeArr:Array<InputSize>,  sizeArr:Array<Dynamic>){

    var xoffset = ScreenMgr.getInst()._virtualX;
    var yoffset = ScreenMgr.getInst()._virtualY;
    var inx:Float = 0;
    var iny:Float = 0;
    var inw:Float = 0;
    var inh:Float = 0;
    var pw:Float = _channel._w / _virtualWidth;
    var ph:Float = _channel._h / _virtualHeight;
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

/*

function setWnd():Bool{
#if !neko
    if ( _ring != null){
        if( _ring.checkAndSetupRing( _channel, this)){
            cbRingSetupToSetChannelArea(null);
            return true;
        }
    }
#end
    cbRingSetupToSetChannelArea(null);
    return true;
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
    --_opCounter;
    if (_opCounter == 0){
        _opCounter += _screens.length;
        //trace("**************"+_layer+"*************");
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
*/
function cbShowWnd( args:Dynamic){
    --_opCounter;
    trace("show window: "+ args);
    if (_opCounter == 0){
        var tmp = _cbDone;
        _cbDone = null;
        tmp(true);
    }
}

/*
   public function move( x:Float, y:Float, cb:Dynamic->Void ):Bool{
   if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
   if ( _cbDone != null) {trace("_cbDone not null"); return false;}
   _cbDone = cb;

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
   trace( i._ipv4);
   trace( obj.x);
   trace( obj.y);
   trace( obj.w);
   trace( obj.h);
   }
   }

   for( i in _newscreens){
   if ( i.get753Port( this) == null && i.get753Port(null) == null){
   trace("screen: "+i._ipv4 +" no enough 753 port!");
   return false;
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
*/

/*
function cbHideBeforeMoveWnd( args:Dynamic):Void{
    trace(args);
    --_opCounter;
    //trace("test");
    if ( _opCounter == 0){
        if ( _closescreens.length > 0){
            _opCounter+=_closescreens.length;
            for (i in 0..._closescreens.length){
                _closescreens[i].closeWnd( this, cbCloseBeforeMoveWnd);
                //trace("test");
            }
        }else{
            ++_opCounter;
            cbCloseBeforeMoveWnd( null, null);
            //trace("test");
        }
    }
    //trace("test");
}

function cbCloseBeforeMoveWnd( args:Dynamic, s:Screen):Void{
    //trace(args);
    --_opCounter;
    if ( _opCounter == 0){
        if ( _createscreens.length > 0 && _ring != null ){
            //trace("test");
            if ( _ring.setup753( this, _newscreens,  _channel, cbSetup753RingBeforMoveWnd) == false){
                trace("resource error");
            }
        }
}
//trace("test");
}
*/

/*
function cbResizeWnd( args, ss){
    --_opCounter;
    if ( _opCounter == 0){
        cbSetup753RingBeforMoveWnd(args);
    }
}

function cbSetup753RingBeforMoveWnd( args){
    _screens = _newscreens;
    //trace("test");
    if (  _ring != null){
        _opCounter += _screens.length;
        for( i in 0..._screens.length){
            trace("set channel area: "+ _screens[i]._ipv4 + " x:"+_inputSize[i].x+",y:"+_inputSize[i].y+",w:"+_inputSize[i].w+",h:"+_inputSize[i].h);
            _screens[i].setChannelArea(this, 
                    Math.round(_inputSize[i].x), 
                    Math.round(_inputSize[i].y), 
                    Math.round(_inputSize[i].w), 
                    Math.round(_inputSize[i].h), _channel, cbSetupChannelAreaBeforMoveWnd);
            //trace("test");
        }
    }else{
        //trace("test");
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
                i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbResizeWndBeforMoveWnd, this);
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
*/

public function resize( w:Float, h:Float, cb:Dynamic->Void){
    if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
    _virtualHeight = h;
    _virtualWidth = w;
    return fastMove( _virtualX, _virtualY, cb);
}

//WndDlg will invoke this
public function reset(x:Float, y:Float, w:Float, h:Float, cb:Dynamic->Void){
    if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
    _virtualX = x;
    _virtualY = y;
    resize(w, h, cb);
    return true;
}

public function close( cb:Dynamic->Void){
    //var ss = ScreenMgr.getInst()._screens;
    if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
    _cbDone = cb;

#if !neko
    _opCounter+=_screens.length;
    for (i in 0..._screens.length){ 
        _screens[i].closeWnd( this, cbCloseWnd ); 
    }
#else
    _opCounter+=1;
    cbCloseWnd(null, null);
#end
    return true;
}

function cbCloseWnd( args:Dynamic, s:Screen){
    if ( args != null && args.get("error") == "1") { trace("close wnd failed");return; }
    else trace("close wnd succeed");

    --_opCounter;
    if (_cbDone != null && _opCounter == 0){
        var tmp = _cbDone;
        _cbDone = null;
        tmp(true);
    }
}

//fast open========================================================================================================
public function cbFastOpen( args, ss){
    if ( args != null && args.get("error") == "1") { trace("fast open failed");return; }
    --_opCounter;
    if (_cbDone != null && _opCounter == 0){
        var tmp = _cbDone;
        _cbDone = null;
        tmp(true);
    }
}
public function cbFastOpen1( args){
    if ( args != null && args.get("error") == "1") { trace("fast open failed");return; }
    --_opCounter;
    if (_cbDone != null && _opCounter == 0){
        var tmp = _cbDone;
        _cbDone = null;
        tmp(true);
    }
}
public function cbFastOpenShow( args){
    if ( args != null && args.get("error") == "1") { trace("fast open failed");return; }
    --_opCounter;
    trace("_opCounter: "+_opCounter);
    if (_cbDone != null && _opCounter == 0){
        trace("fast open succeed");
        var tmp = _cbDone;
        _cbDone = null;
        tmp(true);
    }
}

public function fastOpen(x:Float, y:Float, w:Float, h:Float, c:Channel, ring:Ring, cb:Dynamic->Void ){
    if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
    if ( _cbDone != null) {trace("_cbDone not null"); return false; }
    _cbDone = cb;

    _virtualX = x;
    _virtualY = y;
    _virtualWidth = w;
    _virtualHeight = h;
    _channel =  c;
    _ring = ring;
    //trace("test");

    setRealAreaOnly( 0, 0, _channel._w, _channel._h);

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
    //trace("test");
    calcInputSize( _inputSize, vs);
    ////trace("test");
    if ( _ring == null){
        if ( _channel._screen.has753Available()){
            //trace("fastopen");
            _opCounter += 5;
            _channel._screen.set753Channel(_channel._inport, cbFastOpen, this);
            _screens[0].setChannelArea(this, 
                    Math.round(_inputSize[0].x), 
                    Math.round(_inputSize[0].y), 
                    Math.round(_inputSize[0].w), 
                    Math.round(_inputSize[0].h), _channel, cbFastOpen);
            _screens[0].setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbFastOpen, this);
            _screens[0].setLayer( _layer, cbFastOpen, this);
            _screens[0].showWnd( this, cbFastOpenShow);
            return true;
        }
        else{
            _cbDone  = null;
            trace("dont have 753 port available!");
            return false;
        }
    }else{
        if ( _ring.getRingNodeIfRingAvailable( _channel, this) != null && _ring.check753(this, _screens, _channel) ){
            _ring.setup753( this, _screens,  _channel, cbFastOpen1);
            _opCounter+=1;
            _ring.checkAndSetupRing( _channel, this);
            _opCounter+=_screens.length;
            for( i in 0..._screens.length){
                //trace("set channel area: "+ _screens[i]._ipv4 + " x:"+_inputSize[i].x+",y:"+_inputSize[i].y+",w:"+_inputSize[i].w+",h:"+_inputSize[i].h);
                _screens[i].setChannelArea(this, 
                        Math.round(_inputSize[i].x), 
                        Math.round(_inputSize[i].y), 
                        Math.round(_inputSize[i].w), 
                        Math.round(_inputSize[i].h), _channel, cbFastOpen);
            }
            trace(_screens.length);
            trace("_opCounter: "+_opCounter);
            _opCounter+=_screens.length;
            for (i in _screens){
                i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbFastOpen, this);
            }
            trace("_opCounter: "+_opCounter);
            _opCounter+=_screens.length;
            for (i in _screens){
                i.setLayer( _layer, cbFastOpen, this);
            }
            trace("_opCounter: "+_opCounter);
            _opCounter+=_screens.length;
            for (i in _screens){
                i.showWnd( this, cbFastOpenShow);
            }
            trace("_opCounter: "+_opCounter);
            return true;
        }else{
            trace("ring: "+_ring._nodeIndex+" not available!");
            _cbDone  = null;
            return false;
        }
    }
}
//fast move========================================================================================================
public function cbFastMove( args, ss){
    if ( args != null && args.get("error") == "1") { trace("fast open failed");return; }
    --_opCounter;
    if (_cbDone != null && _opCounter == 0){
        var tmp = _cbDone;
        _cbDone = null;
        tmp(true);
    }
}
public function cbFastMove1( args){
    if ( args != null && args.get("error") == "1") { trace("fast open failed");return; }
    --_opCounter;
    if (_cbDone != null && _opCounter == 0){
        var tmp = _cbDone;
        _cbDone = null;
        tmp(true);
    }
}
public function cbFastMoveShow( args){
    if ( args != null && args.get("error") == "1") { trace("fast open failed");return; }
    --_opCounter;
    trace("_opCounter: "+_opCounter);
    if (_cbDone != null && _opCounter == 0){
        trace("fast Move succeed");
        var tmp = _cbDone;
        _cbDone = null;
        tmp(true);
    }
}
public function fastMove( x:Float, y:Float, cb:Dynamic->Void ):Bool{
    if ( _opCounter != 0 ) {trace("_opCounter:"+_opCounter);return false;}
    if ( _cbDone != null) {trace("_cbDone not null"); return false;}
    _cbDone = cb;
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
            trace( i._ipv4);
            trace( obj.x);
            trace( obj.y);
            trace( obj.w);
            trace( obj.h);
        }
    }

    trace("test");
    for( i in _newscreens){
        if ( i.get753Port( this) == null && i.get753Port(null) == null){
            trace("screen: "+i._ipv4 +" no enough 753 port!");
            _cbDone  = null;
            return false;
        }
    }
    trace("test");

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

    //if ( _keepscreens.length > 0){
    //_opCounter+=_keepscreens.length;
    //for (i in 0..._keepscreens.length){
    //_keepscreens[i].hideWnd( this, cbFastMove1);
    //}
    //}

    if ( _createscreens.length > 0 && _ring != null ){
        _opCounter+=1;
        if ( _ring.setup753( this, _newscreens,  _channel, cbFastMove1) == false){
            trace("resource error");
            _cbDone  = null;
            return false;
        }
    }

    if ( _closescreens.length > 0 && _ring != null){
        _opCounter+=_closescreens.length;
        for (i in 0..._closescreens.length){
            _closescreens[i].closeWnd( this, cbFastMove);
            //trace("test");
        }
    }

    _screens = _newscreens;
    if (  _ring != null){//移动时单屏不需要再设置
        _opCounter += _screens.length;
        for( i in 0..._screens.length){
            trace("set channel area: "+ _screens[i]._ipv4 + " x:"+_inputSize[i].x+",y:"+_inputSize[i].y+",w:"+_inputSize[i].w+",h:"+_inputSize[i].h);
            _screens[i].setChannelArea(this, 
                    Math.round(_inputSize[i].x), 
                    Math.round(_inputSize[i].y), 
                    Math.round(_inputSize[i].w), 
                    Math.round(_inputSize[i].h), _channel, cbFastMove);
        }
    }

    if ( _screens.length > 0){//重置输出窗口大小
        _opCounter+=_screens.length;
        for (i in _screens){
            i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbFastMove, this);
        }
    }

    //if ( _createscreens.length > 0){//新建的输出窗口大小
    //_opCounter+=_createscreens.length;
    //for (i in _createscreens){
    //i.setWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight, cbSetWnd, this);
    //}
    //}

    _opCounter+=_screens.length;
    for (i in _screens){
        i.setLayer( _layer, cbFastMove, this);
    }
    _opCounter+=_screens.length;
    for (i in _screens){
        i.showWnd( this, cbFastMoveShow);
    }

    //trace("_opCounter: "+_opCounter);

    return true;
}
}
