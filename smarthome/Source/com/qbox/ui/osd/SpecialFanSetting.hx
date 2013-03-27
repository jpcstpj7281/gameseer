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

class SpecialFanSetting extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr, s){
        super(dm, s);
        addChild( createElement());

#if neko
        _values.push("Auto");
        _values.push("Off");
        TXT= "Fan Setting";
#else
        _values.push("自动");
        _values.push("关闭");
        TXT= "风扇设定";
#end
    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var shift:Int = _value;
        trace( shift);
        if ( shift ==0){
            bs.addByte( 0x64);
            bs.addByte( 0x64);
            bs.addByte( 0x64);
        }else{
            bs.addByte( 0x16);
            bs.addByte( 0x16);
            bs.addByte( 0x16);
        }
        _screen.setOsd( Std.string(0x10), Std.string(3), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }

}
