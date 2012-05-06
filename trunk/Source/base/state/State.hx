package base.state;



class State{
    
    public var _nextStates:Array<State>;
    public var _preStates:Array<State>;

    public var _id:String;


    public var _sm:StateMachine;
    public var _isRunning:Bool;

    public function new( id:String ){
        _nextStates = new Array<State>();
        _preStates= new Array<State>();
        _id = id;
        _isRunning=false;
    }


    public function fromState( s:State):Void{
    }

    public function toState( s:State):Void{
    }

    public function run():Bool{
        return false;
    }

    public function die():Void{
    }

    public function init( sm:StateMachine ){
        _sm = sm;
        _sm.addState( this);
    }


}

