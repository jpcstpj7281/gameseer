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

class TestModeFrontRed extends ValueBarDlg{
    var _frontGreen:TestModeFrontGreen;

    public function new ( dm:CommDialogMgr, s:Screen, frontGreen:TestModeFrontGreen){
        super(dm,s );
        addChild( createElement());
        _value = 0xff;
        _max= 0xff;
        _min= 0x0;
        _frontGreen = frontGreen;
#if neko
        TXT= "Red";
#else
        TXT= "红前景色";
#end
    }

    override function dispatch(value:Int):Void{ _frontGreen.setRed(value); }
}
