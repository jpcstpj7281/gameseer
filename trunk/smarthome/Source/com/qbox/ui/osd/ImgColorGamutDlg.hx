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
import com.qbox.logic.Screen;

class ImgColorGamutDlg extends ValueSwitchDlg{
    var _colorTemper:ImgColorTemperatureDlg;

    public function new ( dm:CommDialogMgr, s:Screen, colorTemper:ImgColorTemperatureDlg){
        super(dm, s);
        addChild( createElement());

        _value = 0;
        _values.push("R709");
        _values.push("NTSC");
        _values.push("WIDE");
        _colorTemper = colorTemper;
#if neko
        TXT= "Color Gamut";
#else
        TXT= "色域";
#end
    }
    override function dispatch(value:Int):Void{ _colorTemper.setGamut( value); }
}
