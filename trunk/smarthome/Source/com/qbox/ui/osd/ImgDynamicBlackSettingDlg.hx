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

import com.qbox.logic.Qbox;
import com.qbox.logic.Channel;
import haxe.io.BytesBuffer;

class ImgDynamicBlackSettingDlg extends ValueBarDlg{

    public function new ( dm:ListDialogMgr, s){
        super(dm,s );
        addChild( createElement());

        _value = 1;
        _max= 254;
        _min= 1;
#if neko
        TXT= "Dynamic Black Setting";
#else
        TXT= "DYNAMIC BLACK 设定";
#end
    }
    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var shift:Int = _value;
        trace( shift);
        bs.addByte( 0);
        bs.addByte( shift);
        _screen.setOsd( Std.string(0x4a), Std.string(2), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }
}
