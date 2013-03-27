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
import com.qbox.logic.Screen;
import haxe.io.BytesBuffer;

class TestModePeriod extends ValueBarDlg{
    var _testPattern:TestModeTestPattern;

    public function new ( dm:CommDialogMgr, s:Screen, testPattern:TestModeTestPattern){
        super(dm, s);
        addChild( createElement());
        _max = 0xf;
        _value = 0xf;
        _testPattern = testPattern;
#if neko
        TXT= "Test Pattern Period";
#else
        TXT= "测试周期";
#end
    }

    override function dispatch(value:Int):Void{
        _testPattern.setPeriod(value);
    }
}
