
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

    public var _753s:Hash<Wnd>;
    public var _rings:Hash<Wnd>;

    public var _ringNode:RingNode;

    var _currCB:Dynamic->Screen->Void;

    //dont try to create this obj by your own, use ScreenMgr.create() instead.
    public function new( col:Int, row:Int){
        _col = col;
        _row = row;
        super();
    }

    public function has753Available():Bool{
        for( o in _753s.keys()){
            if ( _753s.get(o) == null){
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
    //_753s= new Hash<Wnd>();
    //_rings = new Hash<Wnd>();
    //for ( i in qbox._outputs.keys()){
    //var val = qbox._outputs.get(i);
    //if ( val == "753"){
    //_753s.set(i, null);
    //}else{
    //_rings.set(i, null);
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


public function isOutOfScreen(x:Int, y:Int, w:Int, h:Int ){
    var screenx:Int = _virtualWidth * _col + ScreenMgr.getInst()._virtualX;
    var screeny:Int = _virtualHeight * _row+ ScreenMgr.getInst()._virtualY;
    var screenw:Int = _virtualWidth;
    var screenh:Int = _virtualHeight;
    var isOutOfScreen = false;
    if ( x <screenx ){ 
        if (x + w > screenx ){
            if ( x+w > screenx+_virtualWidth){
                screenw = _virtualWidth;
                //trace(screenw);
            }else{
                screenw =  w - screenx +x;
                //trace(screenw);
            }
            screenx = 0;
        }else{
            isOutOfScreen = true;
            trace("outofscreen");
        }
    }else{
        if ( x >= screenx && x <= screenx + _virtualWidth) {
            //trace(x);
            //trace(w);
            //trace(screenx);
            //trace(_virtualWidth);
            if ( x+w >= screenx+_virtualWidth){
                screenw = _virtualWidth + screenx - x;
                //trace(screenw);
            }else{
                screenw =  w;
                //trace(screenw);
            }
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
    return isOutOfScreen;
}

public function setWnd(x:Int, y:Int, w:Int, h:Int, cbSetWndFunc:Dynamic->Screen->Void ){
    if (_currCB != null){
        trace("there is a set wnd operation processing.");
    }

    var screenx:Int = _virtualWidth * _col + ScreenMgr.getInst()._virtualX;
    var screeny:Int = _virtualHeight * _row+ ScreenMgr.getInst()._virtualY;
    var screenw:Int = _virtualWidth;
    var screenh:Int = _virtualHeight;
    var isOutOfScreen = false;
    if ( x <screenx ){ 
        if (x + w > screenx ){
            if ( x+w > screenx+_virtualWidth){
                screenw = _virtualWidth;
                //trace(screenw);
            }else{
                screenw =  w - screenx +x;
                //trace(screenw);
            }
            screenx = 0;
        }else{
            isOutOfScreen = true;
            trace("outofscreen");
        }
    }else{
        if ( x >= screenx && x <= screenx + _virtualWidth) {
            //trace(x);
            //trace(w);
            //trace(screenx);
            //trace(_virtualWidth);
            if ( x+w >= screenx+_virtualWidth){
                screenw = _virtualWidth + screenx - x;
                //trace(screenw);
            }else{
                screenw =  w;
                //trace(screenw);
            }
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
        var q = QboxMgr.getInst().getQboxByIp( _qbox._ipv4);
        if ( q != null){
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
            q.clearData();
            q.startListening( 6, cbSetWnd, 2);
            q.setMsg( 5, 2);
            q.addKeyVal( "x", Bytes.ofString(Std.string(qx)));
            q.addKeyVal( "y", Bytes.ofString(Std.string(qy)));
            q.addKeyVal( "w", Bytes.ofString(Std.string(qw)));
            q.addKeyVal( "h", Bytes.ofString(Std.string(qh)));
            q.addKeyVal( "out", Bytes.ofString("default"));
            q.sendData();
        }
#else
        var test= new Hash<String>();
        test.set("winHandle","1");
        test.set("error","0");
        var pw = _resWidth /_virtualWidth ;
        var ph = _resHeight/_virtualHeight;
        trace(_resWidth);
        trace(_resHeight);
        trace(_virtualHeight);
        trace(_virtualWidth);
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

/*
public function setChannel( winHandle:String,  channel:Channel, cbSetChannelFunc:Dynamic->Screen->Void):Void{
    if (_currCB != null){ trace("there is a wnd processing."); }
    //var notes = channel._nodes;
    //if (notes ==  null || notes.length == 0){ 
    //trace("channel nodes have not been set!");
    //return;
    //}
    _currCB = cbSetChannelFunc;
#if !neko
    for ( i in notes){
        var arr:Array<String> = i.split(":");
        if ( _qbox._ipv4 == arr[0]){
            var q = QboxMgr.getInst().getQboxByIp( _qbox._ipv4);
            if ( q != null){
                q.clearData();
                q.startListening( 2, cbSetChannel, 3);
                q.setMsg( 1, 3);
                q.addKeyVal( "winHandle", Bytes.ofString(winHandle));
                q.addKeyVal( "in", Bytes.ofString(arr[1]));
                q.sendData();
            }
            break;
        }
    }
#else
    var test= new Hash<String>();
    test.set("error","0");
    cbSetChannel(test);
#end
}
*/

function cbSetChannel( args:Dynamic):Void{
    if (_currCB != null) _currCB( args, this);
    _currCB = null;
}

public function hideWnd( handle:String, cbShowWnd:Dynamic->Void):Void{
#if !neko
    var q = QboxMgr.getInst().getQboxByIp( _qbox._ipv4);
    if ( q != null){
        q.clearData();
        q.startListening( 10, cbShowWnd, 2);
        q.setMsg( 9, 2);
        q.addKeyVal( "winHandle", Bytes.ofString(handle));
        q.addKeyVal( "showState", Bytes.ofString("hide"));
        q.sendData();
    }
#else
    var test= new Hash<String>();
    test.set("winHandle","1");
    test.set("error","0");
    cbShowWnd(test);
#end
}
public function showWnd( handle:String, cbShowWnd:Dynamic->Void):Void{
#if !neko
    var q = QboxMgr.getInst().getQboxByIp( _qbox._ipv4);
    if ( q != null){
        q.clearData();
        q.startListening( 10, cbShowWnd, 2);
        q.setMsg( 9, 2);
        q.addKeyVal( "winHandle", Bytes.ofString(handle));
        q.addKeyVal( "showState", Bytes.ofString("show"));
        q.sendData();
    }
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

public function closeWnd( winHandle:String, cbMoveWndFunc:Dynamic->Screen->Void ):Bool{
    if ( winHandle == "null") return false;
    if (_currCB != null){ trace("there is a wnd operation processing."); }
    trace("closed wnd: "+_col+"|"+_row);
    _currCB = cbMoveWndFunc;
#if !neko
    var q =  _qbox;
    if ( q != null){
        q.clearData();
        q.startListening( 12, cbCloseWnd, 2);
        q.setMsg( 11, 2);
        q.addKeyVal( "winHandle", Bytes.ofString(winHandle));
        q.sendData();
    }
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
}
