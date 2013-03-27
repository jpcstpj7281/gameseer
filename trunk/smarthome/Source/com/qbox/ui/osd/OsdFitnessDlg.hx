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

class OsdFitnessDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s){
        super(dm);
        addChild( createElement());

        //var i:CommDialog = new FitnessAspectRatio(_listDialogMgr, s);
        //i = new FitnessAutoAdjust(_listDialogMgr, s);
        new FitnessHPos(_listDialogMgr, s);
        new FitnessVPos(_listDialogMgr, s);
        //i =new FitnessInputSourceHPos(_listDialogMgr, s);
        //i =new FitnessInputSourceVPos(_listDialogMgr, s);
        //i =new FitnessPhase(_listDialogMgr, s);
        //i =new FitnessFrequency(_listDialogMgr, s);
        var i = new FitnessOrientationNS(_listDialogMgr, s);
        new FitnessOrientationEW(_listDialogMgr, s, i);
#if neko
        TXT= "Fitness";
#else
        TXT= "尺寸位置设定";
#end
    }
}
