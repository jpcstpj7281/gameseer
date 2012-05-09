package base.ui;

import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

class ReturnDlg extends FixedDlg{


    public var _returnCallback:Dynamic;
    public function new ( dm:CommDialogMgr, returnCallback:Dynamic ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("btn_return")));
        x = nme.Lib.current.stage.stageWidth - 80;
        y= nme.Lib.current.stage.stageHeight - 80;
        _returnCallback = returnCallback;
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        if ( _returnCallback != null ){
            _returnCallback();
        }
        _mgr.hideListDialog();
    }
}
