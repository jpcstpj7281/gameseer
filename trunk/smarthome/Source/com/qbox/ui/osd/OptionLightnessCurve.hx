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

class OptionLightnessCurve extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr, s){
        super(dm, s);
        addChild( createElement());

        _values.push("NORMAL");
        _values.push("FILM");
        _values.push("GRAPHIC");
        _values.push("VIDEO");
        _values.push("LINEAR");
#if neko
        TXT= "Lightness Curve";
#else
        TXT= "亮度曲线";
#end
    }
}
