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

class ProjModeSelectDlg extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());
        _value = 0;
#if neko
        _values.push("Normal Mode");
        _values.push("Test Mode");
        TXT= "Select Mode";
#else
        _values.push("普通");
        _values.push("测试");
        TXT= "选择模式";
#end
    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var shift:Int = 0xc0 ;
        if ( _value == 0){
            shift = 0xc0;
        }else{
            shift = 0x20;
        }
        bs.addByte( shift);
        _screen.setOsd( Std.string(0x02), Std.string(1), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }
}
