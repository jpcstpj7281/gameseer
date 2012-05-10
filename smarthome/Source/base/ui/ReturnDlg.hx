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
    static var BM:Bitmap;
    public function new ( dm:CommDialogMgr, returnCallback:Dynamic ){
        if( BM == null) BM= new Bitmap( DataLoader.getInst().bms_.get("btn_return"));
        super(dm);
        x = nme.Lib.current.stage.stageWidth - 80;
        y= nme.Lib.current.stage.stageHeight - 80;
        _returnCallback = returnCallback;
    }

    public override function show(){
        if ( BM.parent != null ) BM.parent.removeChild(BM);
        addChild(BM);
        return super.show();
    }

    public override function hide(){
        if ( contains(BM)) removeChild(BM);
        return super.hide();
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;

        if ( contains(BM)) removeChild(BM);
        if ( _returnCallback != null ){
            _returnCallback();
        }
        _mgr.hideListDialog();
    }
}
