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

class ValueSwitchDlg extends CommDialog{

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm);
        _value = 0;
        _values = new Array<String>();

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
    var _values:Array<String>;
    static var POSX:Int = 400;
    static var WIDTH:Int = 300;

    var _promt:EmbedTextField;
    var TXT:String;

    override function show(){
        if ( _s != null) {
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
            _v.scaleX = 3;
            _v.scaleY = 3;
            _v.width = 50;
            _v.height= 16;
            _v.x = POSX+WIDTH/3;
            _s.addChild( _v);

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
            if (_values!= null &&  _values.length > 0){ _v.text = _values[_value]; }
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null ) {
            if( _less !=null){_less.removeEventListener( MouseEvent.MOUSE_DOWN, onLessMouseClick);_s.removeChild(_less);_less = null;}
            if( _more != null){_more.removeEventListener( MouseEvent.MOUSE_DOWN, onMoreMouseClick); _s.removeChild(_more); _more = null;}
            if( _v != null){ _s.removeChild(_v); _v = null;}
            if ( _promt != null){ _s.removeChild(_promt); _promt = null;}
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
        _s = new Sprite();
        return _s;
    }
}
