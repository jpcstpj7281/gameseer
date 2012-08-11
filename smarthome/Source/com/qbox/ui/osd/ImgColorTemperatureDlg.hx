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

class ImgColorTemperatureDlg extends ListDialog{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var img= new EmbedTextField();
        img.selectable = false;
#if neko
        img.text = "Color Temperature";
#else
        img.text = "色温";
#end
        img.scaleX = 3;
        img.scaleY = 3;
        img.width = 100;
        img.height= 20;
        s.addChild( img);

        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
