package com.qbox.ui.osd;

import com.qbox.logic.QboxMgr;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import base.ui.CommDialogMgr;
import base.ui.ListDialog;
import base.ui.CommDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;

import com.qbox.logic.Qbox;
import com.qbox.logic.Screen;

class ValueBarDlg extends CommDialog{

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm);
        _min = 0;
        _value = 0;
        _max = 0;

        _screen = s;
#if neko
        TXT = "unknow";
#else
        TXT = "未知";
#end
    }

    var _screen:Screen;
    var _less:Sprite;
    var _more:Sprite;
    var _s:Sprite;
    var _c:Sprite;
    var _v:EmbedTextField;
    var _value:Int;
    var _max:Int ;
    var _min:Int ;
    static var POSX:Int = 400;
    static var WIDTH:Int = 300;

    var _promt:EmbedTextField;
    var TXT:String;

    override function show(){
        if ( _s != null) {
            if ( _c != null){ _s.removeChild(_c); }
            if ( _less != null){ _s.removeChild(_less); }
            if ( _more != null){ _s.removeChild(_more); }
            if ( _v!= null){ _s.removeChild(_v); }
            if ( _promt !=null) _s.removeChild(_promt);

            _promt= new EmbedTextField();
            _promt.selectable = false;
            _promt.text = TXT;
            _promt.scaleX = 3;
            _promt.scaleY = 3;
            _promt.width = 150;
            _promt.height= 16;
            _s.addChild( _promt);

            _v= new EmbedTextField();
            _v.selectable = false;
            _v.text = "0";
            _v.scaleX = 3;
            _v.scaleY = 3;
            _v.width = 100;
            _v.height= 16;
            _v.x = nme.Lib.current.stage.stageWidth - 50;
            _s.addChild( _v);

            _c = new Sprite();
            _c.graphics.beginFill(0x888888);
            _c.graphics.drawRect( POSX, 10,  WIDTH, 30);
            _c.addEventListener( MouseEvent.MOUSE_DOWN, onBarMouseDown);
            _s.addChild(_c);

            _less = new Sprite();
            _less.graphics.beginFill(0x888888);
            _less.graphics.moveTo( POSX -10, 10 );
            _less.graphics.lineTo( POSX -25, 25 );
            _less.graphics.lineTo( POSX -10, 40);
            _less.graphics.lineTo( POSX -10, 10);
            _less.graphics.endFill();
            _less.addEventListener( MouseEvent.MOUSE_DOWN, onLessMouseClick);
            _s.addChild(_less);

            _more= new Sprite();
            _more.graphics.beginFill(0x888888);
            _more.graphics.moveTo( POSX+WIDTH +10, 10 );
            _more.graphics.lineTo( POSX+WIDTH +25, 25 );
            _more.graphics.lineTo( POSX+WIDTH +10, 40);
            _more.graphics.lineTo( POSX+WIDTH +10, 10);
            _more.graphics.endFill();
            _more.addEventListener( MouseEvent.MOUSE_DOWN, onMoreMouseClick);
            _s.addChild(_more);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        calValueAndDraw();
        return super.show();
    }
    override function hide(){
        if ( _s != null ) {
            if( _c != null) {_s.removeChild(_c); _c.removeEventListener(  MouseEvent.MOUSE_DOWN, onBarMouseDown );_c = null;}
            if( _v != null) {_s.removeChild(_v); _v = null;}
            if( _less != null) {_s.removeChild(_less); _less.removeEventListener( MouseEvent.MOUSE_DOWN, onLessMouseClick);_less = null;}
            if( _more != null) {_s.removeChild(_more); _more.removeEventListener( MouseEvent.MOUSE_DOWN, onMoreMouseClick);_more = null;}
            if ( _promt != null){ _s.removeChild(_promt); _promt = null;}
        }
        return super.hide();
    }
    function onLessMouseClick( evt:MouseEvent){ 
        --_value;
        if ( _value < _min) _value = _min;
        calValueAndDraw();
    }
    function onMoreMouseClick( evt:MouseEvent){ 
        ++_value;
        if ( _value > _max) _value = _max;
        calValueAndDraw();
    }
    function calValueAndDraw(){
        if (_max == 0 ) return;
        var percent = WIDTH / (_max - _min);
        var lw = percent * (_value - _min);
        var rw = percent * (_max - _value);
        //drawBar( Math.round(lw), Math.round(rw));
        drawBar( lw, rw);
        dispatch( _value);
    }

    public function onBarMouseDown( evt:MouseEvent){
        if ( _s != null && _c != null){
            var lw = evt.localX - POSX;
            var rw = POSX + WIDTH - evt.localX;

            var lp:Float= lw / WIDTH;
            _value = Math.round(lp * (_max - _min)) + _min;
            //drawBar( Math.round(lw), Math.round(rw));
            drawBar( lw, rw);
            dispatch( _value);
        }
    }
    public function dispatch( value:Int):Void{
    }

    function drawBar( leftWidth:Float, rightWidth:Float){
        if (  _c != null){
            trace(leftWidth);
            trace(rightWidth);
            _c.graphics.clear();
            _c.graphics.beginFill(0x00FF00);
            _c.graphics.drawRect( POSX, 10, leftWidth, 30 );
            _c.graphics.endFill();
            _c.graphics.beginFill(0x888888);
            _c.graphics.drawRect( POSX + leftWidth, 10, rightWidth, 30 );
            _c.graphics.endFill();
            _v.text = "" + _value;
        }
    }

    public function createElement():Sprite{
        _s = new Sprite();
        return _s;
    }
}
