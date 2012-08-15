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

class InputFitnessRedEnhance extends ValueBarDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());
        _value = 0;
        _max = 255;
    }

    public override function createElement():Sprite{
        var img= new EmbedTextField();
        img.selectable = false;
#if neko
        img.text = "Red Enhance";
#else
        img.text = "红色增益";
#end
        img.scaleX = 3;
        img.scaleY = 3;
        img.width = 100;
        img.height= 20;

        var s = super.createElement();
        s.addChild( img);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
