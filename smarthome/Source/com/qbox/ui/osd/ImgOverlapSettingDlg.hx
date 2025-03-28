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

class ImgOverlapSettingDlg extends ValueSwitchDlg{
    var _colorTemper:ImgColorTemperatureDlg;

    public function new ( dm:CommDialogMgr, s:Screen, colorTemper:ImgColorTemperatureDlg){
        super(dm, s);
        addChild( createElement());

        _value = 0;
        _values.push("0%");
        _values.push("30%");
        _values.push("50%");
        _colorTemper = colorTemper;
#if neko
        TXT= "Overlap Setting";
#else
        TXT= "重叠设定";
#end
    }
    override function dispatch(value:Int):Void{ _colorTemper.setOverlap( value); }
}
