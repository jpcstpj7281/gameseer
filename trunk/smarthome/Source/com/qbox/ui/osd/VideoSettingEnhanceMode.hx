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

class VideoSettingEnhanceMode extends ValueSwitchDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());
#if neko
        _values.push("on");
        _values.push("off");
#else
        _values.push("开启");
        _values.push("关闭");
#end
    }

    public override function createElement():Sprite{
        var s:Sprite = new Sprite();

        var img= new EmbedTextField();
        img.selectable = false;
#if neko
        img.text = "Enhance Mode";
#else
        img.text = "扩大模式";
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
