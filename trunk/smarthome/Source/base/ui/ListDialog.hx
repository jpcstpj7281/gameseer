package base.ui;

import com.eclecticdesignstudio.dialog.DialogType;
import com.eclecticdesignstudio.dialog.DialogData;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

class ListDialog extends CommDialog {


    public var _downx:Float;
    public var _downy:Float;
    public var _listDialogMgr:SubListDialogMgr;

    public function new ( dm:CommDialogMgr){
        _listDialogMgr = new SubListDialogMgr(nme.Lib.current);
        _listDialogMgr._returnCallback = showParent;

        super( dm);
    }

    public override function clear():Void{
        _listDialogMgr.clear();
        super.clear();
    }
    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.showListDialog();
            hideParent();
        }
    }
}
