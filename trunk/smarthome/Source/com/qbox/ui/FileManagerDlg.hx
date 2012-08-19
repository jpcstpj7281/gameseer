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
class FileManagerDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("file")));
        x = 410;
        y= nme.Lib.current.stage.stageHeight - 80;
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            for ( q in QboxMgr.getInst()._qboxes ){
                //new QboxUpdateDlg(_listDialogMgr, q);
            }
        }
        super.onMouseClick();
    }
}
