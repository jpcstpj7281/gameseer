package com.qbox.ui;

import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Wnd;

import com.pictionary.ui.DrawingDlgMgr;
class ScreensDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("btn_edit")));

        x = 330;
        y= nme.Lib.current.stage.stageHeight - 80;

        new PlusItemFixedDlg(_listDialogMgr, cbPlus);
    }

    public function cbPlus( ):Void{
        var qd = new ScreenDlg(_listDialogMgr, ScreenMgr.getInst().createScreen());
        qd.show();
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            for ( c in ScreenMgr.getInst()._screens){
                new ScreenDlg(_listDialogMgr, c);
            }
        }
        super.onMouseClick();
    }
}
