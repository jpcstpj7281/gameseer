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

class FitnessInputSourceVPos extends ValueBarDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());
        _value = 0;
        _max = 300;
        _min = -300;
    }
    public override function createElement():Sprite{
        var fitness= new EmbedTextField();
        fitness.selectable = false;
#if neko
        fitness.text = "Input Source V Position";
#else
        fitness.text = "输入信号垂直位置";
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
