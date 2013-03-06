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

class ImgVideoSettingDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s:Screen){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new VideoSettingLightnessDlg(_listDialogMgr, s);
        i =new VideoSettingContrast(_listDialogMgr, s);
        i =new VideoSettingDefinition(_listDialogMgr, s);
        i =new VideoSettingColor(_listDialogMgr, s);
        i =new VideoSettingColorTone(_listDialogMgr, s);
        i =new VideoSettingForceMode(_listDialogMgr, s);
        i =new VideoSettingInputBlackLevel(_listDialogMgr, s);
        i =new VideoSettingEnhanceMode(_listDialogMgr, s);
#if neko
        TXT= "Video Setting";
#else
        TXT= "视频设定";
#end
    }

}
