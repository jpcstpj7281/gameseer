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
import base.ui.CommDialog;

class SubjectsDlg extends ListDialog{
    public function new ( dm:CommDialogMgr){
        super( dm);
        var str:String = "我画你猜";
        _uniqueId = str+0;
        var _content = dm.createElement( str, 0);
        addChild( _content);
        createDlgs();
    }

    public function createDlgs():Void{
        var cd = new CommDialog(_listDialogMgr);
        cd.addChild( _listDialogMgr.createElement( "心情涂鸦", 0) );
        cd = new CommDialog(_listDialogMgr);
        cd.addChild( _listDialogMgr.createElement( "自描自在", 0) );
        cd = new CommDialog(_listDialogMgr);
        cd.addChild( _listDialogMgr.createElement( "特发奇想", 0) );
        cd = new CommDialog(_listDialogMgr);
        cd.addChild( _listDialogMgr.createElement( "网络迷局", 0) );
        cd = new CommDialog(_listDialogMgr);
        cd.addChild( _listDialogMgr.createElement( "无拒无束", 0) );
    }
}
