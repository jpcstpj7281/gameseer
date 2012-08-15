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

class ChildFrameVSize extends ValueBarDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());
        _value = 0;
        _max = 10;
    }
    public override function createElement():Sprite{
        var source= new EmbedTextField();
        source.selectable = false;
#if neko
        source.text = "Child Frame Vertical Size";
#else
        source.text = "子图像垂直大小";
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
