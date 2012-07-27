
package com.qbox.logic;


class Wnd{

    var _x:Int;
    var _y:Int;
    var _w:Int;
    var _h:Int;

    public function new(){
        _x = 0;
        _y = 0;
        _w = cast ScreenMgr.getInst()._width*0.6;
        _h = cast ScreenMgr.getInst()._height*0.6;
    }

}
