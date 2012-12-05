package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;


class Task{

    public var _index:Int;

    public var _startDate:Date;
    public var _endDate:Date;
    public var _preDelay:Int;
    public var _postDelay:Int;

    public var _jobs:Array<Job>;

    public function new(index:Int){
        _index = index;
        _startDate = Date.fromTime( Date.now().getTime()+ 5000);
        _endDate = Date.now();
        _preDelay = 0;
        _postDelay = 0;
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

    public function start(){
    }
    public function stop(){
    }

    public function run( date:Date){

        if ( date.getTime() >= _startDate.getTime()){
            start();
        }
        if ( date.getTime() >= _endDate.getTime()){
            stop();
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
