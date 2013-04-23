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
import com.qbox.logic.Channel;
import haxe.io.BytesBuffer;

class FitnessVPos extends ValueBarDlg{

    public function new ( dm:CommDialogMgr, s){
        super(dm, s);
        addChild( createElement());

        _value = 0;
        _max = 255;
        _min = -255;
#if neko
        TXT= "Vertical Position";
#else
        TXT= "垂直位置";
#end
    }
    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var shift:Int =  _value;
        trace( shift);
        bs.addByte(shift >> 24);
        bs.addByte(shift);
        //bs.addByte(0x16);
        //bs.addByte(0x16);
        _screen.setOsd( Std.string(0x05), Std.string(2), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }
}
