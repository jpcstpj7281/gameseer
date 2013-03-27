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
import com.qbox.logic.Screen;

class OsdProjModeDlg extends OsdListDlg{


    public function new ( dm:ListDialogMgr, s:Screen){
        super(dm);
        addChild( createElement());

        new ProjModeSelectDlg(_listDialogMgr, s);
        new ProjModeTestMode(_listDialogMgr, s);
#if neko
        TXT="Projection Mode";
#else
        TXT="投影模式";
#end
    }

}
