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

import com.qbox.logic.Screen;

class TestModeFrontColor extends OsdListDlg{


    public function new ( dm:ListDialogMgr, s:Screen){
        super(dm);
        addChild( createElement());

        var i = new TestModeFrontGreen(_listDialogMgr, s);
        new TestModeFrontRed(_listDialogMgr, s, i);
        new TestModeFrontBlue(_listDialogMgr, s, i);
#if neko
        TXT="Front Color";
#else
        TXT="前景颜色";
#end
    }

}
