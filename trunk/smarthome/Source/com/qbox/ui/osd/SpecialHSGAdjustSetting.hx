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

class SpecialHSGAdjustSetting extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());

        _values.push("开启");
        _values.push("关闭");
    }

    public override function createElement():Sprite{
        var special= new EmbedTextField();
        special.selectable = false;
#if neko
        special.text = "HSG Adjust Setting";
#else
        special.text = "HSG调节设定";
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
