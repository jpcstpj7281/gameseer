package com.qbox.ui.osd;

import com.qbox.logic.QboxMgr;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import base.ui.ListDialog;
import base.ui.CommDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialogMgr;

import com.qbox.logic.Qbox;
import com.qbox.logic.Screen;
import haxe.io.BytesBuffer;

class TestModeTestPattern extends ValueSwitchDlg{
    var _period:Int;
    var _width:Int;

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());
        _value = 0;
        _period = 0xF;
        _width = 0x0;
        _values.push("Solid Field");
        _values.push("Horizontal Ramp");
        _values.push("Vertical Ramp");
        _values.push("Horizontal Lines");
        _values.push("Diagonal Lines");
        _values.push("Vertical Lines");
        _values.push("Grid Lines");
        _values.push("Checkerboard Lines");
#if neko
        TXT= "Test Pattern";
#else
        TXT= "测试模式";
#end
    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        bs.addByte( _value );
        bs.addByte(( _period << 4) + _width );
        _screen.setOsd( Std.string(0x33), Std.string(2), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }
    public function setPeriod( value:Int){
        _period= value;
        dispatch( _value);
    }
    public function setWidth( value:Int){
        _width = value;
        dispatch( _value);
    }
}
