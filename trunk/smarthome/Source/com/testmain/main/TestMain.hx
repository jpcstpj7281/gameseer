package com.testmain.main;

//import org.aswing.BorderLayout;
//import org.aswing.FlowLayout;
//import org.aswing.GridLayout;
//import org.aswing.Insets;
//import org.aswing.JButton;
//import org.aswing.JFrame;
//import org.aswing.JLabel;
//import org.aswing.JPanel;
//import org.aswing.border.EmptyBorder;
//import org.aswing.geom.IntDimension;
import nme.display.Sprite;

import nme.text.TextField;
import nme.display.Stage;
import nme.display.StageAlign;
import nme.display.StageScaleMode;
import nme.Lib;

import nme.events.Event;

//import org.aswing.JButton;
//import org.aswing.JFrame;
//import org.aswing.geom.IntDimension;
//import org.aswing.AsWingManager;

import nme.Lib;
import nme.display.Sprite;
import nme.display.StageScaleMode;

import haxe.io.Bytes;
import haxe.io.BytesOutput;
import nme.display.BitmapData;
import nme.display.Bitmap;

import format.tools.Image;
import format.png.Writer;
import format.png.Reader;
#if sys
import sys.io.File;
#end


import nme.events.MouseEvent;
//import base.common.Tools;
//import base.social.SocialWorld;
//import base.social.SinaWeibo;

#if flash
import base.common.FlashConnect;
#end

#if android
import nme.sensors.Accelerometer;
import nme.events.AccelerometerEvent;
#end
/**
 * @author 
 */
class TestMain extends Sprite {


    public function new () {

        super ();
        initialize ();
    }

    //var sw:SinaWeibo ;
    //private static var labelPrefix : String = "Number of button clicks: ";
    //private var numClicks : Int ;
    //private var label : JLabel;
    //private var button : JButton;
    //var frame : JFrame ;

    private function initialize ():Void {
        //numClicks = 0;

        //Lib.current.stage.align = StageAlign.TOP_LEFT;
        //Lib.current.stage.scaleMode = StageScaleMode.NO_SCALE;

        //Config.ScaleX = Lib.current.stage.stageWidth / 480;
        //Config.ScaleY = Lib.current.stage.stageHeight / 320;

        //var is:InitState = new InitState();
        //is.init(StateMachine.getInst());

        /*
        base.conf.Config.getInst().loadConf(null);
        base.data.DataLoader.getInst().loadAssets(null);

        trace("test");
        AsWingManager.initAsStandard(nme.Lib.current);
        //org.aswing.AsWingManager.initAsStandard(nme.Lib.current.stage);

        trace("test");

        frame= new JFrame( this, "HelloApp中文" );
        frame.getContentPane().append( createCenterPane() );
        frame.setSize(new IntDimension( 200, 120 ) );
        */

        //org.aswing.LookAndFeel.installFont( frame, "test", base.data.DataLoader.getInst().textFormat_.font);
        //frame.setVisible(true);
        //nme.Lib.current.stage.addChild(this);

        //nme.Lib.current.stage.addEventListener(MouseEvent.CLICK, click );
        //if you want to create a "fullscreen" interface rather than
        //draggable window with title, use JWindow instead

        //trace("test");
        //frame.setSize(new IntDimension( 200, 120 ) );
        ////create a button
        //var button:JButton = new JButton("Hello from AsWing in Haxe!");
        //
        //trace("test");
        ////add the button to the frame
        //frame.getContentPane().append(button);
        //frame.getContentPane().append(new JButton("where r u") );
        //
        //trace("test");
        ////add the frame to the stage
        //Lib.current.stage.addChild(this);
        //this.stage.scaleMode = StageScaleMode.NO_SCALE;
        //
        //trace("test");
        ////show it!
        //frame.show();
        //
        //trace("test");

        //#if sys
        //saveBitmap();
        //#end    

        //testweibo();
    }

    //private function click(evt:MouseEvent):Void{
    //frame.show();
    //}
    //private function createCenterPane() : JPanel{
    //var pane : JPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
    //label = new JLabel(labelPrefix+"0");
    //button = new JButton("I'm a AsWing button!中文");
    //pane.append(button);
    //pane.append(label);
    //pane.setBorder(new EmptyBorder(null, new Insets(10,5,10,5)));
    //initHandlers();
    //return pane;
    //}
    //private function initHandlers() : Void{
    ////button.addActionListener( __pressButton );
    //button.addEventListener(MouseEvent.MOUSE_UP, __pressButton);
    //}
    //
    //private function __pressButton( e : Event ) : Void{
    //numClicks++;
    //label.setText(labelPrefix+numClicks);
    //label.revalidate();
    //}

    function testacceleromter(){
        ////if (Accelerometer.isSupported == false){
        //trace("dont has sensor");
        //return;
        //}
        //else trace("has sensor");
        //
        //var acc:Accelerometer = new Accelerometer();
        //acc.addEventListener( AccelerometerEvent.UPDATE, onSensor);
    }

    /*
    function testweibo(){

        sw = new SinaWeibo("4121333920", "0512e457b9a5f71fc0fb22a865dd7640");
        sw._sig.add( onLogin);
        var pin:String=null;
        var refresh:Bool = false;
#if flash
        pin= flash.Lib.current.root.loaderInfo.parameters.pin;
        var refreshstr= flash.Lib.current.root.loaderInfo.parameters.refresh;
        if ( refreshstr != null ) refresh = true;
#end
        sw.login( refresh , pin  );
    }
    */
    /*
    function saveBitmap(){
        var s:Sprite = new Sprite();
        s.graphics.clear();
        s.graphics.beginFill(0xf75544, .5);
        s.graphics.moveTo(50, 0);
        s.graphics.lineTo(100, 50);
        s.graphics.lineTo(50, 100);
        s.graphics.lineTo(0, 50);
        s.graphics.lineTo(50, 0);
        s.graphics.endFill();

        var b:BitmapData = new BitmapData(100,100, true,0);
        b.draw(s);
        var bitmap:Bitmap = new Bitmap(b);

        s.x = 50;
        addChild(s);
        addChild(bitmap);

        var strpng = Tools.converToPNGBytes(b);
        var str:String = strpng.readString(0, strpng.length);
        trace("Str len: "+str.length+ "png len: "+strpng.length);
        var str1:String = "";
        str1 += str;
        trace("Str len: "+str.length+ "str1 len: "+str1.length);

#if cpp
        File.write("test.png", true).writeBytes( strpng, 0, strpng.length);
#end
    }
    */

    //public function onSensor( evt:AccelerometerEvent){
    //trace("onSensor");
    //trace( " x: "+evt.accelerationX+" y: "+ evt.accelerationY+ " z: "+ evt.accelerationZ +" stamp: "+evt.timestamp);
    //}
    // Entry point
    public static function main () {
#if flash
        var debug:String = flash.Lib.current.root.loaderInfo.parameters.debug;
        if(debug == null){
            FlashConnect.redirect();
        }
#end
        //Lib.current.addChild (new TestMain ());
        new TestMain();
    }


}

