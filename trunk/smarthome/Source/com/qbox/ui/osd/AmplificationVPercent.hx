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

class AmplificationVPercent extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());

        _values.push("关闭");
        _values.push("10%");
    }

    public override function createElement():Sprite{
        var s:Sprite = new Sprite();

        var source= new EmbedTextField();
        source.selectable = false;
#if neko
        source.text = "Vertical Amplify Percent";
#else
        source.text = "垂直放大比例";
#end
        source.scaleX = 3;
        source.scaleY = 3;
        source.width = 100;
        source.height= 20;
        var s = super.createElement();
        s.addChild( source);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
