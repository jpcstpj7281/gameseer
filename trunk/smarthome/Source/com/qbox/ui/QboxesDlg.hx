package com.qbox.ui;

import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.QboxMgr;

import com.pictionary.ui.DrawingDlgMgr;
class QboxesDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("qbox")));

        x = 90;
        y= nme.Lib.current.stage.stageHeight - 80;

        new PlusItemFixedDlg(_listDialogMgr, cbPlusQbox);
    }

    public function cbPlusQbox( ):Void{

        if (QboxMgr.getInst()._qboxes.length >8 ) return;
        var qd = new QboxDlg(_listDialogMgr, QboxMgr.getInst().createQbox());
        qd.show();
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            for ( q in QboxMgr.getInst()._qboxes ){
                new QboxDlg(_listDialogMgr, q);
            }
        }
        super.onMouseClick();
    }
}
