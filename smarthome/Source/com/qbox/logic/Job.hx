package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;

class TimeCountJob extends Job { 

    public var _countTime:Int;
    public var _stopInterval:Float;
    public var _stopTime:Float;
    public var _currTime:Float;

    public function new (index:Int, task:Task, stopInterval:Float = 0){
        super(index, task);
        setInterval( stopInterval);
    }

    override public function start(date:Date){
        _stopTime = _stopInterval+ date.getTime();
        super.start(date);
    }

    public function setInterval( stopInterval:Float){
        if ( _isRunning){
            trace("error: you have to stop it, before set interval!");
        }else{
            _stopInterval = stopInterval;
        }
    }

    public function getRemainHours(){ 
        var remain = _stopInterval;
        if ( _startTime != 0){
            remain = _stopTime - _currTime;
        }
        var hours= Std.int( remain/ 3600000) ;
        return hours;
    }
    public function getRemainMinutes(){ 
        var remain = _stopInterval;
        if ( _startTime != 0){
            remain = _stopTime - _currTime;
        }
        var minutes= Std.int(remain/ 60000) %60;
        return minutes;
    }
    public function getRemainSeconds(){ 
        var remain = _stopInterval;
        if ( _startTime != 0){
            remain = _stopTime - _currTime;
        }
        var secs= Std.int(remain/ 1000) %60 ;
        return secs;
    }

    override public function run(date:Date):Bool{
        if ( _isRunning){
            if ( date.getTime() > _stopTime){
                stop(date);
                return false;
            }
            _currTime = date.getTime();
            if (_cbRun!= null) _cbRun();
            return true;
        }
        return false;
    }
    override public function save(){
        var sb = new StringBuf();
        sb.add("TimeCountJob:"+_stopInterval);
        var data =  sb.toString();
        DataLoader.getInst().saveData( "Task"+_task._index+"Job"+_index, data);
    }
}

class JumpToStepJob extends Job { 

    public var _jumpToStep:Int;
    public var _counter:Int;
    public var _current:Int;

    public function new (index:Int, task:Task, jumpToStep:Int = 0, counter:Int = 3){
        super(index, task);
        _jumpToStep = jumpToStep;
        _counter = counter;
        _current = counter;
    }

    public override function stop(date:Date){
        super.stop(date);
        _current = _counter;
    }

    override public function run(date:Date):Bool{
        if ( _isRunning){
            var res:Bool= false;
            if (_current > 0){
                _task._currJobIndex = _jumpToStep;
                --_current;
                res = true;
            }else{
                res = false;
            }
            if (_cbRun!= null) _cbRun();
            if ( _current == -1) stop(date);
            return res;
        }
        return false;
    }
    override public function save(){
        var sb = new StringBuf();
        sb.add("jumpToStep:"+_jumpToStep);
        var data =  sb.toString();
        DataLoader.getInst().saveData( "Task"+_task._index+"Job"+_index, data);
    }
}
class ModeExecJob extends Job { 

    public var _modeIndex:Int;
    var _isDone:Bool;

    public function new (index:Int, task:Task, modeIndex:Int = 0){
        super(index, task);
        _modeIndex = modeIndex ;
    }

    function cbDone(){
        _isDone = true;
    }

    override public function run(date:Date):Bool{
        if ( _isRunning){
            var ms = ModeMgr.getInst()._modes;
            if ( ms.length > _modeIndex){
                _isDone = false;
                ms[_modeIndex].load(cbDone);
                if (_cbRun!= null) _cbRun();
            }
            if (_isDone){
                stop(date);
                return false;
            }else return true;
        }
        return false;
    }
    override public function save(){
        var sb = new StringBuf();
        sb.add("ModeExecJob:"+_modeIndex);
        var data =  sb.toString();
        DataLoader.getInst().saveData( "Task"+_task._index+"Job"+_index, data);
    }
}

class Job{

    public var _index:Int;

    public var _isRunning:Bool;
    var _startTime:Float;
    var _task:Task;

    public var _cbStart:Void->Void;
    public var _cbRun:Void->Void;
    public var _cbStop:Void->Void;

    public function new(id:Int, task:Task ){
        _index = id;
        _isRunning = false;
        _task = task;
        _startTime = 0;
    }

    public function close(){
    }

    public function start( data:Date){
        _isRunning = true;
        _startTime = data.getTime();
        if (_cbStart != null) _cbStart();
    }
    public function stop(data:Date){
        _startTime = 0;
        _isRunning = false;
        if (_cbStop!= null) _cbStop();
    }

    public function load(){
        var data = DataLoader.getInst().getData( "Task"+_task._index+"Job"+_index);
        trace(data);
    }
    public function save(){
    }

    inline public function isRunning():Bool{
        return _isRunning;
    }

    //if return true, then continue to use current job at next time, otherwise go to next job.
    public function run( date:Date):Bool{
        if (_isRunning){
            if (_cbRun!= null) _cbRun();
            return true;
        }
        return false;
    }
}
