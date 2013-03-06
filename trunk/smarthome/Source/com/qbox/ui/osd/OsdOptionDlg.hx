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

class OsdOptionDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s){
        super(dm);
        addChild( createElement());

        var i:CommDialog = new OptionLanguage(_listDialogMgr, s);
        i =new OptionImgDirection(_listDialogMgr, s);
        i =new OptionBitRate(_listDialogMgr, s);
        i =new OptionLightnessCurve(_listDialogMgr, s);
        i =new OptionMenuHorizontalPos(_listDialogMgr, s);
        i =new OptionMenuVerticalPos(_listDialogMgr, s);
        i =new OptionRecoverPreset(_listDialogMgr, s);
#if neko
        TXT= "Option";
#else
        TXT= "选项设定";
#end
    }
}
