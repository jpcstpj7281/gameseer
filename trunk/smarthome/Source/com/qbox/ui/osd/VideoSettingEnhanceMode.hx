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

class VideoSettingEnhanceMode extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());
#if neko
        _values.push("on");
        _values.push("off");
#else
        _values.push("开启");
        _values.push("关闭");
#end
#if neko
        TXT= "Enhance Mode";
#else
        TXT= "扩大模式";
#end
    }
}
