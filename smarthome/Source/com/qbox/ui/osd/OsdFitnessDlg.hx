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

class OsdFitnessDlg extends ListDialog{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

        var i:CommDialog = new FitnessAspectRatio(_listDialogMgr);
        i = new FitnessAutoAdjust(_listDialogMgr);
        i =new FitnessHPos(_listDialogMgr);
        i =new FitnessVPos(_listDialogMgr);
        i =new FitnessInputSourceHPos(_listDialogMgr);
        i =new FitnessInputSourceVPos(_listDialogMgr);
        i =new FitnessPhase(_listDialogMgr);
        i =new FitnessFrequency(_listDialogMgr);
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var fitness= new EmbedTextField();
        fitness.selectable = false;
#if neko
        fitness.text = "Fitness";
#else
        fitness.text = "尺寸位置设定";
#end
        fitness.scaleX = 3;
        fitness.scaleY = 3;
        fitness.width = 50;
        fitness.height= 20;
        s.addChild( fitness);

        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
