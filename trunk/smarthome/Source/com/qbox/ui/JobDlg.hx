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
import com.qbox.logic.ModeMgr;
import com.qbox.logic.Job;

import base.ui.NumberTextField;



class TimeCountJobDlg extends ListDialog{

    var _pos:EmbedTextField;
    var _delete:EmbedTextField;

    var _qboxip:EmbedTextField;
    var _deleteBtn:EmbedTextField;
    var _editBtn:EmbedTextField;

    var _inHour:Number60TextField;
    var _inMinute:Number60TextField;
    var _inSec:Number60TextField;

    var _seperate1:EmbedTextField;
    var _seperate2:EmbedTextField;

    var _s:Sprite;

    var _task:Task;
    var _job:TimeCountJob;

    var _cbDelete:Void->Void;

    public function new ( dm:ListDialogMgr, m:Task, j:TimeCountJob,  cbdelete:Void->Void){
        super(dm);
        addChild( createElement());

        _cbDelete = cbdelete;
        _task = m;
        _job = j;
        _job._cbStart = onStart;
        _job._cbRun = onRun;
        _job._cbStop = onStop;
    }
    function onStart():Void{ 
        cannceEdit();
        alpha = 1;
    }
    function onRun():Void{ 
        if ( _inHour != null) _inHour.text = ""+_job.getRemainHours();
        if ( _inSec != null) _inSec.text = ""+_job.getRemainSeconds();
        if ( _inMinute!= null) _inMinute.text = ""+_job.getRemainMinutes();
    }
    function onStop():Void{ 
        if ( _inHour != null) _inHour.text = ""+_job.getRemainHours();
        if ( _inSec != null) _inSec.text = ""+_job.getRemainSeconds();
        if ( _inMinute!= null) _inMinute.text = ""+_job.getRemainMinutes();
        alpha = 0.5;
    }
    function onDeleteBtnMouseClick( evt:MouseEvent ):Void{
        _task.deleteJob(_job);
        _cbDelete();
    }

    public override function onMouseClick():Void{ }
    public function cannceEdit(){
        if ( _inHour.type == INPUT){
            _inHour.type = DYNAMIC;
            _inMinute.type = DYNAMIC;
            _inSec.type = DYNAMIC;
            _inHour.setBorder(false);
            _inMinute.setBorder(false);
            _inSec.setBorder(false);

            var s = Std.parseInt( _inSec.text);
            var m = Std.parseInt( _inMinute.text);
            var h = Std.parseInt( _inHour.text);
            var t = 1000 * ( s + 60 * m + 3600 * h);
            _job.setInterval( t);
        }
    }
    function onEditBtnMouseClick( evt:MouseEvent ):Void{ 
        if ( _inHour.type == INPUT){
            cannceEdit();
        }else{
            _inHour.type = INPUT;
            _inMinute.type = INPUT;
            _inSec.type = INPUT;
            _inHour.setBorder(true);
            _inMinute.setBorder(true);
            _inSec.setBorder(true);
        }
    }

    override function show(){
        if ( _s != null) {
            if ( _pos!= null){
                _s.removeChild(_pos);
                _s.removeChild(_deleteBtn);
                _s.removeChild(_editBtn);
                _s.removeChild(_inHour);
                _s.removeChild(_inMinute);
                _s.removeChild(_inSec);
                _s.removeChild(_seperate1);
                _s.removeChild(_seperate2);
            }
            _pos= new EmbedTextField();
            _pos.selectable = false;
            _pos.text = "" + _job._index+":Timer" ;
            _pos.scaleX = 3;
            _pos.scaleY = 3;
            _pos.width = 50;
            _pos.height= 16;

            _seperate1= new EmbedTextField();
            _seperate1.selectable = false;
            _seperate1.text = ":";
            _seperate1.scaleX = 3;
            _seperate1.scaleY = 3;
            _seperate1.width = 10;
            _seperate1.height= 16;
            _seperate1.x = 315;

            _seperate2= new EmbedTextField();
            _seperate2.selectable = false;
            _seperate2.text = ":";
            _seperate2.scaleX = 3;
            _seperate2.scaleY = 3;
            _seperate2.width = 10;
            _seperate2.height= 16;
            _seperate2.x = 365;

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

            _editBtn= new EmbedTextField();
            _editBtn.selectable = false;
            _editBtn.text = "Edit";
            _editBtn.scaleX = 3;
            _editBtn.scaleY = 3;
            _editBtn.width = 30;
            _editBtn.height= 16;
            _editBtn.setBorder(true);
            _editBtn.x = nme.Lib.current.stage.stageWidth - 180;
            _editBtn.addEventListener( MouseEvent.CLICK, onEditBtnMouseClick);

            _inHour= new Number60TextField();
            _inHour.selectable = false;
            _inHour.text = "" + _job.getRemainHours();
            _inHour.scaleX = 3;
            _inHour.scaleY = 3;
            _inHour.width = 15;
            _inHour.height= 16;
            _inHour.x = 280;
            _inMinute= new Number60TextField();
            _inMinute.selectable = false;
            _inMinute.text = "" + _job.getRemainMinutes();
            _inMinute.scaleX = 3;
            _inMinute.scaleY = 3;
            _inMinute.width = 15;
            _inMinute.height= 16;
            _inMinute.x = 330;
            _inSec= new Number60TextField();
            _inSec.selectable = false;
            _inSec.text = "" + _job.getRemainSeconds();
            _inSec.scaleX = 3;
            _inSec.scaleY = 3;
            _inSec.width = 15;
            _inSec.height= 16;
            _inSec.x = 380;

            _s.addChild( _pos);
            _s.addChild( _deleteBtn);
            _s.addChild( _editBtn);
            _s.addChild( _inHour);
            _s.addChild( _inMinute);
            _s.addChild( _inSec);
            _s.addChild( _seperate1);
            _s.addChild( _seperate2);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }

    override function hide(){
        if ( _s != null && _pos != null) {
            if ( _inHour.type == INPUT){
                onEditBtnMouseClick(null);
            }

            _deleteBtn.removeEventListener(  MouseEvent.CLICK, onDeleteBtnMouseClick); 
            _s.removeChild(_pos);
            _s.removeChild(_deleteBtn);
            _s.removeChild(_editBtn);
            _s.removeChild(_inHour);
            _s.removeChild(_inMinute);
            _s.removeChild(_inSec);
            _s.removeChild(_seperate1);
            _s.removeChild(_seperate2);
            _pos= null;
            _deleteBtn= null;
            _editBtn= null;
            _inHour= null;
            _inMinute= null;
            _inSec= null;
            _seperate1= null;
            _seperate2= null;
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
    var _number:EmbedTextField;
    var _increase:EmbedTextField;
    var _decrease:EmbedTextField;
    var _editBtn:EmbedTextField;

    var _s:Sprite;

    var _task:Task;
    var _job:ModeExecJob;

    var _cbDelete:Void->Void;

    public function new ( dm:ListDialogMgr, m:Task, j:ModeExecJob,  cbdelete:Void->Void){
        super(dm);
        addChild( createElement());
        _cbDelete = cbdelete;
        _task = m;
        _job = j;
        _job._cbStart = onStart;
        _job._cbStop = onStop;
    }
    function onStart():Void{ 
        cannceEdit();
        alpha = 1;
    }
    function onStop():Void{ 
        alpha = 0.5;
    }

    function onDeleteBtnMouseClick( evt:MouseEvent ):Void{
        _task.deleteJob(_job);
        _cbDelete();
    }

    public override function onMouseClick():Void{ }

    function onDecreaseBtnMouseClick( evt:MouseEvent ):Void{ 
        --_job._modeIndex;
        if (_job._modeIndex< 0 ){
            _job._modeIndex= 0;
        }
        _number.text = ""+_job._modeIndex;
    }
    function onIncreaseBtnMouseClick( evt:MouseEvent ):Void{ 
        ++_job._modeIndex;
        var length = ModeMgr.getInst()._modes.length;
        if (_job._modeIndex >= length ){
            _job._modeIndex = length -1;
            if( _job._modeIndex == -1) _job._modeIndex= 0;
        }
        _number.text = ""+_job._modeIndex;
    }

    public function cannceEdit(){
        if ( _increase!= null){
            _increase.removeEventListener(  MouseEvent.CLICK, onIncreaseBtnMouseClick); 
            _s.removeChild(_increase);
            _increase= null;

            _s.removeChild(_decrease);
            _decrease.removeEventListener(  MouseEvent.CLICK, onDecreaseBtnMouseClick); 
            _decrease= null;
        }
    }
    function onEditBtnMouseClick( evt:MouseEvent ):Void{ 
        if (_increase == null){
            _increase= new EmbedTextField();
            _increase.selectable = false;
            _increase.text = "+";
            _increase.scaleX = 3;
            _increase.scaleY = 3;
            _increase.width = 10;
            _increase.height= 16;
            //_increase.setBorder(true);
            _increase.x = 380;
            _increase.addEventListener( MouseEvent.CLICK, onIncreaseBtnMouseClick);

            _decrease= new EmbedTextField();
            _decrease.selectable = false;
            _decrease.text = "-";
            _decrease.scaleX = 3;
            _decrease.scaleY = 3;
            _decrease.width = 10;
            _decrease.height= 16;
            //_decrease.setBorder(true);
            _decrease.x = 280;
            _decrease.addEventListener( MouseEvent.CLICK, onDecreaseBtnMouseClick);
            _s.addChild( _decrease);
            _s.addChild( _increase);
        }else{
            cannceEdit();
        }
    }

    override function show(){
        if ( _s != null) {
            if ( _pos!= null){
                _s.removeChild(_pos);
                _s.removeChild(_deleteBtn);
                _s.removeChild(_editBtn);
                _s.removeChild(_number);
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

            _number= new EmbedTextField();
            _number.selectable = false;
            _number.text = ""+ _job._modeIndex;
            _number.scaleX = 3;
            _number.scaleY = 3;
            _number.width = 50;
            _number.height= 16;
            _number.x = 330;

            _editBtn= new EmbedTextField();
            _editBtn.selectable = false;
            _editBtn.text = "Edit";
            _editBtn.scaleX = 3;
            _editBtn.scaleY = 3;
            _editBtn.width = 30;
            _editBtn.height= 16;
            _editBtn.setBorder(true);
            _editBtn.x = nme.Lib.current.stage.stageWidth - 180;
            _editBtn.addEventListener( MouseEvent.CLICK, onEditBtnMouseClick);

            _s.addChild( _pos);
            _s.addChild( _deleteBtn);
            _s.addChild( _editBtn);
            _s.addChild( _number);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _pos != null) {
            _deleteBtn.removeEventListener(  MouseEvent.CLICK, onDeleteBtnMouseClick); 
            if (_increase != null){
                onEditBtnMouseClick(null);
            }
            _s.removeChild(_pos);
            _s.removeChild(_deleteBtn);
            _s.removeChild(_number);
            _pos= null;
            _deleteBtn= null;
            _number= null;
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
    var _number:EmbedTextField;
    var _increase:EmbedTextField;
    var _decrease:EmbedTextField;
    var _counter:EmbedTextField;
    var _incrCounter:EmbedTextField;
    var _decrCounter:EmbedTextField;
    var _editBtn:EmbedTextField;

    var _s:Sprite;

    var _task:Task;
    var _job:JumpToStepJob;

    var _cbDelete:Void->Void;

    public function new ( dm:ListDialogMgr, m:Task, j:JumpToStepJob,  cbdelete:Void->Void){
        super(dm);
        addChild( createElement());
        _cbDelete = cbdelete;
        _task = m;
        _job = j;
        _job._cbStart = onStart;
        _job._cbRun = onRun;
        _job._cbStop = onStop;
    }
    function onStart():Void{ 
        cannceEdit();
        alpha = 1;
    }
    function onRun():Void{ if ( _counter!= null) _counter.text = "" + _job._current; }
    function onStop():Void{ if ( _counter!= null) _counter.text = "" + _job._counter; alpha = 0.5; }

    function onDeleteBtnMouseClick( evt:MouseEvent ):Void{
        _task.deleteJob(_job);
        _cbDelete();
    }

    public override function onMouseClick():Void{ }

    function onDecreaseBtnMouseClick( evt:MouseEvent ):Void{ 
        --_job._jumpToStep;
        if (_job._jumpToStep< 1 ){
            _job._jumpToStep= 1;
        }
        _number.text = ""+_job._jumpToStep;
    }
    function onIncreaseBtnMouseClick( evt:MouseEvent ):Void{ 
        ++_job._jumpToStep;
        if (_job._jumpToStep >= _job._index  ){
            _job._jumpToStep= _job._index -1;
            if( _job._jumpToStep == -1) _job._jumpToStep = 0;
        }
        _number.text = ""+_job._jumpToStep;
    }

    function onDecrCountBtnMouseClick( evt:MouseEvent ):Void{ 
        --_job._counter;
        if (_job._counter< 0 ){
            _job._counter= 0;
        }
        _job._current = _job._counter;
        _counter.text = ""+_job._counter;
    }
    function onIncrCountBtnMouseClick( evt:MouseEvent ):Void{ 
        _job._current = ++_job._counter;
        _counter.text = ""+_job._counter;
    }

    public function cannceEdit(){
        if(_increase != null){
            _increase.removeEventListener(  MouseEvent.CLICK, onIncreaseBtnMouseClick); 
            _s.removeChild(_increase);
            _increase= null;

            _decrease.removeEventListener(  MouseEvent.CLICK, onDecreaseBtnMouseClick); 
            _s.removeChild(_decrease);
            _decrease= null;

            _incrCounter.removeEventListener(  MouseEvent.CLICK, onIncrCountBtnMouseClick); 
            _s.removeChild(_incrCounter);
            _incrCounter= null;

            _decrCounter.removeEventListener(  MouseEvent.CLICK, onDecrCountBtnMouseClick); 
            _s.removeChild(_decrCounter);
            _decrCounter= null;
        }
    }
    function onEditBtnMouseClick( evt:MouseEvent ):Void{ 
        if (_increase == null){
            _increase= new EmbedTextField();
            _increase.selectable = false;
            _increase.text = "+";
            _increase.scaleX = 3;
            _increase.scaleY = 3;
            _increase.width = 10;
            _increase.height= 16;
            _increase.x = 380;
            _increase.addEventListener( MouseEvent.CLICK, onIncreaseBtnMouseClick);

            _decrease= new EmbedTextField();
            _decrease.selectable = false;
            _decrease.text = "-";
            _decrease.scaleX = 3;
            _decrease.scaleY = 3;
            _decrease.width = 10;
            _decrease.height= 16;
            _decrease.x = 280;
            _decrease.addEventListener( MouseEvent.CLICK, onDecreaseBtnMouseClick);

            _incrCounter= new EmbedTextField();
            _incrCounter.selectable = false;
            _incrCounter.text = "+";
            _incrCounter.scaleX = 3;
            _incrCounter.scaleY = 3;
            _incrCounter.width = 10;
            _incrCounter.height= 16;
            _incrCounter.x = 580;
            _incrCounter.addEventListener( MouseEvent.CLICK, onIncrCountBtnMouseClick);

            _decrCounter= new EmbedTextField();
            _decrCounter.selectable = false;
            _decrCounter.text = "-";
            _decrCounter.scaleX = 3;
            _decrCounter.scaleY = 3;
            _decrCounter.width = 10;
            _decrCounter.height= 16;
            _decrCounter.x = 480;
            _decrCounter.addEventListener( MouseEvent.CLICK, onDecrCountBtnMouseClick);

            _s.addChild( _decrease);
            _s.addChild( _increase);
            _s.addChild( _decrCounter);
            _s.addChild( _incrCounter);
        }else{
            cannceEdit();
        }
    }

    override function show(){
        if ( _s != null) {
            if ( _pos!= null){
                _s.removeChild(_pos);
                _s.removeChild(_deleteBtn);
                _s.removeChild(_editBtn);
                _s.removeChild(_number);
                _s.removeChild(_counter);
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

            _number= new EmbedTextField();
            _number.selectable = false;
            _number.text = ""+ _job._jumpToStep;
            _number.scaleX = 3;
            _number.scaleY = 3;
            _number.width = 50;
            _number.height= 16;
            _number.x = 330;

            _counter= new EmbedTextField();
            _counter.selectable = false;
            _counter.text = ""+ _job._counter;
            _counter.scaleX = 3;
            _counter.scaleY = 3;
            _counter.width = 50;
            _counter.height= 16;
            _counter.x = 530;

            _editBtn= new EmbedTextField();
            _editBtn.selectable = false;
            _editBtn.text = "Edit";
            _editBtn.scaleX = 3;
            _editBtn.scaleY = 3;
            _editBtn.width = 30;
            _editBtn.height= 16;
            _editBtn.setBorder(true);
            _editBtn.x = nme.Lib.current.stage.stageWidth - 180;
            _editBtn.addEventListener( MouseEvent.CLICK, onEditBtnMouseClick);

            _s.addChild( _pos);
            _s.addChild( _deleteBtn);
            _s.addChild( _editBtn);
            _s.addChild( _number);
            _s.addChild( _counter);
            _s.height = nme.Lib.current.stage.stageHeight/15;
        }
        return super.show();
    }
    override function hide(){
        if ( _s != null && _pos != null) {
            _deleteBtn.removeEventListener(  MouseEvent.CLICK, onDeleteBtnMouseClick); 
            if (_increase != null){ onEditBtnMouseClick(null); }
            _s.removeChild(_pos);
            _s.removeChild(_deleteBtn);
            _s.removeChild(_number);
            _s.removeChild(_counter);
            _pos= null;
            _deleteBtn= null;
            _number= null;
            _counter= null;
        }
        return super.hide();
    }

    public function createElement():Sprite{
        _s= new Sprite();
        return _s;
    }
}
