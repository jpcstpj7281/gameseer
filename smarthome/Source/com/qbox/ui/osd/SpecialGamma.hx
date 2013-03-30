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
import haxe.io.BytesBuffer;

class SpecialGamma extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr, s){
        super(dm, s);
        addChild( createElement());
        _value = 5;

        _values.push("TI Film");
        _values.push("IT Graphics Enhanced");
        _values.push("TI Video Enhanced");
        _values.push("Linear");
        _values.push("OEM");
#if neko
        _values.push("Off");
        TXT= "Gamma";
#else
        _values.push("关闭");
        TXT= "亮度曲线";
#end
    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var shift:Int = _value;
        trace( shift);
        if ( shift == 5){
            bs.addByte( 0xc0);
            bs.addByte( 0x00);
        }else{
            bs.addByte( 0x40);
            bs.addByte( _value);
        }
        _screen.setOsd( Std.string(0x09), Std.string(2), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }
}
