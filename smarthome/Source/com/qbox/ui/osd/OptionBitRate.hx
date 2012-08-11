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

class OsdOptionDlg extends ListDialog{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var option= new EmbedTextField();
        option.selectable = false;
#if neko
        option.text = "option";
#else
        option.text = "选项设定";
#end
        option.scaleX = 3;
        option.scaleY = 3;
        option.width = 50;
        option.height= 20;
        s.addChild( option);

        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
