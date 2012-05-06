
package com.pictionary.ui;

import base.ui.InputDialog;



class UserNameInputDlg extends InputDialog{


    dynamic override function fireInput( data:String):Void{
        base.data.DataLoader.getInst().saveData( "usrname", data);
        base.state.StateMachine.getInst().toState("InitMainState");
        trace("Fired!");
    }
}
