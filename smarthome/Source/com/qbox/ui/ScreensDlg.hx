package com.qbox.ui;

import com.qbox.logic.QboxMgr;
import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Wnd;
import com.qbox.ui.PlusRight;
import com.qbox.ui.PlusDown;


class ScreensDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("screen")));

        x = 330;
        y= nme.Lib.current.stage.stageHeight - 80;

        new PlusDown(_listDialogMgr);
        new PlusRight(_listDialogMgr);
    }

    public override function onMouseClick( ):Void{
        //if ( QboxMgr.getInst()._qboxes.length == 0) {
        //trace("there is no qbox!");
        //return;
        //}
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            for ( c in ScreenMgr.getInst()._screens){
                new ScreenDlg(_listDialogMgr, c);
            }
        }
        super.onMouseClick();
    }
}
