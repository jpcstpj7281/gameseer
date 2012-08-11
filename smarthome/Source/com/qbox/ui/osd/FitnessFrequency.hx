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
import base.ui.CommDialogMgr;

import com.qbox.logic.Qbox;
import com.qbox.logic.Channel;

class FitnessFrequency extends CommDialog{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());

    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var fitness= new EmbedTextField();
        fitness.selectable = false;
#if neko
        fitness.text = "Frequency";
#else
        fitness.text = "频率";
#end
        fitness.scaleX = 3;
        fitness.scaleY = 3;
        fitness.width = 100;
        fitness.height= 20;
        s.addChild( fitness);

        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
