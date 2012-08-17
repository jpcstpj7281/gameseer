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

class VideoSettingInputBlackLevel extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());

        _values.push("0 IRE");
        _values.push("7.5 IRE");
    }

    public override function createElement():Sprite{
        var img= new EmbedTextField();
        img.selectable = false;
#if neko
        img.text = "Input Black Level";
#else
        img.text = "输入信号黑阶";
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
