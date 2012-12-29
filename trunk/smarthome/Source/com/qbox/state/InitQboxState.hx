package com.qbox.state;

import base.state.State;
import base.state.StateMachine;
import base.state.LoadDataState;
import base.state.LoadConfState;
import base.state.InitNetworkState;
import base.state.StateMachine;
import base.state.InitBaseState;

class InitQboxState extends State{


    public function new( ){
        super("InitQboxState");
    }

    override function init( sm:StateMachine ):Void{ 
        super.init(sm);
        var loadConfState:LoadConfState = new LoadConfState();
        _nextStates.push(loadConfState);
        loadConfState.init( _sm);

        var loadDataState:LoadDataState = new LoadDataState();
        loadConfState._nextStates.push(loadDataState);
        loadDataState.init( _sm);

        //var initNetworkState:InitNetworkState= new InitNetworkState();
        //loadDataState._nextStates.push(initNetworkState);
        //initNetworkState.init( _sm);

        //var initSocialState:InitSocialState= new InitSocialState();
        //initNetworkState._nextStates.push(initSocialState);
        //initSocialState.init( _sm);

        var initMainState:InitMainState= new InitMainState();
        loadDataState._nextStates.push(initMainState);
        //initSocialState._nextStates.push( initMainState);
        //initMainState._nextStates.push(initNetworkState);
        initMainState.init( _sm);


        //var initBaseState:InitBaseState= new InitBaseState();
        //initNetworkState._nextStates.push(initBaseState);
        //initBaseState._nextStates.push(initMainState);
        //initBaseState.init( _sm);

        //var initSocialState:InitSocialState= new InitSocialState();
        //initMainState._nextStates.push(initSocialState);
        //initSocialState._nextStates.push( initMainState);
        //initSocialState.init( _sm);

        //var initUnconnectedState:InitUnconnectedState = new InitUnconnectedState();
        //initMainState._nextStates.push(initUnconnectedState);
        //initUnconnectedState.init( _sm);
        //initUnconnectedState._nextStates.push(initMainState);
        //initUnconnectedState._nextStates.push( initSocialState);

    }
    override function fromState( s:State ):Void{ }
    override function toState( s:State ):Void{ }


}
