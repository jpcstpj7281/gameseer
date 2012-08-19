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

class ValueSwitchDlg extends CommDialog{

    public function new ( dm:CommDialogMgr){
        super(dm);
        _value = 0;
        _values = new Array<String>();
    }

    var _less:Sprite;
    var _more:Sprite;
    var _g:Sprite;
    var _c:Sprite;
    var _v:EmbedTextField;
    var _value:Int;
    var _values:Array<String>;
    static var POSX:Int = 400;
    static var WIDTH:Int = 300;
    override function show(){
        if ( _g != null) {
            if ( _less != null){ _g.removeChild(_less); }
            if ( _more != null){ _g.removeChild(_more); }
            if ( _v!= null){ _g.removeChild(_v); }

            _v= new EmbedTextField();
            _v.selectable = false;
            _v.scaleX = 3;
            _v.scaleY = 3;
            _v.width = 50;
            _v.height= 20;
            _v.x = POSX+WIDTH/3;
            _g.addChild( _v);

            _less = new Sprite();
            _less.graphics.beginFill(0x888888);
            _less.graphics.moveTo( POSX -10, 10 );
            _less.graphics.lineTo( POSX -25, 25 );
            _less.graphics.lineTo( POSX -10, 40);
            _less.graphics.lineTo( POSX -10, 10);
            _less.graphics.endFill();
            _less.addEventListener( MouseEvent.MOUSE_DOWN, onLessMouseClick);
            _g.addChild(_less);

            _more= new Sprite();
            _more.graphics.beginFill(0x888888);
            _more.graphics.moveTo( POSX+WIDTH +10, 10 );
            _more.graphics.lineTo( POSX+WIDTH +25, 25 );
            _more.graphics.lineTo( POSX+WIDTH +10, 40);
            _more.graphics.lineTo( POSX+WIDTH +10, 10);
            _more.graphics.endFill();
            _more.addEventListener( MouseEvent.MOUSE_DOWN, onMoreMouseClick);
            _g.addChild(_more);
            if (_values!= null &&  _values.length > 0){ _v.text = _values[_value]; }
        }
        return super.show();
    }
    override function hide(){
        if ( _g != null && _c != null) {
            _less.removeEventListener( MouseEvent.MOUSE_DOWN, onLessMouseClick);
            _more.removeEventListener( MouseEvent.MOUSE_DOWN, onMoreMouseClick);
            _g.removeChild(_less);
            _g.removeChild(_more);
            _g.removeChild(_v);
            _v = null;
            _less = null;
            _more = null;
        }
        return super.hide();
    }
    function onLessMouseClick( evt:MouseEvent){ 
        if ( _values.length == 0 ) return;
        --_value;
        if ( _value < 0) _value = _values.length -1;
        calValueAndDraw();
    }
    function onMoreMouseClick( evt:MouseEvent){ 
        if ( _values.length == 0 ) return;
        ++_value;
        if ( _value >= _values.length) _value = 0;
        calValueAndDraw();
    }
    function calValueAndDraw(){
        if (_v == null) return;
        _v.text = _values[_value];
    }
    public function createElement():Sprite{
        var s:Sprite = new Sprite();
        _g = new Sprite();
        s.addChild (_g);
        return s;
    }
}
