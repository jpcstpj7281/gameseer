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
import haxe.io.BytesBuffer;

class HSGGreenSat extends ValueBarDlg{
    var _hsg:SpecialHSGSetting;

    public function new ( dm:CommDialogMgr, s, hsg:SpecialHSGSetting){
        super(dm, s);
        addChild( createElement());

        _value = 0x4000;
        _max = 0x7fff;
        _min = 0;
        TXT= "Green Sat";
        _hsg = hsg;
#if neko
        //TXT= "Horizontal Position";
#else
        //TXT= "水平位置";
#end
    }
    override function dispatch(value:Int):Void{
        _hsg.setGreenSat(value);
    }
}
