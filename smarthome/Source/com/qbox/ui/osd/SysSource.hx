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

class SysSource extends CommDialog{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());

    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var sys= new EmbedTextField();
        sys.selectable = false;
#if neko
        sys.text = "Source";
#else
        sys.text = "信号源";
#end
        sys.scaleX = 3;
        sys.scaleY = 3;
        sys.width = 100;
        sys.height= 20;
        s.addChild( sys);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
