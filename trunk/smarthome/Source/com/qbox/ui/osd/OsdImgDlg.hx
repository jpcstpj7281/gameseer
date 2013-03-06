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

class OsdImgDlg extends OsdListDlg{


    public function new ( dm:ListDialogMgr, s:Screen){
        super(dm);
        addChild( createElement());

        var i:CommDialog = new ImgLightnessDlg(_listDialogMgr, s);
        i = new ImgContrastDlg(_listDialogMgr, s);
        i =new ImgInputFitnessDlg(_listDialogMgr, s);
        i =new ImgVideoSettingDlg(_listDialogMgr, s);
        i =new ImgColorTemperatureDlg(_listDialogMgr, s);
        i =new ImgColorGamutDlg(_listDialogMgr, s);
        i =new ImgOverlapSettingDlg(_listDialogMgr, s);
        i =new ImgDynamicBlackSettingDlg(_listDialogMgr, s);
        i =new ImgDlpSettingDlg(_listDialogMgr, s);
#if neko
        TXT="Image";
#else
        TXT="图像设定";
#end
    }

}
