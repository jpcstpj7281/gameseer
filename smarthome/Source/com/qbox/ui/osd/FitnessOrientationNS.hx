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

import com.qbox.logic.Screen;
import haxe.io.BytesBuffer;

class FitnessOrientationNS extends ValueSwitchDlg{
    var _ew:Int;

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());
        _value = 1;
        _ew = 0;
#if neko
        _values.push("flip");
        _values.push("normal");
        TXT= "Vertical";
#else
        _values.push("正");
        _values.push("反");
        TXT= "垂直";
#end
    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var shift:Int = value | (_ew <<1);
        trace( shift);
        bs.addByte( shift);
        _screen.setOsd( Std.string(0x03), Std.string(1), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }
    public function setEW( value:Int){
        _ew = value;
        dispatch( _value);
    }
}
