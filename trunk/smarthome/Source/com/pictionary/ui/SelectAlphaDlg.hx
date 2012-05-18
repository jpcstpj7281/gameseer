package com.pictionary.ui;

import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.display.DisplayObject;

import haxe.Timer;
import com.pictionary.ui.DrawingDlgMgr;
import base.ui.FixedDlg;
import base.ui.CommDialogMgr;
class SelectAlphaDlg extends FixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("pan")));
        x = 180;
        y= nme.Lib.current.stage.stageHeight - 155;
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        if ( Std.is( _mgr, DrawingDlgMgr)){
        }
    }
}
