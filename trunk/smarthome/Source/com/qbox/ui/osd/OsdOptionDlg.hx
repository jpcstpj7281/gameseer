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

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

        var i:CommDialog = new OptionLanguage(_listDialogMgr);
        i =new OptionImgDirection(_listDialogMgr);
        i =new OptionBitRate(_listDialogMgr);
        i =new OptionLightnessCurve(_listDialogMgr);
        i =new OptionMenuHorizontalPos(_listDialogMgr);
        i =new OptionMenuVerticalPos(_listDialogMgr);
        i =new OptionRecoverPreset(_listDialogMgr);
#if neko
        TXT= "Option";
#else
        TXT= "选项设定";
#end
    }
}
