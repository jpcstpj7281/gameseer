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

class ImgColorTemperatureDlg extends ValueSwitchDlg{

    var _overlap:Int;
    var _gamut:Int;


    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());
        _value = 0;
        _overlap = 0;
        _gamut = 0;
        _values.push("9300K");
        _values.push("7500K");
        _values.push("6500K");
        _values.push("3200K");
#if neko
        TXT= "Color Temperature";
#else
        TXT= "色温";
#end
    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var shift:Int = 0x80 + _value + _overlap * 12 + _gamut * 4 ;
        trace( shift);
        bs.addByte( shift);
        _screen.setOsd( Std.string(0x0d), Std.string(1), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }
    public function setGamut( value:Int){
        _gamut = value;
        dispatch( _value);
    }
    public function setOverlap( value:Int){
        _overlap = value;
        dispatch( _value);
    }
}
