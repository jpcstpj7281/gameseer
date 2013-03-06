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

class ImgInputFitnessDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr, s:Screen){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new InputFitnessRedBlackLevel(_listDialogMgr, s);
        i =new InputFitnessGreenBlackLevel(_listDialogMgr, s);
        i =new InputFitnessBlueBlackLevel(_listDialogMgr, s);
        i =new InputFitnessRedEnhance(_listDialogMgr, s);
        i =new InputFitnessGreenEnhance(_listDialogMgr, s);
        i =new InputFitnessBlueEnhance(_listDialogMgr, s);
#if neko
        TXT= "Input Fitness";
#else
        TXT= "输入准位";
#end
    }
}
