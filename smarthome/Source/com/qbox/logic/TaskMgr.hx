package com.qbox.logic;

import base.data.DataLoader;
import haxe.Timer;


class TaskMgr{

    public static var inst:TaskMgr;
    inline public static function getInst():TaskMgr{
        if ( inst == null) {
            inst = new TaskMgr();
        }
        return inst;
    }

    //Array< Qbox>, container of Qboxes.
    public var _tasks:Array<Task>;
    //public var _timer:Timer;

    public function new(){
        _tasks =  new Array<Task>();
        while(true){
            var c = new Task(_tasks.length);
            if( c.hasData()){
                _tasks.push( c);
            }
            else{
                break;
            }
        }
        //_timer = new Timer(300);
        Lib.current.addEventListener(Event.ENTER_FRAME, loop);
        //_timer.run = trun;
    }


    function trun(){
        var d  = Date.now();
        for( i in _tasks){
            i.run( d );
        }
    }

    public function deleteTask( m:Task):Void{
        for ( i in m._index..._tasks.length){
            DataLoader.getInst().saveData( "Task"+_tasks[i]._index, null);
            -- _tasks[i]._index;
            _tasks[i].save();
        }
        _tasks.remove(m);
    }

    public function create():Task{
        var data:String = null;
        if ( _tasks.length>0){
            var m = _tasks[_tasks.length-1];
            data = DataLoader.getInst().getData( "Task"+ m._index );
        }
        var c = null;
        if ( data != null || _tasks.length == 0){
            c = new Task(_tasks.length);
            _tasks.push( c);
        }
        return c;
    }

    public function saveData(){
        for ( i in _tasks){
            i.save();
        }
    }

    inline public function removeTask( Task:Task):Void{ _tasks.remove(Task); }
    public function closeAll( ):Void{ 
        for ( i in _tasks){
            i.close();
            removeTask(i);
        }
    }

    public function removeQbox( c:Task){
        for ( i in _tasks){
            if ( c == i ){
                _tasks.remove( i ) ;
                break;
            }
        }
    }
}
