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

class GroupVerticalNum extends ValueBarDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());
        _value = 0;
        _min= 1;
        _max= 8;
#if neko
        TXT= "Machine Vertical Number";
#else
        TXT= "单机垂直序号";
#end
    }
}
