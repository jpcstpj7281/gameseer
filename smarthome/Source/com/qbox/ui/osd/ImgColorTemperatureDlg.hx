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

class ImgColorTemperatureDlg extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());
        _value = 0;
        _values.push("3200K");
        _values.push("6500K");
        _values.push("7500K");
        _values.push("9300K");
#if neko
        TXT= "Color Temperature";
#else
        TXT= "色温";
#end
    }
}
