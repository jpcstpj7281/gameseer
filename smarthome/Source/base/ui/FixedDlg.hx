
package base.ui;

import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

class FixedDlg extends CommDialog {


    public function new ( dm:CommDialogMgr, elem:DisplayObject = null){
        super( dm);
        if ( elem != null ) addChild(elem);
    }

    public override function onMouseClick( ):Void{
    }
}
