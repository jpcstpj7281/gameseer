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

import com.qbox.logic.Screen;
class DlpSettingGreenContrast extends ValueBarDlg{
    var _contrast:ImgContrastDlg;

    public function new ( dm:CommDialogMgr, s:Screen, contrast:ImgContrastDlg){
        super(dm, s);
        addChild( createElement());

        _contrast = contrast;
        _value = 50;
        _max = 100;
#if neko
        TXT= "Green Contrast";
#else
        TXT= "绿色对比度";
#end
    }
    override function dispatch(value:Int):Void{ _contrast.setGreen( value); }
}
