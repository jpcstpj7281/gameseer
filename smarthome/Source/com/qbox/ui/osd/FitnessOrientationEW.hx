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

import haxe.io.BytesBuffer;
import com.qbox.logic.Screen;

class FitnessOrientationEW extends ValueSwitchDlg{
    var _ns:FitnessOrientationNS;
    public function new ( dm:CommDialogMgr, s:Screen, ns:FitnessOrientationNS){
        super(dm, s);
        addChild( createElement());
        _value = 0;
        _ns = ns;
#if neko
        _values.push("normal");
        _values.push("flip");
        TXT= "Horizontal";
#else
        _values.push("正");
        _values.push("反");
        TXT= "水平";
#end
    }

    override function dispatch(value:Int):Void{
        _ns.setEW( value);
    }
}
