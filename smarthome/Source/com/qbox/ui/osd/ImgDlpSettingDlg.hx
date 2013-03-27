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
    public function new ( dm:ListDialogMgr, s:Screen, b:ImgLightnessDlg, c:ImgContrastDlg){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new DlpSettingRedLightness(_listDialogMgr, s, b);
        i =new DlpSettingGreenLightness(_listDialogMgr, s, b);
        i =new DlpSettingBlueLightness(_listDialogMgr, s, b);
        i =new DlpSettingRedContrast(_listDialogMgr, s, c);
        i =new DlpSettingGreenContrast(_listDialogMgr, s, c);
        i =new DlpSettingBlueContrast(_listDialogMgr, s, c);
#if neko
        TXT= "DLP setting";
#else
        TXT= "DLP设定";
#end
    }

}
