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
import haxe.io.BytesBuffer;

class HSGBlue extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s:Screen, hsg:SpecialHSGSetting){
        super(dm);
        addChild( createElement());
        new HSGBlueGain(_listDialogMgr, s, hsg);
        new HSGBlueSat(_listDialogMgr, s, hsg);
        new HSGBlueHue(_listDialogMgr, s, hsg);
#if neko
        TXT="HSG Blue";
#else
        TXT="HSG Blue";
#end
    }
}
