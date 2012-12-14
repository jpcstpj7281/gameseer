package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;

class TimeCountJob extends Job { 

    public var _countTime:Int;
    public var _stopInterval:Float;
    public var _stopTime:Float;

    public function new (index:Int, task:Task, stopInterval:Float = 0){
        super(index, task);
        _stopInterval = stopInterval;
    }

    override public function start(date:Date){
        _stopTime = _stopInterval+ date.getTime();
        super.start(date);
    }

    public function setInterval( stopInterval:Float){
        if ( _isRuning){
            trace("error: you have to stop it, before set interval!");
        }else{
            _stopInterval = stopInterval;
        }
    }

    override public function run(date:Date):Bool{
        if ( _isRuning){
            if ( date.getTime() > _stopTime){
                stop(date);
                return false;
            }
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

    public function new (index:Int, task:Task, jumpToStep:Int = 0){
        super(index, task);
        _jumpToStep = jumpToStep;
    }

    override public function run(date:Date):Bool{
        if ( _isRuning){
            stop(date);
            _task._currJobIndex = _jumpToStep;
            return true;
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

    public function new (index:Int, task:Task, modeIndex:Int = 0){
        super(index, task);
        _modeIndex = modeIndex ;
    }

    override public function run(date:Date):Bool{
        if ( _isRuning){
            stop(date);
            var ms = ModeMgr.getInst()._modes;
            if ( ms.length > _modeIndex){
                ms[_modeIndex].load();
            }
            return false;

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

    public var _isRuning:Bool;
    var _startTime:Float;

    var _task:Task;

    public function new(id:Int, task:Task ){
        _index = id;
        _isRuning = false;
        _task = task;
    }

    public function close(){
    }

    public function start( data:Date){
        _isRuning = true;
        _startTime = data.getTime();
    }
    public function stop(data:Date){
        _isRuning = false;
    }

    public function load(){
        var data = DataLoader.getInst().getData( "Task"+_task._index+"Job"+_index);
        trace(data);
    }
    public function save(){
    }

    inline public function isRuning():Bool{
        return _isRuning;
    }

    //if return true, then continue to use current job at next time, otherwise go to next job.
    public function run( date:Date):Bool{
        if (_isRuning){
            return true;
        }
        return false;
    }
}
