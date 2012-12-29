package com.ac.main;

import nme.display.Sprite;
import nme.Lib;
/*
   class ACMain 
   {

   static public function main()
   {
//#if flash
new ACMain();
//#else 
//Lib.create(function(){new Main();},800,600,60,0xccccff,(1*Lib.HARDWARE) | Lib.RESIZABLE, "AsWing_Paling_UI");
//
//#end

}

public  function new():Void
{  
AsWingManager.initAsStandard( Lib.current);

var sp:org.aswing.JLabel= new  org.aswing.JLabel("*****sdew中文");

sp.setSizeWH(100, 30);
sp.setLocationXY(10, 10);
Lib.current.addChild(sp);
var jb:JButton = new JButton("__ewwesew中文");
jb.setSizeWH(100, 20);
jb.setLocationXY(300, 300);

Lib.current.addChild(jb);
var tt : JFrame = new JFrame( Lib.current,"TestAswing中文");

tt.setSizeWH(300,300);
tt.setLocationXY(100,100);
tt.show(); 
}
}
 */

import nme.display.Sprite;

import nme.display.Stage;
import nme.display.StageAlign;
import nme.display.StageScaleMode;
import nme.Lib;
import nme.text.TextField;
import base.conf.Config;
import base.state.StateMachine;
import com.ac.state.InitACState;


#if flash
import base.common.FlashConnect;
#end

class ACMain extends Sprite {

    static public function main()
    {
#if flash FlashConnect.redirect(); #end
        Lib.current.addChild (new ACMain());
    }

    public function new () {

        super ();
        initialize ();
    }

    private function initialize ():Void {
        Lib.current.stage.align = StageAlign.TOP_LEFT;
        Lib.current.stage.scaleMode = StageScaleMode.NO_SCALE;

        Config.ScaleX = Lib.current.stage.stageWidth / 480;
        Config.ScaleY = Lib.current.stage.stageHeight / 320;

        Config.confFileName = "qbox.xml";
        Config.appName = "Qbox";
        var is= new InitACState();
        is.init(StateMachine.getInst());
    }
}

