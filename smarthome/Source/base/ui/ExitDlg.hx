package base.ui;

import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

class ExitDlg extends FixedDlg{


    public function new ( dm:CommDialogMgr){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("exit")));
        x = 50;
        y= nme.Lib.current.stage.stageHeight - 100;
    }

    public override function onMouseClick( ):Void{
        nme.system.System.exit();
    }
}
