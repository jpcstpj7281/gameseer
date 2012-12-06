package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;


class Task{

    public var _index:Int;

    public var _startDate:Date;
    public var _endDate:Date;

    public var _jobs:Array<Job>;

    public var _isRunning:Bool;

    public var _currJobIndex:Int;

    public function new(index:Int){
        _index = index;
        _startDate = Date.fromTime( Date.now().getTime()+ 5000);
        _endDate = Date.now();
    }

    public function close(){
    }

    public function hasData(){
        return  DataLoader.getInst().getData( "task"+_index ) != null;
    }

    public function load():Bool{
        var data:String = DataLoader.getInst().getData( "task"+_index );
        trace(data);
        return true;
    }

    public function save(){
        var sb = new StringBuf();
        var ts = TaskMgr.getInst()._tasks;
        var count:Int = 0;
        for ( i in ts){
            ++count;
            sb.add( "task:"+ count++ +":");
            sb.add("test");
            sb.add("=");
        }
    }

    inline public function start(){
        _isRunning = true;
    }

    inline public function stop(){
        _isRunning = false;
    }

    public function run( date:Date){

        if ( date.getTime() >= _startDate.getTime()){
            start();
        }
        if ( date.getTime() >= _endDate.getTime()){
            stop();
        }

        if (_isRunning){
            if ( _currJobIndex < _jobs.length){
                if ( !_jobs[_currJobIndex].run(date)){
                    ++_currJobIndex;
                }
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
