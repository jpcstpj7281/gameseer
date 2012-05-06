package base.state;

class StatePath{

    public var _stateList:Array<State>;

    public function new(){
    }
    public function addState( s:State){
        _stateList.push(s);
    }
    public function removeState( s:State){
        _stateList.remove(s);
    }
    public function generateStatePath( from:State, to:State){
        _stateList = new Array<State>();
        var sl:Array<State> = new Array<State>();
        if ( to == from ){
            _stateList.push(to);
        }else makeStatePath( from, to, sl);
    }
    private function makeStatePath( from:State, to:State, stateList:Array<State> ):Void{
        for( n in from._nextStates){
            var sl:Array<State> = stateList.copy( );

            for ( s in sl ){//出现循环就结束这次迭代
                if ( n == s ){
                    trace("terminate recursive");
                    return;
                }
            }
            //trace("test1");
            sl.push( n);
            //trace( sl);
            //trace( stateList);
            //trace( _stateList);
            //trace("n: " + n._id);
            //trace("t: " + to._id);
            //trace("test2");
            if ( n == to){
                //trace("test3");
                if ( _stateList.length ==0 || _stateList.length > sl.length){//还没生成LIST或少于已生成的LIST才更换
                    //trace("stateList: "+_stateList.length);
                    //trace( sl);
                    //trace( stateList);
                    //trace( _stateList);
                    trace("Make state path: ");
                    for( i in sl ){
                        trace("-->>"+ i._id);
                    }
                    _stateList = sl;
                }
                return ;
            }
            //trace("test4");
            makeStatePath( n , to , sl);
        }
    }

    public function empty():Bool{
        return _stateList == null || _stateList.length == 0;
    }

    public function pop():State{
        return _stateList.shift();
    }

}
