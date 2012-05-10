package base.ui;
import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

class SubListDialogMgr extends ListDialogMgr{


    public var _returnCallback:Dynamic;
    public function new (droppoint:Sprite ){
        super( droppoint );
        new ReturnDlg( this , returnCallback);
    }
    function returnCallback():Void{
        if (_returnCallback != null ) _returnCallback();
    }

}
