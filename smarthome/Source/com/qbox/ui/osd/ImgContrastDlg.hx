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

class ImgContrastDlg extends ValueBarDlg{
    var _red:Int;
    var _green:Int;
    var _blue:Int;

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm,s );
        addChild( createElement());
        _value = 50;
        _red = 50;
        _green  = 50;
        _blue= 50;
        _max= 100;

#if neko
        TXT= "Contrast";
#else
        TXT= "对比度";
#end
    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var shiftr = Std.int(_red * _value /50);
        var shiftg = Std.int(_green * _value /50);
        var shiftb = Std.int(_blue * _value /50);
        if(shiftr >100) shiftr = 100;
        if(shiftg >100) shiftg = 100;
        if(shiftb >100) shiftb = 100;
        bs.addByte( 50+shiftg);
        bs.addByte( 50+shiftr);
        bs.addByte( 50+shiftb);
        _screen.setOsd( Std.string(0x01), Std.string(3), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }

    public function setRed(value:Int){ _red = value; dispatch(_value); }
    public function setGreen(value:Int){ _green = value; dispatch(_value); }
    public function setBlue(value:Int){ _blue = value; dispatch(_value); }
}
