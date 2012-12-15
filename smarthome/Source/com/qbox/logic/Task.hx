package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;

import com.qbox.logic.Job;

class Task{

    public var _index:Int;

    public var _startDate:Date;
    public var _endDate:Date;

    public var _jobs:Array<Job>;

    public var _isRunning:Bool;

    public var _currJobIndex:Int;

    public function new(index:Int){
        _index = index;
        _startDate = null;
        _endDate = null;
        _jobs = new Array<Job>();
        _currJobIndex = 0;
    }

    public function close(){
    }

    public function hasData(){
        return  DataLoader.getInst().getData( "task"+_index ) != null;
    }

    public function load(){
        var count = 0;
        while( true){
            var data:String = DataLoader.getInst().getData( "Task"+_index+"Job"+count );
            if ( data == null ) break;
            var j:Job = null;
            if ( _jobs.length<= count){
                j = _jobs[count];
            }else{
                var type = data.substr(0, 4);
                if ( type == "Time"){
                    j = createTimer();
                }else if ( type == "Jump"){
                    j = createJumper();
                }else if ( type == "Mode"){
                    j = createModeExec();
                }
            }
            ++count;
        }
    }

    public function save(){
        for ( i in _jobs){ 
            i.save(); 
        }
    }

    public function deleteJob( m:Job):Void{
        for ( i in m._index..._jobs.length){
            DataLoader.getInst().saveData( "Task"+_index+"Job"+_jobs[i]._index, null);
            -- _jobs[i]._index;
            _jobs[i].save();
        }
        _jobs.remove(m);
    }

    public function createTimer():TimeCountJob{
        var c = new TimeCountJob(_jobs.length, this, 10000);
        _jobs.push( c);
        return c;
    }
    public function createJumper():JumpToStepJob{
        var c = new JumpToStepJob(_jobs.length, this, 0, 3);
        _jobs.push( c);
        return c;
    }
    public function createModeExec():ModeExecJob{
        var c = new ModeExecJob(_jobs.length, this, 0);
        _jobs.push( c);
        return c;
    }

    public function start(){
        _isRunning = true;
        trace("start task");
    }

    public function stop(){
        _isRunning = false;
        for ( i in _jobs){
            if ( i._isRunning ){
                i.stop(Date.now());
            }
        }
        trace("stop task");
    }

    public function run( date:Date){

        if ( _startDate != null && date.getTime() >= _startDate.getTime()){
            start();
        }
        if ( _endDate != null && date.getTime() >= _endDate.getTime()){
            stop();
        }

        if (_isRunning){
            if ( _currJobIndex < _jobs.length){
                if(! _jobs[_currJobIndex]._isRunning){
                    _jobs[_currJobIndex].start(date);
                }
                if ( !_jobs[_currJobIndex].run(date)){
                    ++_currJobIndex;
                }
            }
            else{
                stop();
                _currJobIndex = 0;
            }
        }


        //trace(date.getDate());
        //trace(date.getFullYear());
        //trace(date.getMonth());
        //trace(date.getHours());
        //trace(date.getMinutes());
        //trace(date.getSeconds());
        //trace(date.getTime());
    }
}
