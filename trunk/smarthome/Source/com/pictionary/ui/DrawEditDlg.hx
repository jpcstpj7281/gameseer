package com.pictionary.ui;

import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import com.pictionary.ui.DrawingDlgMgr;
import base.ui.FixedDlg;
class DrawEditDlg extends FixedDlg{
    public function new ( dm:DrawingDlgMgr){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("btn_edit")));
        x=20;
        y= nme.Lib.current.stage.stageHeight - 80;
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        if ( Std.is( _mgr, DrawingDlgMgr)){
            cast(_mgr, DrawingDlgMgr).toggleFixed();
        }
    }
}
