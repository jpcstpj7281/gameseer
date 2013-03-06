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

class SpecialAmplificationSetting extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new AmplificationHPercent(_listDialogMgr, s);
        i =new AmplificationVPercent(_listDialogMgr, s);
        i =new AmplificationHMovment(_listDialogMgr, s);
        i =new AmplificationVMovment(_listDialogMgr, s);
#if neko
        TXT= "Amplification Setting";
#else
        TXT= "放大设定";
#end
    }
}
