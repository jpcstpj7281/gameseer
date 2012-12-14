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
import com.qbox.logic.TaskMgr;
import com.qbox.logic.Job;

class TimeCountJobDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;

    var _qboxip:EmbedTextField;
    var _deleteBtn:EmbedTextField;
    var _s:Sprite;

    var _task:Task;
    var _job:Job;

    var _cbDelete:Void->Void;

    public function new ( dm:ListDialogMgr, m:Task, j:Job,  cbdelete:Void->Void){
        _task = m;
        _job = j;
        super(dm);
        addChild( createElement());

        _cbDelete = cbdelete;

    }

    function onDeleteBtnMouseClick( evt:MouseEvent ):Void{
        _task.deleteJob(_job);
        _cbDelete();
    }

    public override function onMouseClick():Void{ }
    function onEditBtnMouseClick( evt:MouseEvent ):Void{ super.onMouseClick(); }

    override function show(){
        if ( _s != null) {
            if ( _pos!= null){
                _s.removeChild(_pos);
                _s.removeChild(_deleteBtn);
            }
            _pos= new EmbedTextField();
            _pos.selectable = false;
            _pos.text = "" + _job._index+":Timer" ;
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

            _s.addChild( _pos);
            _s.addChild( _deleteBtn);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _pos != null) {
            _deleteBtn.removeEventListener(  MouseEvent.CLICK, onDeleteBtnMouseClick); 
            _s.removeChild(_pos);
            _s.removeChild(_deleteBtn);
            _pos= null;
            _deleteBtn= null;
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();
        return _s;
    }
}

class ModeExecJobDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;

    var _qboxip:EmbedTextField;
    var _deleteBtn:EmbedTextField;
    var _s:Sprite;

    var _task:Task;
    var _job:Job;

    var _cbDelete:Void->Void;

    public function new ( dm:ListDialogMgr, m:Task, j:Job,  cbdelete:Void->Void){
        _task = m;
        _job = j;
        super(dm);
        addChild( createElement());

        _cbDelete = cbdelete;

    }

    function onDeleteBtnMouseClick( evt:MouseEvent ):Void{
        _task.deleteJob(_job);
        _cbDelete();
    }

    public override function onMouseClick():Void{ }
    function onEditBtnMouseClick( evt:MouseEvent ):Void{ super.onMouseClick(); }

    override function show(){
        if ( _s != null) {
            if ( _pos!= null){
                _s.removeChild(_pos);
                _s.removeChild(_deleteBtn);
            }
            _pos= new EmbedTextField();
            _pos.selectable = false;
            _pos.text = "" + _job._index+":Mode" ;
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

            _s.addChild( _pos);
            _s.addChild( _deleteBtn);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _pos != null) {
            _deleteBtn.removeEventListener(  MouseEvent.CLICK, onDeleteBtnMouseClick); 
            _s.removeChild(_pos);
            _s.removeChild(_deleteBtn);
            _pos= null;
            _deleteBtn= null;
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();
        return _s;
    }
}
class JumpToStepJobDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;

    var _qboxip:EmbedTextField;
    var _deleteBtn:EmbedTextField;
    var _s:Sprite;

    var _task:Task;
    var _job:Job;

    var _cbDelete:Void->Void;

    public function new ( dm:ListDialogMgr, m:Task, j:Job,  cbdelete:Void->Void){
        _task = m;
        _job = j;
        super(dm);
        addChild( createElement());

        _cbDelete = cbdelete;

    }

    function onDeleteBtnMouseClick( evt:MouseEvent ):Void{
        _task.deleteJob(_job);
        _cbDelete();
    }

    public override function onMouseClick():Void{ }
    function onEditBtnMouseClick( evt:MouseEvent ):Void{ super.onMouseClick(); }

    override function show(){
        if ( _s != null) {
            if ( _pos!= null){
                _s.removeChild(_pos);
                _s.removeChild(_deleteBtn);
            }
            _pos= new EmbedTextField();
            _pos.selectable = false;
            _pos.text = "" + _job._index+":Jumper" ;
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

            _s.addChild( _pos);
            _s.addChild( _deleteBtn);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _pos != null) {
            _deleteBtn.removeEventListener(  MouseEvent.CLICK, onDeleteBtnMouseClick); 
            _s.removeChild(_pos);
            _s.removeChild(_deleteBtn);
            _pos= null;
            _deleteBtn= null;
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();
        return _s;
    }
}
