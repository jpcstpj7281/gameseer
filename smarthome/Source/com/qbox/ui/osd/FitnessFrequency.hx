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

class FitnessFrequency extends ValueBarDlg{

    public function new ( dm:CommDialogMgr, s){
        super(dm, s);
        addChild( createElement());
        _value = 0;
        _max = 200;
#if neko
        TXT= "Frequency";
#else
        TXT= "频率";
#end
    }
}
