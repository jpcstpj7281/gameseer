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

import com.pictionary.ui.DrawingDlgMgr;

class PlusRight extends FixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("right")));
        x = nme.Lib.current.stage.stageWidth - 160;
        y= nme.Lib.current.stage.stageHeight - 80;
    }

    public function cbPlus( ):Void{
        var arr = ScreenMgr.getInst().createColScreen();
        for ( i in arr){
            if ( QboxMgr.getInst()._qboxes.length > 0 ){
                i._qboxid = QboxMgr.getInst()._qboxes[0]._ipv4;
                i._output= "out0";
            }
            var qd = new ScreenDlg( cast _mgr, i);
            qd.show();
        }
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        cbPlus();
    }
}

class PlusDown extends FixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("down")));
        x = nme.Lib.current.stage.stageWidth - 240;
        y= nme.Lib.current.stage.stageHeight - 80;
    }

    public function cbPlus( ):Void{
        var arr = ScreenMgr.getInst().createRowScreen();
        for ( i in arr){
            if ( QboxMgr.getInst()._qboxes.length > 0 ){
                i._qboxid = QboxMgr.getInst()._qboxes[0]._ipv4;
                i._output= "out0";
            }
            var qd = new ScreenDlg( cast _mgr, i);
            qd.show();
        }
    }
    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        cbPlus();
    }
}

class ScreensDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("screen")));

        x = 330;
        y= nme.Lib.current.stage.stageHeight - 80;

        new PlusDown(_listDialogMgr);
        new PlusRight(_listDialogMgr);
    }

    //public function cbPlus( ):Void{
    //var qd = new ScreenDlg(_listDialogMgr, ScreenMgr.getInst().createScreen());
    //qd.show();
    //}

    public override function onMouseClick( ):Void{
        if ( QboxMgr.getInst()._qboxes.length == 0) return;
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            for ( c in ScreenMgr.getInst()._screens){
                new ScreenDlg(_listDialogMgr, c);
            }
        }
        super.onMouseClick();
    }
}
