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

class OsdImgDlg extends ListDialog{

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
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var img= new EmbedTextField();
        img.selectable = false;
#if neko
        img.text = "img";
#else
        img.text = "图像设定";
#end
        img.scaleX = 3;
        img.scaleY = 3;
        img.width = 50;
        img.height= 20;
        s.addChild( img);

        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
