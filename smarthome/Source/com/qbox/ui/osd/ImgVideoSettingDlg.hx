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

class ImgVideoSettingDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new VideoSettingLightnessDlg(_listDialogMgr);
        i =new VideoSettingContrast(_listDialogMgr);
        i =new VideoSettingDefinition(_listDialogMgr);
        i =new VideoSettingColor(_listDialogMgr);
        i =new VideoSettingColorTone(_listDialogMgr);
        i =new VideoSettingForceMode(_listDialogMgr);
        i =new VideoSettingInputBlackLevel(_listDialogMgr);
        i =new VideoSettingEnhanceMode(_listDialogMgr);
#if neko
        TXT= "Video Setting";
#else
        TXT= "视频设定";
#end
    }

}
