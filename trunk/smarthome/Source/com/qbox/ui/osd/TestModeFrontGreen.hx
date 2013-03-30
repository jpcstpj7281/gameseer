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
import base.ui.CommDialog;

import base.ui.CommDialogMgr;
import com.qbox.logic.Qbox;
import com.qbox.logic.Channel;
import com.qbox.logic.Screen;
import haxe.io.BytesBuffer;

class TestModeFrontGreen extends ValueBarDlg{
    var _red:Int;
    var _blue:Int;

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm,s );
        addChild( createElement());
        _value = 0x1ff;
        _max= 0x1ff;
        _min= 0x0;
        _red = 0xff;
        _blue = 0xff;

#if neko
        TXT= "Green";
#else
        TXT= "绿";
#end
    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        bs.addByte( _value >> 8);
        bs.addByte( _value);
        bs.addByte( _red);
        bs.addByte( _blue);
        _screen.setOsd( Std.string(0x12), Std.string(4), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }

    public function setRed(value:Int):Void{ _red = value; dispatch(_value);}
    public function setBlue(value:Int):Void{ _blue = value; dispatch(_value);}
}
