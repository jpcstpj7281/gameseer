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

class SysRunningTime extends OsdCommDlg{

    public function new ( dm:CommDialogMgr, s){
        super(dm, s);
        addChild( createElement());

#if neko
        TXT= "System running Time";
#else
        TXT= "系统运行时间";
#end
    }
}
