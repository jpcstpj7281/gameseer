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

class SpecialStartUpDelayTime extends ValueBarDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());
        _value = 0;
        _max= 10;
    }
    public override function createElement():Sprite{
        var special= new EmbedTextField();
        special.selectable = false;
#if neko
        special.text = "Startup Delay Time";
#else
        special.text = "开机延迟时间";
#end
        special.scaleX = 3;
        special.scaleY = 3;
        special.width = 100;
        special.height= 20;
        var s = super.createElement();
        s.addChild( special);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
