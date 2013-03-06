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

class OsdSourceDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s){
        super(dm);
        addChild( createElement());

        var i:CommDialog = new SourceOption(_listDialogMgr, s);
        i = new SourceChildFrameSourceOption(_listDialogMgr, s);
        i =new SourceChildFrame2SourceOption(_listDialogMgr, s);
        i =new SourceChildFrameSetting(_listDialogMgr, s);
        i =new SourceChildFrameSetting2(_listDialogMgr, s);
        i =new SourceInputSourceStatusRecord(_listDialogMgr, s);
        i =new SourceUserMode(_listDialogMgr, s);
#if neko
        TXT= "Source";
#else
        TXT= "信号源设定";
#end
    }
}
