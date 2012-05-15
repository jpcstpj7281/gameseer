package base.ui;

import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

import com.pictionary.ui.DrawingDlgMgr;
class EditDlg extends FixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("btn_edit")));
        x = nme.Lib.current.stage.stageWidth - 160;
        y= nme.Lib.current.stage.stageHeight - 80;
    }

    public override function onMouseClick( ):Void{
        if ( _mgr.isAnimating() ) return;
        if ( Std.is( _mgr, ComponentDlgMgr)){
            cast(_mgr, ComponentDlgMgr).toggleFixed();
        }
    }
}
