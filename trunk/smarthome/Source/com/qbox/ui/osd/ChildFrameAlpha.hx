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

class OsdSourceDlg extends ListDialog{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var source= new EmbedTextField();
        source.selectable = false;
#if neko
        source.text = "source";
#else
        source.text = "信号源设定";
#end
        source.scaleX = 3;
        source.scaleY = 3;
        source.width = 50;
        source.height= 20;
        s.addChild( source);

        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
