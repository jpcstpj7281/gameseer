package com.qbox.ui;
import nme.events.MouseEvent;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;
import base.ui.ListDialog;

import com.qbox.logic.Task;
import com.qbox.logic.Job;
import com.qbox.logic.TaskMgr;
import com.qbox.logic.ModeMgr;
import com.qbox.ui.JobDlg;


class TaskDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;

    var _qboxip:EmbedTextField;
    //var _output:EmbedTextField;
    var _deleteBtn:EmbedTextField;
    //var _loadBtn:EmbedTextField;
    //var _saveBtn:EmbedTextField;
    var _editBtn:EmbedTextField;
    var _s:Sprite;

    var _task:Task;

    var _cbDelete:Void->Void;

    var _oldReturnCB:Void->Void;

    public function new ( dm:ListDialogMgr, m:Task, cbdelete:Void->Void){
        _task = m;
        super(dm);
        addChild( createElement());

        _cbDelete = cbdelete;

        new PlusTimerFixedDlg(_listDialogMgr, cbPlusTimer );
        new PlusJumperFixedDlg(_listDialogMgr, cbPlusJumper);
        new PlusModeExecFixedDlg(_listDialogMgr, cbPlusModeExec);
        new PlayDlg(_listDialogMgr, _task);
        _oldReturnCB = _listDialogMgr._returnCallback ;
        _listDialogMgr._returnCallback  = returnCallback ;

        _task._cbStop = onStop;
        _task._cbStart = onStart;
    }

    function returnCallback(){
        _task.save();
        _oldReturnCB();
    }

    function onStart(){
        for ( i in cast(_listDialogMgr, ListDialogMgr)._movableInstances){
            if(Std.is(i, ModeExecJobDlg)){
                var m = cast (i, ModeExecJobDlg);
                if ( m.alpha > 0){
                    m.cannceEdit();
                    i.alpha = 0.5;
                }
            }if(Std.is(i, JumpToStepJobDlg) ){
                var m = cast (i, JumpToStepJobDlg);
                if ( m.alpha > 0){
                    m.cannceEdit();
                    i.alpha = 0.5;
                }
            }if(Std.is(i, TimeCountJobDlg) ){
                var m = cast (i, TimeCountJobDlg);
                if ( m.alpha >0){
                    m.cannceEdit();
                    i.alpha = 0.5;
                }
            }
        }
    }
    function onStop(){
        if( !_task._isRunning){
            for ( i in cast(_listDialogMgr, ListDialogMgr)._movableInstances){
                if ( alpha > 0){
                    i.alpha = 1;
                }
            }
        }
    }

    public function cbPlusJumper(){ 
        if ( _task._jobs.length == 0) {
            trace("cannot add jumper if there is no job");
            return;
        }
        var m = _task.createJumper();
        if ( m != null){
            var md = new JumpToStepJobDlg(_listDialogMgr, _task, m, refresh);
            md.show();
        }
    }

    public function cbPlusModeExec(){ 
        if ( ModeMgr.getInst()._modes.length == 0) {
            trace("cannot add mode executor if there is no mode");
            return;
        }
        var m = _task.createModeExec();
        if ( m != null){
            var md = new ModeExecJobDlg(_listDialogMgr, _task, m, refresh);
            md.show();
        }
    }
    public function cbPlusTimer(){
        var m = _task.createTimer();
        if ( m != null){
            var md = new TimeCountJobDlg(_listDialogMgr, _task, m, refresh);
            md.show();
        }
    }

    public function refresh():Void{
        _listDialogMgr.removeAllMovables();
        for ( i in _task._jobs){
            var m:ListDialog = null;
            if ( Std.is( i, TimeCountJob)){
                m = new TimeCountJobDlg(_listDialogMgr, _task, cast i, refresh);
            }else if ( Std.is(i, JumpToStepJob)){
                m = new JumpToStepJobDlg(_listDialogMgr, _task, cast i, refresh);
            }else if ( Std.is(i, ModeExecJob) ){
                m = new ModeExecJobDlg(_listDialogMgr, _task, cast i, refresh);
            }
            m.show();
        }
    }

    function onDeleteBtnMouseClick( evt:MouseEvent ):Void{
        TaskMgr.getInst().deleteTask(_task);
        _cbDelete();
    }

    public override function onMouseClick():Void{ }

    //function onSaveBtnMouseClick( evt:MouseEvent ):Void{ _task.save(); }
    //function onLoadBtnMouseClick( evt:MouseEvent ):Void{ _task.load(); }
    function onEditBtnMouseClick( evt:MouseEvent ):Void{
        refresh();
        super.onMouseClick();
    }

    override function show(){
        if ( _s != null) {
            if ( _pos != null){
                //_s.removeChild(_output);
                _s.removeChild(_pos);
                _s.removeChild(_deleteBtn);
                //_s.removeChild(_saveBtn);
                //_s.removeChild(_loadBtn);
                _s.removeChild(_editBtn);
            }


            _pos= new EmbedTextField();
            _pos.selectable = false;
            _pos.text = "Task:" + _task._index;
            _pos.scaleX = 3;
            _pos.scaleY = 3;
            _pos.width = 50;
            _pos.height= 16;

            _deleteBtn= new EmbedTextField();
            _deleteBtn.selectable = false;
            _deleteBtn.text = "Delete";
            _deleteBtn.scaleX = 3;
            _deleteBtn.scaleY = 3;
            _deleteBtn.width = 30;
            _deleteBtn.height= 16;
            _deleteBtn.setBorder(true);
            _deleteBtn.x = nme.Lib.current.stage.stageWidth - 80;
            _deleteBtn.addEventListener( MouseEvent.CLICK, onDeleteBtnMouseClick);

            //_saveBtn= new EmbedTextField();
            //_saveBtn.setBorder(true);
            //_saveBtn.selectable = false;
            //_saveBtn.scaleX = 3;
            //_saveBtn.scaleY = 3;
            //_saveBtn.width = 30;
            //_saveBtn.height= 16;
            //_saveBtn.x = nme.Lib.current.stage.stageWidth - 180;
            //_saveBtn.text = "Save";
            //_saveBtn.addEventListener( MouseEvent.CLICK, onSaveBtnMouseClick);
            //
            //_loadBtn= new EmbedTextField();
            //_loadBtn.setBorder(true);
            //_loadBtn.selectable = false;
            //_loadBtn.scaleX = 3;
            //_loadBtn.scaleY = 3;
            //_loadBtn.width = 30;
            //_loadBtn.height= 16;
            //_loadBtn.x = nme.Lib.current.stage.stageWidth - 280;
            //_loadBtn.text = "Load";
            //_loadBtn.addEventListener( MouseEvent.CLICK, onLoadBtnMouseClick);

            _editBtn= new EmbedTextField();
            _editBtn.setBorder(true);
            _editBtn.selectable = false;
            _editBtn.scaleX = 3;
            _editBtn.scaleY = 3;
            _editBtn.width = 30;
            _editBtn.height= 16;
            _editBtn.x = nme.Lib.current.stage.stageWidth - 380;
            _editBtn.text = "Edit";
            _editBtn.addEventListener( MouseEvent.CLICK, onEditBtnMouseClick);

            _s.addChild( _pos);
            _s.addChild( _deleteBtn);
            //_s.addChild( _saveBtn);
            //_s.addChild( _loadBtn);
            _s.addChild( _editBtn);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _pos != null) {
            _deleteBtn.removeEventListener(  MouseEvent.CLICK, onDeleteBtnMouseClick); 
            //_saveBtn.removeEventListener(  MouseEvent.CLICK, onSaveBtnMouseClick); 
            //_loadBtn.removeEventListener(  MouseEvent.CLICK, onLoadBtnMouseClick); 
            _s.removeChild(_pos);
            _s.removeChild(_deleteBtn);
            //_s.removeChild(_saveBtn);
            //_s.removeChild(_loadBtn);
            _s.removeChild(_editBtn);
            _pos= null;
            _deleteBtn= null;
            //_loadBtn= null;
            //_saveBtn= null;
            _editBtn= null;
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();
        return _s;
    }
}
