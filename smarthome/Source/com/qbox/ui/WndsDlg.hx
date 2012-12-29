package com.qbox.ui;

import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.WndMgr;
import com.qbox.logic.Wnd;

class WndsDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("wnd")));

        x = 250;
        y= nme.Lib.current.stage.stageHeight - 80;

    }

    public function cbPlusWnd( ):Void{
        var qd = new WndDlg(_listDialogMgr, WndMgr.getInst().createWnd());
        qd.show();
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            new WndMenuFixedDlg(_listDialogMgr);
            for ( c in WndMgr.getInst()._wnds){
                new WndDlg(_listDialogMgr, c);
            }
        }
        super.onMouseClick();
    }
}
