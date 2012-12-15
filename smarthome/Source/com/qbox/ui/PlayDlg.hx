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

import com.qbox.logic.Task;
import com.qbox.ui.JobDlg;

class PlayDlg extends FixedDlg{
    var _task:Task;
    public function new ( dm:CommDialogMgr , task:Task){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("play")));
        x = nme.Lib.current.stage.stageWidth - 400;
        y= nme.Lib.current.stage.stageHeight - 80;
        _task = task;
    }

    public function cbPlay( ):Void{
        if( !_task._isRunning){
            for ( i in cast(_mgr, ListDialogMgr)._movableInstances){
                if(Std.is(i, ModeExecJobDlg)){
                    cast (i, ModeExecJobDlg).cannceEdit();
                }if(Std.is(i, JumpToStepJobDlg) ){
                    cast (i, JumpToStepJobDlg).cannceEdit();
                }if(Std.is(i, TimeCountJobDlg) ){
                    cast (i, TimeCountJobDlg).cannceEdit();
                }
                i.alpha = 0.5;
            }
            _task.start();
        }else{
            _task.stop();
            for ( i in cast(_mgr, ListDialogMgr)._movableInstances){
                i.alpha = 1;
            }
        }
    }
    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        cbPlay();
    }
}
