
package com.qbox.logic;


class Screen{

    public var _col:Int;
    public var _row:Int;

    public var _virtualWidth:Int;
    public var _virtualHeight:Int;

    public var _qboxid:String;
    public var _output:String;

    public function new( col:Int, row:Int){
        _col = col;
        _row = row;
    }


    public function openWnd(x:Int, y:Int, w:Int, h:Int):String{
        var screenx = _virtualWidth * _col;
        var screeny = _virtualHeight * _row;
        var screenw:Int = _virtualWidth;
        var screenh:Int = _virtualHeight;
        if ( x <screenx && x + w > screenx ){
            if ( x+w > screenx+_virtualWidth){
                screenw = _virtualWidth;
            }else{
                screenw =  w - screenx +x;
            }
        }
        if ( y <screeny && y + h > screeny ){
            if ( y+h > screeny+_virtualHeight){
                screenh = _virtualHeight;
            }else{
                screenh = h - screeny +y;
            }
        }
        if ( x >= screenx && x <= screenx + _virtualWidth) {
            if ( x+w > screenx+_virtualWidth){
                screenw = _virtualWidth + screenx - x;
            }else{
                screenw =  w;
            }
            screenx = x;
        }

        if ( y >= screeny && y <= screeny + _virtualHeight){
            if ( y+h > screeny+_virtualHeight){
                screenh = _virtualHeight +screeny - y;
            }else{
                screenh = h;
            }
            screeny = y;
        }

        trace("" + screenx + " "+screeny+" "+screenw+" "+screenh);
        return "handle";
    }
    public function moveWnd(x:Int, y:Int, w:Int, h:Int, handle:String):String{
        return "handle";
    }
    public function resizeWnd(x:Int, y:Int, w:Int, h:Int, handle:String):String{
        return "handle";
    }
    public function closeWnd( handle:String):Bool{
        return true;
    }
}
