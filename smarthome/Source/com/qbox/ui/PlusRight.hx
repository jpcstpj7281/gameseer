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


class PlusRight extends FixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("right")));
        x = nme.Lib.current.stage.stageWidth - 160;
        y= nme.Lib.current.stage.stageHeight - 80;
    }

    public function cbPlus( ):Void{
        var arr = ScreenMgr.getInst().createColScreen();
        for ( i in arr){
            //if ( QboxMgr.getInst()._qboxes.length > 0 ){
                i._qboxid = "127.0.0.1";
                //i._output= "out0";
                if ( Std.is(_mgr, MainStage) ){
                    cast(_mgr, MainStage).resetScreenPlate();
                }else{
                    var qd = new ScreenDlg( cast _mgr, i);
                    qd.show();
                }
                //}
        }
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        cbPlus();
    }
}

