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

class OsdSysDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new SysModel(_listDialogMgr);
        i =new SysMachinePosNum(_listDialogMgr);
        i =new SysSource(_listDialogMgr);
        i =new SysImgResolution(_listDialogMgr);
        i =new SysRunningTime(_listDialogMgr);
        i =new SysSoftwareVersion(_listDialogMgr);
        i =new SysLEDLightTemperature(_listDialogMgr);
#if neko
        TXT= "System Setting";
#else
        TXT= "系统设定";
#end
    }
}
