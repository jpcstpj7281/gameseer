package com.ac.state;

import base.state.State;
import base.state.StateMachine;
import base.state.LoadDataState;
import base.state.LoadConfState;
import base.state.InitNetworkState;
import base.state.StateMachine;
import base.state.InitBaseState;

class InitACState extends State{


    public function new( ){
        super("InitACState");
    }

    override function init( sm:StateMachine ):Void{ 
        super.init(sm);
        var loadConfState:LoadConfState = new LoadConfState();
        _nextStates.push(loadConfState);
        loadConfState.init( _sm);

        var loadDataState:LoadDataState = new LoadDataState();
        loadConfState._nextStates.push(loadDataState);
        loadDataState.init( _sm);

        var initMainState:InitMainState= new InitMainState();
        loadDataState._nextStates.push(initMainState);
        initMainState.init( _sm);
    }
    override function fromState( s:State ):Void{ }
    override function toState( s:State ):Void{ }
}
