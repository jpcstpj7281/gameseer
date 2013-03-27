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
import com.qbox.logic.Screen;

class ProjModeTestMode extends OsdListDlg{


    public function new ( dm:ListDialogMgr, s:Screen){
        super(dm);
        addChild( createElement());

        var i= new TestModeTestPattern(_listDialogMgr, s);
        new TestModePeriod(_listDialogMgr, s, i);
        new TestModeWidth(_listDialogMgr, s, i);
        new TestModeFrontColor(_listDialogMgr, s);
#if neko
        TXT="Test Mode Setting";
#else
        TXT="测试模式设置";
#end
    }

}
