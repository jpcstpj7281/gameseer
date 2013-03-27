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

        var b= new ImgLightnessDlg(_listDialogMgr, s);
        var c = new ImgContrastDlg(_listDialogMgr, s);
        //i =new ImgInputFitnessDlg(_listDialogMgr, s);
        //i =new ImgVideoSettingDlg(_listDialogMgr, s);
        var ct =new ImgColorTemperatureDlg(_listDialogMgr, s);
        new ImgColorGamutDlg(_listDialogMgr, s, ct);
        new ImgOverlapSettingDlg(_listDialogMgr, s, ct);
        new ImgDynamicBlackSettingDlg(_listDialogMgr, s);
        new ImgDlpSettingDlg(_listDialogMgr, s, b, c);
#if neko
        TXT="Image";
#else
        TXT="图像设定";
#end
    }

}
