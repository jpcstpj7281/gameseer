
package com.qbox.logic;

import haxe.io.Bytes;

class Screen extends Qbox{

    public var _col:Int;
    public var _row:Int;

    public var _virtualWidth:Int;
    public var _virtualHeight:Int;

    public var _resWidth:Int;
    public var _resHeight:Int;

    //public var _output:String;
    //public var _qbox(getQbox, setQbox):Qbox;

    public var _753ports:Hash<Wnd>;
    public var _ringports:Hash<Wnd>;

    public var _ringNode:RingNode;

    public var _channels:Array<Channel>;

    var _currCB:Dynamic->Screen->Void;

    //dont try to create this obj by your own, use ScreenMgr.create() instead.
    public function new( col:Int, row:Int){
        _col = col;
        _row = row;
        _753ports = new Hash<Wnd>();
        _ringports = new Hash<Wnd>();
        _channels = new Array<Channel>();

#if neko
        _753ports.set("1", null);
        _753ports.set("2", null);
        _ringports.set("3", null);
        _ringports.set("4", null);
#end
        super();
    }

    public function has753Available():Bool{
        for( o in _753ports.keys()){
            if ( _753ports.get(o) == null){
                return true;
            }
        }
        return false;
    }

    public function isAfterOf( s:Screen):Bool{
        if (_col >= s._col){
            if ( _row>= s._row){
                return true;
            }
        }else if ( _row> s._row){
            return true;
        }
        return false;
    }

    public function calcScreen(x:Float, y:Float, w:Float, h:Float){
        trace(_virtualWidth);
        trace(ScreenMgr.getInst()._virtualX);
        var screenx:Float= _virtualWidth * _col + ScreenMgr.getInst()._virtualX;//UI上的窗口X坐标,加入ScreenPlate的X偏移
        var screeny:Float= _virtualHeight * _row+ ScreenMgr.getInst()._virtualY;//UI上的窗口X坐标,加入ScreenPlate的Y偏移
        var screenw:Float= _virtualWidth;
        var screenh:Float= _virtualHeight;
        var isOutOfScreen = false;

        var cutleft:Float= 0;
        var cutright:Float= 0;
        var cutup:Float= 0;
        var cutdown:Float= 0;
        if ( x <screenx ){ 
            if (x + w > screenx ){
                if ( x + w > screenx + _virtualWidth){
                    screenw = _virtualWidth;
                }else{
                    screenw =  x + w - screenx ;
                }
                cutright = x + w - screenx - _virtualWidth;//可能是负
                cutleft =  screenx - x;//一定是正
                //窗口的X在这个屏左边,所以从0开始;
                screenx = 0;
            }else{
                isOutOfScreen = true;
                screenh = screenw = 0;
                trace("outofscreen");
            }
        }else{
            if ( x >= screenx && x <= screenx + _virtualWidth) {
                if ( x+w >= screenx+_virtualWidth){
                    screenw = _virtualWidth + screenx - x;
                }else{
                    screenw =  w;
                }
                cutleft = screenx - x; //一定是负
                cutright = x + w - screenx - _virtualWidth;//可能是负
                //窗口的X在屏右边,所以X到SCREEX的偏移位为这个子窗口的X
                screenx = x - screenx;
            }else if ( x >screenx + _virtualWidth){
                isOutOfScreen = true;
                screenh = screenw = 0;
                trace("outofscreen");
            }
        }

        if ( !isOutOfScreen && y <screeny){
            if (y + h > screeny ){
                if ( y+h > screeny+_virtualHeight){
                    screenh = _virtualHeight;
                }else{
                    screenh = y + h - screeny;
                }
                cutdown= y + h - screeny - _virtualHeight;//可能是负
                cutup= screeny - y;//一定是正
                //窗口的Y在这个屏上边,所以从0开始;
                y = 0;
            }else{
                isOutOfScreen = true;
                screenh = screenw = 0;
                trace("outofscreen");
            }
        }else if ( !isOutOfScreen){
            if ( y >= screeny && y <= screeny + _virtualHeight){
                if ( y+h >= screeny+_virtualHeight){
                    screenh = _virtualHeight +screeny -y;
                }else{
                    screenh = h;
                }
                cutdown= y + h - screeny - _virtualHeight;//可能是负
                cutup= screeny - y;//一定是负
                //窗口的y在屏下边,所以y到SCREEY的偏移位为这个子窗口的Y
                screeny = y - screeny;
            }else if(  x > screeny + _virtualHeight){
                isOutOfScreen = true;
                screenx = screeny = screenh = screenw = 0;
                trace("outofscreen");
            }
        }

        return { isOutScreen:isOutOfScreen, 
            x:screenx, 
            y:screeny, 
            w:screenw, 
            h:screenh, 
            col:_col, 
            row:_row, 
            rw:_resWidth, 
            rh:_resHeight, 
            vw:_virtualWidth, 
            vh:_virtualHeight,
            cutLeft:cutleft,
            cutRight:cutright,
            cutUp:cutup,
            cutDown:cutdown
        };
        //return isOutOfScreen;
    }

    //correspond port of wnd, return a available port if cant find correspond port.
    public function get753Port( wnd:Wnd):String{
        for ( i in _753ports.keys()){
            var w = _753ports.get(i);
            if (  w == wnd){
                return i;
            }
        }
        return null;
    }
    public function getRingPort( wnd:Wnd):String{
        for ( i in _ringports.keys()){
            var w = _ringports.get(i);
            if ( w == wnd){
                return i;
            }
        }
        return null;
    }

    public function setWnd(x:Float, y:Float, w:Float, h:Float, cbSetWndFunc:Dynamic->Screen->Void, wnd:Wnd ){
        if (_currCB != null){
            trace("there is a wnd operation processing.");
        }

        var port:String = get753Port(wnd);
        if ( port == null){
            trace("There is no port available to set wnd");
            return false;
        }

        var obj = calcScreen( x, y, w, h);
        var screenx = obj.x;
        var screeny = obj.y;
        var screenw = obj.w;
        var screenh = obj.h;
        var isOutOfScreen = obj.isOutScreen;

        _currCB = cbSetWndFunc;
        if (isOutOfScreen){
            trace(""+_col+"|"+_row+":Out of screen");
            var outofscreen = new Hash<String>();
            outofscreen.set("out","null");
            outofscreen.set("error","0");
            cbSetWnd(outofscreen);
            return false;
        }
        else {
            trace(""+_col+"|"+_row+":" + screenx + " "+screeny+" "+screenw+" "+screenh);
#if !neko
            //calculate real window size
            var pw = _resWidth /_virtualWidth ;
            var ph = _resHeight/_virtualHeight;
            //trace( "virtualX: "+screenx);
            //trace( "virtualY: "+screeny);
            //trace( "virtualW: "+screenw);
            //trace( "virtualH: "+screenh);
            var qx = Math.round(screenx*pw);
            var qy = Math.round(screeny*ph);
            var qw = Math.round(screenw*pw);
            var qh = Math.round(screenh*ph);
            trace("qbox x: "+qx);
            trace("qbox y: "+qy);
            trace("qbox w: "+qw);
            trace("qbox h: "+qh);
            clearData();
            startListening( 6, cbSetWnd, 2);
            setMsg( 5, 2);
            addKeyVal( "x", Bytes.ofString(Std.string(qx)));
            addKeyVal( "y", Bytes.ofString(Std.string(qy)));
            addKeyVal( "w", Bytes.ofString(Std.string(qw)));
            addKeyVal( "h", Bytes.ofString(Std.string(qh)));
            addKeyVal( "out", Bytes.ofString(port));
            sendData();
#else
            var test= new Hash<String>();
            test.set("out",port);
            test.set("error","0");
            var pw = _resWidth /_virtualWidth ;
            var ph = _resHeight/_virtualHeight;
            //trace(_resWidth);
            //trace(_resHeight);
            //trace(_virtualHeight);
            //trace(_virtualWidth);
            var qx = Math.round(screenx*pw);
            var qy = Math.round(screeny*ph);
            var qw = Math.round(screenw*pw);
            var qh = Math.round(screenh*ph);
            trace("qbox x: "+qx);
            trace("qbox y: "+qy);
            trace("qbox w: "+qw);
            trace("qbox h: "+qh);
            test.set( "x", (Std.string(qx)));
            test.set( "y", (Std.string(qy)));
            test.set( "w", (Std.string(qw)));
            test.set( "h", (Std.string(qh)));
            //trace(test);
            cbSetWnd(test);
#end

            return true;
        }
    }

    function cbSetWnd( args:Dynamic):Void{
        if (_currCB != null) {
            var tmp = _currCB;
            _currCB = null;
            tmp(args, this);
        }
    }

    public function setChannelArea(wnd:Wnd, x:Int, y:Int, w:Int, h:Int, c:Channel, cb:Dynamic->Screen->Void){
        if (_currCB != null){ trace("there is a wnd processing."); return;}
        _currCB = cb;
#if !neko
        var p = get753Port(wnd);
        if ( p == null){
            trace("null port error!");
            return;
        }
        clearData();
        startListening( 12, cbSetChannelArea, 3);
        setMsg( 11, 3);
        addKeyVal( "in", Bytes.ofString(c._inport));
        addKeyVal( "out", Bytes.ofString(p));
        addKeyVal( "x", Bytes.ofString(""+x));
        addKeyVal( "y", Bytes.ofString(""+y));
        addKeyVal( "w", Bytes.ofString(""+w));
        addKeyVal( "h", Bytes.ofString(""+h));
        sendData();
#else
        var test= new Hash<String>();
        test.set("error","0");
        cbSetChannelArea(test);
#end
    }

    function cbSetChannelArea( args:Dynamic):Void{
        if (_currCB != null) {
            var tmp = _currCB;
            _currCB = null;
            tmp(args, this);
        }
    }

    public function hideWnd( wnd:Wnd, cbShowWnd:Dynamic->Void){
#if !neko
        var p = get753Port(wnd);
        if ( p == null){
            trace("null port error!");
            return;
        }
        clearData();
        startListening( 10, cbShowWnd, 2);
        setMsg( 9, 2);
        addKeyVal( "out", Bytes.ofString(p));
        addKeyVal( "showState", Bytes.ofString("hide"));
        sendData();
#else
        var test= new Hash<String>();
        test.set("out","1");
        test.set("error","0");
        cbShowWnd(test);
#end
    }
    public function showWnd( wnd:Wnd, cbShowWnd:Dynamic->Void):Void{
#if !neko
        var p = get753Port(wnd);
        if ( p == null){
            trace("null port error!");
            return;
        }
        clearData();
        startListening( 10, cbShowWnd, 2);
        setMsg( 9, 2);
        addKeyVal( "out", Bytes.ofString(p));
        addKeyVal( "showState", Bytes.ofString("show"));
        sendData();
#else
        var test= new Hash<String>();
        test.set("out","1");
        test.set("error","0");
        cbShowWnd(test);
#end
    }

    public function closeWnd( wnd:Wnd, cbCloseWndFunc:Dynamic->Screen->Void):Bool{
        if (_currCB != null){ trace("there is a wnd operation processing."); }
        trace("closed wnd: "+_col+"|"+_row);
        _currCB = cbCloseWndFunc;

        var out:String = null;
        for ( i in _753ports.keys()){
            var w = _753ports.get(i);
            if ( w == wnd){
                _753ports.set(i, null);
                out = i;
            }
        }
        for ( i in _ringports.keys()){
            var w = _ringports.get(i);
            if ( w == wnd){
                _ringports.set(i, null);
            }
        }
        if ( out == null){
            trace("close null port error!");
        }
#if !neko
        clearData();
        startListening( 12, cbCloseWnd, 2);
        setMsg( 11, 2);
        addKeyVal( "out", Bytes.ofString(out));
        sendData();
#else
        var test= new Hash<String>();
        test.set("error","0");
        cbCloseWnd(test);
#end
        return true;
    }
    function cbCloseWnd(args:Dynamic){
        if (_currCB != null) {
            var tmp = _currCB;
            _currCB = null;
            tmp(args, this);
        }
    }

    override function cbLoadOutput( args:Dynamic){
        if ( args.get("error") == 0){

            if ( args.exists("out1")){
                _753ports.set( "1", null);
            }
            if ( args.exists("out2")){
                _753ports.set( "2", null);
            }
            if ( args.exists("out3")){
                _ringports.set( "3", null);
            }
            if ( args.exists("out4")){
                _ringports.set( "4", null);
            }
            //for ( i in 1...5){ _outputs.set( ""+i, outputs.get("out"+i) ); }
        }
        super.cbLoadOutput(args);
    }

    override function loadInput(){
        ChannelMgr.getInst().removeChannelByScreen(this);
        WndMgr.getInst().closeAll();
        super.loadInput();
    }

    override function cbLoadInputsResolution( args:Dynamic){
        if (args.get("error") ==0){
            var c = ChannelMgr.getInst().createChannel();
            c._inport = args.get("in");
            c._screen = this;
            c._w = Std.parseInt(args.get("w"));
            c._h = Std.parseInt(args.get("h"));
            _channels.push(c);
        }
        //trace( args);
        super.cbLoadInputsResolution(args);
    }

    public function set753Channel( input:String, cbSetChannelFunc:Dynamic->Screen->Void, wnd:Wnd):Bool{
        if (_currCB != null){ trace("there is a wnd processing."); return false;}
#if !neko
        var p = get753Port(wnd);
        if ( p == null){ 
            p = get753Port(null);
            if ( p == null){
                trace( "there is no 753 port available to set 753 channel!");
                return false;
            }
            else
                _753ports.set(p, wnd);
        }
        _currCB = cbSetChannelFunc;
        clearData();
        startListening( 2, cbSetChannel, 3);
        setMsg( 1, 3);
        addKeyVal( "out", Bytes.ofString(p));
        addKeyVal( "in", Bytes.ofString(input));
        sendData();
#else
        var test= new Hash<String>();
        test.set("error","0");
        cbSetChannel(test);
#end
        return true;
    }
    public function setRingChannel( out:String,  input:String, cbSetChannelFunc:Dynamic->Screen->Void, wnd:Wnd):Void{
        if (_currCB != null){ trace("there is a wnd processing."); }
        _currCB = cbSetChannelFunc;
#if !neko
        var p = _ringports.get(out);
        if ( p == null){
            _ringports.set( out, wnd);
        }else{
            trace( "there is no port:"+out+" available to set Ring channel!");
            return;
        }
        clearData();
        startListening( 2, cbSetChannel, 3);
        setMsg( 1, 3);
        addKeyVal( "out", Bytes.ofString(out));
        addKeyVal( "in", Bytes.ofString(input));
        sendData();
#else
        var test= new Hash<String>();
        test.set("error","0");
        cbSetChannel(test);
#end
    }

    function cbSetChannel( args:Dynamic):Void{
        if (_currCB != null){
            var tmp = _currCB;
            _currCB = null;
            tmp(args, this);
        }
    }

    public function setLayer( l:Int,  cbSetLayerFunc:Dynamic->Screen->Void, wnd:Wnd):Void{
        if (_currCB != null){ trace("there is a wnd processing."); }
        _currCB = cbSetLayerFunc;
#if !neko
        var p = get753Port(wnd);
        if ( p == null) {
            trace("cannot find port of wnd");
            return;
        }
        clearData();
        startListening( 8, cbSetLayer, 2);
        setMsg( 7, 2);
        addKeyVal( "out", Bytes.ofString(p));
        addKeyVal( "layer", Bytes.ofString(""+l));
        sendData();
#else
        var test= new Hash<String>();
        test.set("error","0");
        cbSetLayer(test);
#end
    }

    function cbSetLayer( args:Dynamic):Void{
        if (_currCB != null){
            var tmp = _currCB;
            _currCB = null;
            tmp(args, this);
        }
    }

    public function resizeWnd(x:Float, y:Float, w:Float, h:Float, cbSetWndFunc:Dynamic->Screen->Void, wnd:Wnd ){
        if (_currCB != null){
            trace("there is a wnd operation processing.");
            return false;
        }

        var port:String = get753Port(wnd);
        if ( port == null){
            trace("There is no port available to set wnd");
            return false;
        }

        var obj = calcScreen( x, y, w, h);
        var screenx = obj.x;
        var screeny = obj.y;
        var screenw = obj.w;
        var screenh = obj.h;
        var isOutOfScreen = obj.isOutScreen;

        _currCB = cbSetWndFunc;
        if (isOutOfScreen){
            trace(""+_col+"|"+_row+":Out of screen");
            var outofscreen = new Hash<String>();
            outofscreen.set("out","null");
            outofscreen.set("error","0");
            cbSetWnd(outofscreen);
            return false;
        }
        else {
            trace(""+_col+"|"+_row+":" + screenx + " "+screeny+" "+screenw+" "+screenh);
#if !neko
            //calculate real window size
            var pw = _resWidth /_virtualWidth ;
            var ph = _resHeight/_virtualHeight;
            //trace( "virtualX: "+screenx);
            //trace( "virtualY: "+screeny);
            //trace( "virtualW: "+screenw);
            //trace( "virtualH: "+screenh);
            var qx = Math.round(screenx*pw);
            var qy = Math.round(screeny*ph);
            var qw = Math.round(screenw*pw);
            var qh = Math.round(screenh*ph);
            trace("qbox x: "+qx);
            trace("qbox y: "+qy);
            trace("qbox w: "+qw);
            trace("qbox h: "+qh);
            clearData();
            //startListening( 14, cbSetWnd, 2);
            //setMsg( 13, 2);
            startListening( 6, cbSetWnd, 2);
            setMsg( 5, 2);
            addKeyVal( "x", Bytes.ofString(Std.string(qx)));
            addKeyVal( "y", Bytes.ofString(Std.string(qy)));
            addKeyVal( "w", Bytes.ofString(Std.string(qw)));
            addKeyVal( "h", Bytes.ofString(Std.string(qh)));
            addKeyVal( "out", Bytes.ofString(port));
            sendData();
#else
            var test= new Hash<String>();
            test.set("out",port);
            test.set("error","0");
            var pw = _resWidth /_virtualWidth ;
            var ph = _resHeight/_virtualHeight;
            //trace(_resWidth);
            //trace(_resHeight);
            //trace(_virtualHeight);
            //trace(_virtualWidth);
            var qx = Math.round(screenx*pw);
            var qy = Math.round(screeny*ph);
            var qw = Math.round(screenw*pw);
            var qh = Math.round(screenh*ph);
            trace("qbox x: "+qx);
            trace("qbox y: "+qy);
            trace("qbox w: "+qw);
            trace("qbox h: "+qh);
            test.set( "x", (Std.string(qx)));
            test.set( "y", (Std.string(qy)));
            test.set( "w", (Std.string(qw)));
            test.set( "h", (Std.string(qh)));
            //trace(test);
            cbSetWnd(test);
#end

            return true;
        }
    }

}
