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
import base.ui.CommDialogMgr;
import com.qbox.logic.Qbox;

class FitnessAspectRatio extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());

        _values.push("4:3");
        _values.push("16:9");
    }

    public override function createElement():Sprite{
        var fitness= new EmbedTextField();
        fitness.selectable = false;
#if neko
        fitness.text = "Aspect Ratio";
#else
        fitness.text = "长宽比";
#end
        fitness.scaleX = 3;
        fitness.scaleY = 3;
        fitness.width = 100;
        fitness.height= 20;
        var s = super.createElement();
        s.addChild( fitness);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
