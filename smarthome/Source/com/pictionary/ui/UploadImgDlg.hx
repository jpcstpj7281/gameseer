package com.pictionary.ui;

import base.ui.CommDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import nme.display.DisplayObject;

import haxe.Timer;
import base.ui.FixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListFixedDlg;
import nme.geom.Matrix;
import nme.display.BitmapData;

class UploadImgDlg extends ListFixedDlg{


    public function new ( dm:CommDialogMgr ){

        var m = new Matrix();
        m.rotate(3.14/2);
        m.translate( 60, 0);
        var bmt = DataLoader.getInst().bms_.get("exit");
        var bmd = new BitmapData(bmt.width, bmt.height);
        bmd.draw( bmt, m);
        var bm= new Bitmap( bmd);

        super(dm, bm);
        //_upload.addChild( bm);
        x = 160;
        y= nme.Lib.current.stage.stageHeight - 80;
        //_upload.addEventListener( MouseEvent.CLICK, onClickUpload);
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;

        if ( _listDialogMgr._movableInstances.length == 0 ){
            new base.ui.InputDialog( _listDialogMgr, "test", 0);
            new base.ui.InputDialog( _listDialogMgr, "test", 1);
        }
        super.onMouseClick();
        hideParent();
        //cast( _mgr, DrawingDlgMgr).uploadImg();
    }

    public override function showParent():Void{
        var dm:DrawingDlgMgr = cast (_mgr);
        dm.showListDialog();
    }
    public override function hideParent():Void{
        var dm:DrawingDlgMgr = cast (_mgr);
        dm.hideListDialog();
    }
}
