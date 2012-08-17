
package com.qbox.logic;

import haxe.io.Bytes;

class Screen{

    public var _col:Int;
    public var _row:Int;

    public var _virtualWidth:Int;
    public var _virtualHeight:Int;

    public var _qboxid:String;
    public var _output:String;

    var _currCB:Dynamic->Screen->Void;

    public function new( col:Int, row:Int){
        _col = col;
        _row = row;
    }


    public function setWnd(x:Int, y:Int, w:Int, h:Int, cbSetWndFunc:Dynamic->Screen->Void ){
        if (_currCB != null){
            trace("there is a set wnd operation processing.");
        }

        var screenx:Int = _virtualWidth * _col;
        var screeny:Int = _virtualHeight * _row;
        var screenw:Int = _virtualWidth;
        var screenh:Int = _virtualHeight;
        var isOutOfScreen = false;
        if ( x <screenx ){
            if (x + w > screenx ){
                if ( x+w > screenx+_virtualWidth){
                    screenw = _virtualWidth;
                }else{
                    screenw =  w - screenx +x;
                }
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
                    screenh = _virtualHeight +screeny - y;
                }else{
                    screenh = h;
                }
                screeny = y - screeny;
            }else if(  x > screeny + _virtualHeight){
                isOutOfScreen = true;
                trace("outofscreen");
            }
        }

        if (isOutOfScreen){
            trace(""+_col+"|"+_row+":Out of screen");
            var outofscreen = new Hash<String>();
            outofscreen.set("winHandle","null");
            outofscreen.set("error","0");
            cbSetWnd(outofscreen);
        }
        else {
            trace(""+_col+"|"+_row+":" + screenx + " "+screeny+" "+screenw+" "+screenh);
            _currCB = cbSetWndFunc;
#if !neko
            var q = QboxMgr.getInst().getQboxByIp( _qboxid);
            if ( q != null){
                q.clearData();
                q.startListening( 6, cbSetWnd, 2);
                q.setMsg( 5, 2);
                q.addKeyVal( "x", Bytes.ofString(Std.string( screenx) ));
                q.addKeyVal( "y", Bytes.ofString(Std.string( screeny) ));
                q.addKeyVal( "w", Bytes.ofString(Std.string( screenw) ));
                q.addKeyVal( "h", Bytes.ofString(Std.string( screenh) ));
                q.addKeyVal( "out", Bytes.ofString(_output ));
                q.sendData();
            }
#else
            var test= new Hash<String>();
            test.set("winHandle","1");
            test.set("error","0");
            cbSetWnd(test);
#end
        }
    }

    function cbSetWnd( args:Dynamic):Void{
        if (_currCB != null) {
            var tmp = _currCB;
            _currCB = null;
            tmp(args, this);
        }
    }

    public function setChannel( winHandle:String,  channel:Channel, cbSetChannelFunc:Dynamic->Screen->Void):Void{
        if (_currCB != null){
            trace("there is a set channel operation processing.");
        }
        var notes = channel._nodes;
        if (notes ==  null || notes.length == 0){ 
            trace("channel nodes have not been set!");
            return;
        }
        _currCB = cbSetChannelFunc;
#if !neko
        for ( i in notes){
            var arr:Array<String> = i.split(":");
            if ( _qboxid == arr[0]){
                var q = QboxMgr.getInst().getQboxByIp( _qboxid);
                if ( q != null){
                    q.clearData();
                    q.startListening( 1, cbSetChannel, 3);
                    q.setMsg( 2, 3);
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

    function cbSetChannel( args:Dynamic):Void{
        if (_currCB != null) _currCB( args, this);
        _currCB = null;
    }

    public function showWnd( handle:String, cbShowWnd:Dynamic->Void):Void{
#if !neko
        var q = QboxMgr.getInst().getQboxByIp( _qboxid);
        if ( q != null){
            q.clearData();
            q.startListening( 10, cbShowWnd, 2);
            q.setMsg( 9, 2);
            q.addKeyVal( "winHandle", Bytes.ofString(handle));
            q.addKeyVal( "showState", Bytes.ofString("1"));
            q.sendData();
        }
#else
        var test= new Hash<String>();
        test.set("winHandle","1");
        test.set("error","0");
        cbShowWnd(test);
#end
    }


    public function moveWnd(x:Int, y:Int, w:Int, h:Int, winHandle:String):String{
        var screenx:Int = _virtualWidth * _col;
        var screeny:Int = _virtualHeight * _row;
        var screenw:Int = _virtualWidth;
        var screenh:Int = _virtualHeight;
        var isOutOfScreen = false;
        if ( x <screenx ){
            if (x + w > screenx ){
                if ( x+w > screenx+_virtualWidth){
                    screenw = _virtualWidth;
                }else{
                    screenw =  w - screenx +x;
                }
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
                    screenh = _virtualHeight +screeny - y;
                }else{
                    screenh = h;
                }
                screeny = y - screeny;
            }else if(  x > screeny + _virtualHeight){
                isOutOfScreen = true;
                trace("outofscreen");
            }
        }

        if (isOutOfScreen){
            trace(""+_col+"|"+_row+":Out of screen");
            var outofscreen = new Hash<String>();
            outofscreen.set("winHandle","null");
            outofscreen.set("error","0");
            cbMoveWnd(outofscreen);
        }else{
            cbMoveWnd("test");
        }
        return "handle";
    }

    function cbMoveWnd(args:Dynamic){
        trace(args);
    }
    public function resizeWnd(x:Int, y:Int, w:Int, h:Int, handle:String):String{
        return "handle";
    }
    public function closeWnd( handle:String):Bool{
        return true;
    }
}
