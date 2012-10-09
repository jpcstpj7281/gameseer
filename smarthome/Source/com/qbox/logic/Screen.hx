
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

    //function setQbox( qbox:Qbox):Qbox{
    ////trace("setQbox");
    //_qbox = qbox;
    //_753ports= new Hash<Wnd>();
    //_ringports = new Hash<Wnd>();
    //for ( i in qbox._outputs.keys()){
    //var val = qbox._outputs.get(i);
    //if ( val == "753"){
    //_753ports.set(i, null);
    //}else{
    //_ringports.set(i, null);
    //}
    //}
    //return qbox;
    //}
    //function getQbox():Qbox{
    //return _qbox;
    //}

    /* deprecated
    //open wnd by reachieve wnd data from qbox;
    public function resurrectWnd( resx:Int, resy:Int, resw:Int, resh:Int, input:String){
    var screenx:Int = _virtualWidth * _col + ScreenMgr.getInst()._virtualX;
    var screeny:Int = _virtualHeight * _row+ ScreenMgr.getInst()._virtualY;

    var pw:Float = _virtualWidth / _resWidth;
    var ph:Float = _virtualHeight / _resHeight;

    var virtualX =  Math.round( resx * pw + screenx);
    var virtualY =  Math.round( resy * pw + screeny);
    _virtualWidth=  Math.round( resw * pw);
    _virtualHeight=  Math.round( resh * ph);

    var wnd = WndMgr.getInst().createWnd();
    wnd._virtualX = virtualX;
    wnd._virtualY = virtualY;
    wnd._virtualWidth = _virtualWidth;
    wnd._virtualHeight = _virtualHeight;
    var nodes = new Array<String>();
    nodes.push( _qbox._ipv4 + ":" +input);
    var c = ChannelMgr.getInst().getChannel( nodes);
    if ( c == null){
    c = ChannelMgr.getInst().createChannel();
    c.addNode( _qbox, input);
    }
    wnd._channel = c;
    return wnd;

    //trace("resurrectWnd");
    }
     */


    public function calcScreen(x:Int, y:Int, w:Int, h:Int ){
        var screenx:Int = _virtualWidth * _col + ScreenMgr.getInst()._virtualX;//UI上的窗口X坐标,加入ScreenPlate的X偏移
        var screeny:Int = _virtualHeight * _row+ ScreenMgr.getInst()._virtualY;//UI上的窗口X坐标,加入ScreenPlate的Y偏移
        var screenw:Int = _virtualWidth;
        var screenh:Int = _virtualHeight;
        var isOutOfScreen = false;

        var cutleft:Int = 0;
        var cutright:Int = 0;
        var cutup:Int = 0;
        var cutdown:Int = 0;
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

    public function setWnd(x:Int, y:Int, w:Int, h:Int, cbSetWndFunc:Dynamic->Screen->Void, wnd:Wnd ){
        if (_currCB != null){
            trace("there is a wnd operation processing.");
        }

        var availablePorts:String = null;
        for ( i in _753ports.keys()){
            var w = _753ports.get(i);
            if ( w == null || w == wnd){
                availablePorts = i;
                _753ports.set( i, wnd);
                break;
            }
        }
        if ( availablePorts == null){
            trace("There is no port available to set wnd");
            return false;
        }

        var obj = calcScreen( x, y, w, h);
        var screenx = obj.x;
        var screeny = obj.y;
        var screenw = obj.w;
        var screenh = obj.h;
        var isOutOfScreen = obj.isOutScreen;

        if ( ! isOutOfScreen && y <screeny){
            if (y + h > screeny ){
                if ( y+h > screeny+_virtualHeight){
                    screenh = _virtualHeight;
                }else{
                    screenh = h - screeny +y;
                }
            }else{
                isOutOfScreen = true;
                trace("outofscreen");
            }
        }else if ( !isOutOfScreen){
            if ( y >= screeny && y <= screeny + _virtualHeight){
                if ( y+h >= screeny+_virtualHeight){
                    screenh = _virtualHeight +screeny -y;
                }else{
                    screenh = h;
                }
                screeny = y - screeny;
            }else if(  x > screeny + _virtualHeight){
                isOutOfScreen = true;
                trace("outofscreen");
            }
        }

        _currCB = cbSetWndFunc;
        if (isOutOfScreen){
            trace(""+_col+"|"+_row+":Out of screen");
            var outofscreen = new Hash<String>();
            outofscreen.set("winHandle","null");
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
            addKeyVal( "out", Bytes.ofString(availablePorts));
            sendData();
#else
            var test= new Hash<String>();
            test.set("winHandle",availablePorts);
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

    public function setChannelArea( x:Int, y:Int, w:Int, h:Int, c:Channel, cb:Dynamic->Screen->Void){
        if (_currCB != null){ trace("there is a wnd processing."); }
        _currCB = cb;
#if !neko
        clearData();
        startListening( 12, cbSetChannelArea, 3);
        setMsg( 11, 3);
        addKeyVal( "in", Bytes.ofString(c._inport));
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

    public function hideWnd( handle:String, cbShowWnd:Dynamic->Void):Void{
#if !neko
        clearData();
        startListening( 10, cbShowWnd, 2);
        setMsg( 9, 2);
        addKeyVal( "winHandle", Bytes.ofString(handle));
        addKeyVal( "showState", Bytes.ofString("hide"));
        sendData();
#else
        var test= new Hash<String>();
        test.set("winHandle","1");
        test.set("error","0");
        cbShowWnd(test);
#end
    }
    public function showWnd( handle:String, cbShowWnd:Dynamic->Void):Void{
#if !neko
        clearData();
        startListening( 10, cbShowWnd, 2);
        setMsg( 9, 2);
        addKeyVal( "winHandle", Bytes.ofString(handle));
        addKeyVal( "showState", Bytes.ofString("show"));
        sendData();
#else
        var test= new Hash<String>();
        test.set("winHandle","1");
        test.set("error","0");
        cbShowWnd(test);
#end
    }

    public function resizeWnd(x:Int, y:Int, w:Int, h:Int, handle:String):String{
        return "handle";
    }

    public function closeWnd( winHandle:String, cbCloseWndFunc:Dynamic->Screen->Void, wnd:Wnd ):Bool{
        if ( winHandle == "null") return false;
        if (_currCB != null){ trace("there is a wnd operation processing."); }
        trace("closed wnd: "+_col+"|"+_row);
        _currCB = cbCloseWndFunc;

        for ( i in _753ports.keys()){
            var w = _753ports.get(i);
            if ( w == wnd){
                _753ports.set(i, null);
            }
        }
        for ( i in _ringports.keys()){
            var w = _ringports.get(i);
            if ( w == wnd){
                _ringports.set(i, null);
            }
        }
#if !neko
        clearData();
        startListening( 12, cbCloseWnd, 2);
        setMsg( 11, 2);
        addKeyVal( "winHandle", Bytes.ofString(winHandle));
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
                _ringports.set( "3", null);
            }
            //for ( i in 1...5){ _outputs.set( ""+i, outputs.get("out"+i) ); }
        }
        super.cbLoadOutput(args);
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

        super.cbLoadInputsResolution(args);
    }

    public function setChannel( winHandle:String,  input:String, cbSetChannelFunc:Dynamic->Screen->Void, wnd:Wnd):Void{
        if (_currCB != null){ trace("there is a wnd processing."); }
        _currCB = cbSetChannelFunc;
#if !neko
        var p = _753ports.get(winHandle);
        if ( p != null){ 
            _753ports.set( winHandle, wnd);
        }else{
            p = _ringports.get(winHandle);
            if ( p != null){
                _ringports.set( winHandle, wnd);
            }else{
                trace( "there is no port available to set channel!");
                return;
            }
        }
        clearData();
        startListening( 2, cbSetChannel, 3);
        setMsg( 1, 3);
        addKeyVal( "winHandle", Bytes.ofString(winHandle));
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


}
