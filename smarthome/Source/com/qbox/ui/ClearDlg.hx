package com.qbox.ui;

import com.qbox.logic.ScreenMgr;
import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.WndMgr;
import com.qbox.ui.PlusRight;
import com.qbox.ui.PlusDown;


class ClearDlg extends FixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("clear")));

        x = 650;
        y= nme.Lib.current.stage.stageHeight - 80;

    }



    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            WndMgr.getInst().closeAll( cbLoad);
        }
        super.onMouseClick();
    }
    function cbLoad( ){
    }
}
