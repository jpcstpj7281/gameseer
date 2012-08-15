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

class GroupHorizontalIndex extends ValueBarDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());
        _value = 0;
        _min= 1;
        _max= 8;
    }
    public override function createElement():Sprite{
        var group= new EmbedTextField();
        group.selectable = false;
#if neko
        group.text = "Machine Horizontal Index";
#else
        group.text = "单机水平序号";
#end
        group.scaleX = 3;
        group.scaleY = 3;
        group.width = 100;
        group.height= 20;
        var s = super.createElement();
        s.addChild( group);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
