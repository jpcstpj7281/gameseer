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

class OsdSpecialDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s){
        super(dm);
        addChild( createElement());

        var i:CommDialog = new SpecialStartUpDelayTime(_listDialogMgr, s);
        i =new SpecialImgFrameworkLock(_listDialogMgr, s);
        i =new SpecialRGBFirstTimeAutoAdjust(_listDialogMgr, s);
        i =new SpecialAGCSetting(_listDialogMgr, s);
        i =new SpecialTestFrame(_listDialogMgr, s);
        i =new SpecialHSGAdjustSetting(_listDialogMgr, s);
        i =new SpecialForceModeSetting(_listDialogMgr, s);
        i =new SpecialDVIDigitalEQSetting(_listDialogMgr, s);
        i =new SpecialAmplificationSetting(_listDialogMgr, s);
        i =new SpecialFanSetting(_listDialogMgr, s);
#if neko
        TXT= "Special Setting";
#else
        TXT= "特殊设定";
#end
    }
}
