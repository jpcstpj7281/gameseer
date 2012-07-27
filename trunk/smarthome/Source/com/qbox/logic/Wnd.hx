
package com.qbox.logic;


class Wnd{

    //var _x:Int;
    //var _y:Int;
    //var _w:Int;
    //var _h:Int;

    public var _screensWnd:Array<String>;

    public var _virtualX:Int;
    public var _virtualY:Int;
    public var _virtualWidth:Int;
    public var _virtualHeight:Int;
    public function new(){
        //_x = 0;
        //_y = 0;
        //_w = cast ScreenMgr.getInst()._width*0.6;
        //_h = cast ScreenMgr.getInst()._height*0.6;
        _screensWnd = new Array<String>();
    }

    public function open(x:Int, y:Int, w:Int, h:Int){
        _virtualX = x;
        _virtualY = y;
        _virtualWidth = w;
        _virtualHeight = h;

        for (i in ScreenMgr.getInst()._screens){ _screensWnd.push(i.openWnd( x,y,w,h)); }
    }

    public function move( x:Int, y:Int){
        _virtualX = x;
        _virtualY = y;
        var ss = ScreenMgr.getInst()._screens;
        for (i in 0...ss.length){ 
            _screensWnd[i] = ss[i].moveWnd( _virtualX,_virtualY,_virtualWidth,_virtualHeight,_screensWnd[i]);
        }
    }
    public function resize( w:Int, h:Int){

        _virtualHeight = h;
        _virtualWidth = w;
        var ss = ScreenMgr.getInst()._screens;
        for (i in 0...ss.length){ 
            _screensWnd[i] = ss[i].resizeWnd( _virtualX,_virtualY,w,h,_screensWnd[i]);
        }
    }

    public function close(){
        var ss = ScreenMgr.getInst()._screens;
        for (i in 0...ss.length){ 
            ss[i].closeWnd( _screensWnd[i]);
        }
    }

}
