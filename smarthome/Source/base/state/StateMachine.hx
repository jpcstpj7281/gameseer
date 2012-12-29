
package base.state;


import base.state.State;
import nme.Lib;
import nme.events.Event;

//import base.common.Tools;

class StateMachine{

	public static  var inst:StateMachine;
	inline public static function getInst():StateMachine {
		if ( inst == null) {
			inst = new StateMachine();
		}
		return inst;
	}

    public var _allStates:Hash<State>;

    public var _curState:State;

    public var _statePath:StatePath;

    function new (){
         _allStates = new Hash<State>();
         Lib.current.addEventListener(Event.ENTER_FRAME, loop);

         _statePath = new StatePath();
    }

    private function loop( evt:Event ):Void{
        var res:Bool = _curState.run();
        //trace(_curState);
        //trace(res);
        //trace(_statePath.empty());
        if( _curState != null &&  !res ){
            //trace("loop6");
            var next:State = null;
            var pre:State = null;
            pre = _curState;
            if ( _statePath.empty() ){
                //trace("loop5");
                if ( _curState._nextStates.length != 0){
                    next = _curState._nextStates[0];//获取下一个状态
                    trace("get state in next arr: " + next._id);
                    //trace("len: "+_curState._nextStates.length);
                }
            }else{
                //trace("loop0");
                next = _statePath.pop();
                trace("get state in state path: " + next._id);
                //trace("loop1");
            }
            if ( next == null){
                Lib.current.removeEventListener( Event.ENTER_FRAME, loop);
                trace("Got a null next State, terminate State Machine loop! current state: " + _curState._id);
                return ;
            }
            _curState = next;
            //trace( pre._id);
            trace( "before " + pre._id + "->" + next._id);
            pre.toState( next);
            next.fromState(pre);

        }else if ( _curState != null && res &&  !_statePath.empty() ){
            //trace("loop3");
            var next:State = null;
            var pre:State = null;
            pre = _curState;
            next = _statePath.pop();

            _curState = next;
            //trace( pre._id);
            trace( "before " + pre._id + "->" + next._id);
            pre.toState( next);
            next.fromState(pre);
        }
        //trace("run");
    }

    public function getState( id:String):State{
        return _allStates.get(id);
    }



    public function addState( state:State):Void{
        if ( Lambda.count(_allStates) == 0){
            _curState = state;
        }
        _allStates.set( state._id, state);
    }


    public function postState( ):Bool{
        if(  _curState._nextStates.length != 1 ){
            return false;
        }

        return true;
    }


    public function toState( stateid:String) :Void{
        var state:State = _allStates.get(stateid );
        //Tools.assert( state != null );

        _statePath.generateStatePath( _curState, state);

        //_curState.toState(state ) ;
    }

}

