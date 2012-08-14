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

class SpecialImgFrameworkLock extends CommDialog{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());

    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var special= new EmbedTextField();
        special.selectable = false;
#if neko
        special.text = "Image Framework Lock";
#else
        special.text = "图像框架锁定";
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
