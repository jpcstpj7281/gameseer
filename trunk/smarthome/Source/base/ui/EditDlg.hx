package base.ui;

import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

class EditDlg extends FixedDlg{


    public var _returnCallback:Dynamic;
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("btn_edit")));
        x = nme.Lib.current.stage.stageWidth - 160;
        y= nme.Lib.current.stage.stageHeight - 80;
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        cast(_mgr, ComponentDlgMgr).toggleFixed();
    }
}
