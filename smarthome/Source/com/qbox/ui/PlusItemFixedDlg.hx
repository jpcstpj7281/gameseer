package com.qbox.ui;

import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.FixedDlg;
import base.ui.CommDialogMgr;

class PlusItemFixedDlg extends FixedDlg{
    var _cb:Void->Void;
    public function new ( dm:CommDialogMgr, cb:Void->Void ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("plus")));
        x = nme.Lib.current.stage.stageWidth - 160;
        y= nme.Lib.current.stage.stageHeight - 80;
        _cb = cb;
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        _cb();
    }
}
