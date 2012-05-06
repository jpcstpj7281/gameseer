package com.blueseer.main;


import nme.display.Sprite;

import nme.display.Stage;
import nme.display.StageAlign;
import nme.display.StageScaleMode;
import nme.Lib;
import nme.text.TextField;
import base.conf.Config;
import base.state.StateMachine;
import com.blueseer.state.InitState;


#if flash
import base.common.FlashConnect;
#end

/**
 * @author 
 */
class SmartHome extends Sprite {


    public function new () {

        super ();
        initialize ();
    }

    private function initialize ():Void {

        Lib.current.stage.align = StageAlign.TOP_LEFT;
        Lib.current.stage.scaleMode = StageScaleMode.NO_SCALE;

        Config.ScaleX = Lib.current.stage.stageWidth / 480;
        Config.ScaleY = Lib.current.stage.stageHeight / 320;

        var is:InitState = new InitState();

        is.init(StateMachine.getInst());

    }
    public static function main () {
#if flash
        //FlashConnect.redirect();
#end
        Lib.current.addChild (new SmartHome ());
    }


}

