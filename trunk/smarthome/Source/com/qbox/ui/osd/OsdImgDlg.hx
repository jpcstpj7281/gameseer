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

class OsdImgDlg extends OsdListDlg{


    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

        var i:CommDialog = new ImgLightnessDlg(_listDialogMgr);
        i = new ImgContrastDlg(_listDialogMgr);
        i =new ImgInputFitnessDlg(_listDialogMgr);
        i =new ImgVideoSettingDlg(_listDialogMgr);
        i =new ImgColorTemperatureDlg(_listDialogMgr);
        i =new ImgColorGamutDlg(_listDialogMgr);
        i =new ImgOverlapSettingDlg(_listDialogMgr);
        i =new ImgDynamicBlackSettingDlg(_listDialogMgr);
        i =new ImgDlpSettingDlg(_listDialogMgr);
#if neko
        TXT="Image";
#else
        TXT="图像设定";
#end
    }

}
