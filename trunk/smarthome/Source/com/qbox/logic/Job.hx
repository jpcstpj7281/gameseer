package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;


class Job{

    public var _id:Int;

    public var _preDelay:Int;
    public var _postDelay:Int;

    public var _jobs:Array<Job>;

    public function new(id:Int){
        _id = id;
        _preDelay = 0;
        _postDelay = 0;
    }

    public function close(){
    }

    public function hasData(){
        return  DataLoader.getInst().getData( "task"+_id ) != null;
    }
    public function load():Bool{
        var data:String = DataLoader.getInst().getData( "task"+_id );
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


        //trace(date.getDate());
        //trace(date.getFullYear());
        //trace(date.getMonth());
        //trace(date.getHours());
        //trace(date.getMinutes());
        //trace(date.getSeconds());
        //trace(date.getTime());
    }
}
