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

class OptionMenuVerticalPos extends ValueBarDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());
        _value = 0;
        _max = 50;
    }
    public override function createElement():Sprite{
        var option= new EmbedTextField();
        option.selectable = false;
#if neko
        option.text = "Menu Vertical Position";
#else
        option.text = "菜单垂直位置";
#end
        option.scaleX = 3;
        option.scaleY = 3;
        option.width = 100;
        option.height= 20;
        var s = super.createElement();
        s.addChild( option);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
