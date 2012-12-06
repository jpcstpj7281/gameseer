package com.qbox.logic;

import hxjson2.JSON;
import base.data.DataLoader;

class TimeCountJob extends Job { 

    public var _countTime:Int;

    public var _stopInterval:Float;
    public var _stopTime:Float;

    public function new (index:Int, stopInterval:Float = 0){
        super(index);
        _stopInterval = stopInterval;
    }

    override public function start(date:Date){
        _stopTime = _stopInterval+ date.getTime();
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
}

class Job{

    public var _index:Int;

    public var _isRuning:Bool;
    var _startTime:Float;

    public function new(id:Int){
        _index = id;
        _isRuning = false;
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

    inline public function isRuning():Bool{
        return _isRuning;
    }

    public function run( date:Date):Bool{
        if (_isRuning){
            return true;
        }
        return false;
    }
}
