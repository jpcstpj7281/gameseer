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

class SpecialHSGAdjustSetting extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr, s){
        super(dm, s);
        addChild( createElement());

        _values.push("开启");
        _values.push("关闭");
#if neko
        TXT= "HSG Adjust Setting";
#else
        TXT= "HSG调节设定";
#end
    }
}
