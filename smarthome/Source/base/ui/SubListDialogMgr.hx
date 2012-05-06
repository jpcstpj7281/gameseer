package base.ui;

import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogType;
import com.eclecticdesignstudio.dialog.DialogData;
import com.eclecticdesignstudio.dialog.events.DialogEvent;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;

import haxe.Timer;

class SubListDialogMgr extends ListDialogMgr{


    var _returnParent:Sprite;
    public var _returnCallback:Dynamic;
    public function new (droppoint:Sprite ){
        super( droppoint );
        _returnParent = new Sprite();

        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("btn_return"));
        _returnParent.addChild( bm);
        _returnParent.x = nme.Lib.current.stage.stageWidth - 80;
        _returnParent.y= nme.Lib.current.stage.stageHeight - 80;
        _returnParent.addEventListener( MouseEvent.CLICK, onClickReturn);

        _fixedElement.push(_returnParent);
    }

    public override function clear():Void{
        hideListDialog();
        _returnParent = null;
        _returnCallback = null;
        super.clear();
    }
    public function onClickReturn( evt:MouseEvent) :Void{
        if ( isAnimating() ) return;
        if ( _returnCallback != null ){
            //trace("onClickReturn call returnCallback");
            _returnCallback();
        }
        //trace("onClickReturn");
        hideListDialog();
    }

}
