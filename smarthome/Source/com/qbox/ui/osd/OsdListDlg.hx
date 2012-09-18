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

class OsdListDlg extends ListDialog{


    public function new ( dm:ListDialogMgr){
        super(dm);
#if neko
        TXT= "unknow";
#else
        TXT= "δ֪";
#end
    }

    var _s:Sprite;
    var _promt:EmbedTextField;
    var TXT:String;
    override function show(){
        if ( _promt != null){
            _s.removeChild(_promt);
        }
        _promt= new EmbedTextField();
        _promt.selectable = false;
        _promt.text = TXT;
        _promt.scaleX = 3;
        _promt.scaleY = 3;
        _promt.width = 50;
        _promt.height= 16;
        _s.addChild( _promt);
        _s.height = nme.Lib.current.stage.stageHeight/15;
        return super.show();
    }
    override function hide(){
        if ( _promt != null){ _s.removeChild(_promt); }
        _promt = null;
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();
        return _s;
    }
}
