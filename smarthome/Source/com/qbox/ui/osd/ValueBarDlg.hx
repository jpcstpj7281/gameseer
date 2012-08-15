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
import com.qbox.logic.Channel;

class ValueBarDlg extends CommDialog{

    public function new ( dm:CommDialogMgr){
        super(dm);
        _min = 0;
    }

    var _g:Sprite;
    var _c:Sprite;
    var _v:EmbedTextField;
    var _value:Int;
    var _max:Int ;
    var _min:Int ;
    static var POSX:Int = 400;
    static var WIDTH:Int = 300;
    override function show(){
        if ( _g != null) {
            if ( _c != null){
                _g.removeChild(_c);
            }
            _c = new Sprite();
            _c.graphics.beginFill(0x888888);
            _c.graphics.drawRect( POSX, 10,  WIDTH, 30);
            _c.addEventListener( MouseEvent.MOUSE_DOWN, onBarMouseDown);
            _g.addChild(_c);
        }
        return super.show();
    }
    override function hide(){
        if ( _g != null && _c != null) {
            _c.removeEventListener(  MouseEvent.MOUSE_DOWN, onBarMouseDown );
            _g.removeChild(_c);
            _c = null;
        }
        return super.hide();
    }
    public function onBarMouseDown( evt:MouseEvent){
        if ( _g != null && _c != null){
            var lw = evt.localX - POSX;
            var rw = POSX + WIDTH - evt.localX;
            _c.graphics.clear();
            _c.graphics.beginFill(0x00FF00);
            _c.graphics.drawRect( POSX, 10, lw, 30 );
            _c.graphics.endFill();
            _c.graphics.beginFill(0x888888);
            _c.graphics.drawRect( evt.localX , 10, rw , 30 );
            _c.graphics.endFill();

            var lp:Float= lw / WIDTH;
            _value = Math.round(lp * (_max - _min)) + _min;
            _v.text = "" + _value;
        }
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();
        _g = new Sprite();
        s.addChild (_g);

        _v= new EmbedTextField();
        _v.selectable = false;
        _v.text = "0";
        _v.scaleX = 3;
        _v.scaleY = 3;
        _v.width = 100;
        _v.height= 20;
        _v.x = nme.Lib.current.stage.stageWidth - 50;

        _less = new Sprite();

        s.addChild( _v);

        return s;
    }
}
