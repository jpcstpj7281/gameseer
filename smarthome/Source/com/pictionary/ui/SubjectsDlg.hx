package com.pictionary.ui;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

import base.ui.ListDialog;
import base.ui.CommDialogMgr;

class SubjectsDlg extends ListDialog{
    public function new ( dm:CommDialogMgr){
        super( dm);
        var str = "ÎÒ»­Äã²Â";
        _uniqueId = str+0;
        var _content = CommDialogMgr.getElement( str, 0);
        addChild( _content);
    }

    public function createDlgs():Void{
        var cd = new CommDialog(_listDialogMgr);
        cd.addChild( _listDialogMgr.createElement( "test1", 0) );
    }
}
