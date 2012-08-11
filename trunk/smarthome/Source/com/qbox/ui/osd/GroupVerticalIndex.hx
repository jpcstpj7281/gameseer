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

class OsdGroupDlg extends ListDialog{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var group= new EmbedTextField();
        group.selectable = false;
#if neko
        group.text = "group";
#else
        group.text = "组屏设定";
#end
        group.scaleX = 3;
        group.scaleY = 3;
        group.width = 50;
        group.height= 20;
        s.addChild( group);

        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
