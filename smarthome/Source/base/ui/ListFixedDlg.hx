package base.ui;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

import base.ui.CommDialog;
class ListFixedDlg extends FixedDlg{


    public var _listDialogMgr:SubListDialogMgr;

    public function new ( dm:CommDialogMgr, obj:DisplayObject){
        _listDialogMgr = new SubListDialogMgr(nme.Lib.current);
        _listDialogMgr._returnCallback = showParent;

        super( dm);
        addChild(obj);
    }

    public override function clear():Void{
        _listDialogMgr.clear();
        _listDialogMgr = null;
        super.clear();
    }
    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.showListDialog();
            hideParent();
        }
    }
}
