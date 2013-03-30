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

class DlpSettingRedLightness extends ValueBarDlg{

    var _brightness:ImgLightnessDlg;
    public function new ( dm:CommDialogMgr, s, brightness:ImgLightnessDlg){
        super(dm, s);
        addChild( createElement());

        _brightness = brightness;
        _value = 0;
        _max = 255;
        _min = -255;
#if neko
        TXT= "Red Lightness";
#else
        TXT= "红色亮度值";
#end
    }
    override function dispatch(value:Int):Void{ _brightness.setRed(value); }
}
