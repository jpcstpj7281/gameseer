package com.blueseer.state;

import base.state.State;
import base.state.StateMachine;
import base.state.LoadDataState;
import base.state.LoadConfState;
import base.state.InitNetworkState;
import base.state.InitBaseState;

class InitState extends State{


    public function new( ){
        super("InitState");
    }

    override function init( sm:StateMachine ):Void{ 
        super.init(sm);
        var loadConfState:LoadConfState = new LoadConfState();
        _nextStates.push(loadConfState);
        loadConfState.init( _sm);
        
        var loadDataState:LoadDataState = new LoadDataState();
        loadConfState._nextStates.push(loadDataState);
        loadDataState.init( _sm);

        var initNetworkState:InitNetworkState= new InitNetworkState();
        loadDataState._nextStates.push(initNetworkState);
        initNetworkState.init( _sm);

        var initBaseState:InitBaseState= new InitBaseState();
        initNetworkState._nextStates.push(initBaseState);
        initBaseState.init( _sm);

        //var initUIState:InitUIState= new InitUIState();
        //initBaseState._nextStates.push(initUIState);
        //initUIState.init( _sm);

        var initDeviceState:InitDeviceState= new InitDeviceState();
        initBaseState._nextStates.push(initDeviceState);
        initDeviceState._nextStates.push( initBaseState);
        initDeviceState._nextStates.push( initNetworkState);
        initDeviceState.init( _sm);

        var initUnconnectedState:InitUnconnectedState = new InitUnconnectedState();
        initBaseState._nextStates.push(initUnconnectedState);
        initUnconnectedState.init( _sm);
        initUnconnectedState._nextStates.push(initBaseState);
        initUnconnectedState._nextStates.push(initNetworkState);
        initUnconnectedState._nextStates.push( initDeviceState);

    }
    override function fromState( s:State ):Void{ }
    override function toState( s:State ):Void{ }

    
}
