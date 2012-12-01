package com.qbox.ui;

import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.ModeMgr;
import com.qbox.logic.Mode;
import com.qbox.logic.TaskMgr;
import com.qbox.logic.Task;

class TaskMgrDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("file")));
        x = 570;
        y= nme.Lib.current.stage.stageHeight - 80;

        new PlusItemFixedDlg(_listDialogMgr, cbPlus );
    }

    public function cbPlus(){

        var m = TaskMgr.getInst().create();
        if ( m != null){
            var md = new TaskDlg(_listDialogMgr, m, refresh);
            md.show();
        }
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();

            for ( i in TaskMgr.getInst()._tasks){
                new TaskDlg(_listDialogMgr, i, refresh);
            }
        }
        super.onMouseClick();
    }

    public function refresh():Void{
        _listDialogMgr.removeAllMovables();

        for ( i in TaskMgr.getInst()._tasks){
            var m = new TaskDlg(_listDialogMgr, i, refresh);
            m.show();
        }
    }
}
