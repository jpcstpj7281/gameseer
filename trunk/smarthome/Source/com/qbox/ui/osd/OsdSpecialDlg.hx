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

        //new SpecialStartUpDelayTime(_listDialogMgr, s);
        //new SpecialImgFrameworkLock(_listDialogMgr, s);
        //new SpecialRGBFirstTimeAutoAdjust(_listDialogMgr, s);
        //new SpecialAGCSetting(_listDialogMgr, s);
        //new SpecialTestFrame(_listDialogMgr, s);
        //new SpecialHSGAdjustSetting(_listDialogMgr, s);
        //new SpecialForceModeSetting(_listDialogMgr, s);
        //new SpecialDVIDigitalEQSetting(_listDialogMgr, s);
        //new SpecialAmplificationSetting(_listDialogMgr, s);
        new SpecialFanSetting(_listDialogMgr, s);
        new OsdProjModeDlg(_listDialogMgr, s);
        new SpecialHSGSetting(_listDialogMgr, s);
        new SpecialGamma(_listDialogMgr, s);
#if neko
        TXT= "Special Setting";
#else
        TXT= "特殊设定";
#end
    }
}
