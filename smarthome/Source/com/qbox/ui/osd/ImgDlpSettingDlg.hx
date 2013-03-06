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

class ImgDlpSettingDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s:Screen){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new DlpSettingRedLightness(_listDialogMgr, s);
        i =new DlpSettingGreenLightness(_listDialogMgr, s);
        i =new DlpSettingBlueLightness(_listDialogMgr, s);
        i =new DlpSettingRedContrast(_listDialogMgr, s);
        i =new DlpSettingGreenContrast(_listDialogMgr, s);
        i =new DlpSettingBlueContrast(_listDialogMgr, s);
#if neko
        TXT= "DLP setting";
#else
        TXT= "DLP设定";
#end
    }

}
