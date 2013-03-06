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

class OsdGroupDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s){
        super(dm);
        addChild( createElement());

        var i:CommDialog = new GroupHorizontalNum(_listDialogMgr, s);
        i =new GroupVerticalNum(_listDialogMgr, s);
        i =new GroupHorizontalIndex(_listDialogMgr, s);
        i =new GroupVerticalIndex(_listDialogMgr, s);
        i =new GroupMachineNumber(_listDialogMgr, s);
#if neko
        TXT= "Group";
#else
        TXT= "组屏设定";
#end
    }
}
