package com.qbox.ui;

import com.qbox.logic.ScreenMgr;
import com.qbox.logic.WndMgr;
import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Wnd;


class PlusRight extends FixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("right")));
        x = nme.Lib.current.stage.stageWidth - 160;
        y= nme.Lib.current.stage.stageHeight - 80;
    }

    function cbCloseWnd(){}
    public function cbPlus( ):Void{
        var arr = ScreenMgr.getInst().createColScreen();
        var ms:MainStage = null;
        for ( i in arr){
            if ( Std.is(_mgr, MainStage) ){
                ms = cast(_mgr, MainStage);
                WndMgr.getInst().closeAll(cbCloseWnd);
            }else{
                var qd = new ScreenDlg( cast _mgr, i);
                qd.show();
            }
        }
        if ( ms != null) ms.resetScreenPlate();
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        cbPlus();
    }
}

