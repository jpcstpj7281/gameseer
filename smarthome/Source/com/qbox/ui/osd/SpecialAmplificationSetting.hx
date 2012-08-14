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

class SpecialAmplificationSetting extends ListDialog{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new AmplificationHPercent(_listDialogMgr);
        i =new AmplificationVPercent(_listDialogMgr);
        i =new AmplificationHMovment(_listDialogMgr);
        i =new AmplificationVMovment(_listDialogMgr);
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var special= new EmbedTextField();
        special.selectable = false;
#if neko
        special.text = "Amplification Setting";
#else
        special.text = "放大设定";
#end
        special.scaleX = 3;
        special.scaleY = 3;
        special.width = 100;
        special.height= 20;
        s.addChild( special);

        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
