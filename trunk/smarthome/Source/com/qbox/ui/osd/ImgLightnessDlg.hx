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
import com.qbox.logic.Screen;

import haxe.io.Bytes;
import haxe.io.BytesBuffer;

class ImgLightnessDlg extends ValueBarDlg{
    var _red:Int;
    var _green:Int;
    var _blue:Int;

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());

        _value = 0;
        _red = 0;
        _green = 0;
        _blue = 0;
        _max = 255;
#if neko
        TXT= "Blightness";
#else
        TXT= "亮度";
#end

    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var vred:Int = _red+_value;
        var vgreen:Int = _green+_value;
        var vblue:Int = _blue+_value;
        if ( vred > 255) vred = 255;
        if ( vgreen> 255) vgreen= 255;
        if ( vblue> 255) vblue= 255;
        var shiftr:Int=0;
        shiftr = vred<< 2;
        var shiftg:Int=0; 
        shiftg = vgreen<<2;
        var shiftb:Int=0; 
        shiftb = vblue<< 2;
        bs.addByte(Std.int(shiftg >> 8));
        bs.addByte(Std.int(shiftg));
        bs.addByte(Std.int(shiftr >> 8));
        bs.addByte(Std.int(shiftr));
        bs.addByte(Std.int(shiftb >> 8));
        bs.addByte(Std.int(shiftb));
        //bs.addByte(shiftr >> 8);
        //bs.addByte(shiftr);
        //bs.addByte(shiftb >> 8);
        //bs.addByte(shiftb);
        _screen.setOsd( Std.string(0x0a), Std.string(6), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }
    
    public function setGreen(value:Int){ _green = value; dispatch(_value); }
    public function setRed(value:Int){ _red= value; dispatch(_value); }
    public function setBlue(value:Int){ _blue= value; dispatch(_value); }
}
