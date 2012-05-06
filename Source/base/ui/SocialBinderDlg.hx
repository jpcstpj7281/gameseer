package base.ui;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import nme.display.Sprite;

import com.eclecticdesignstudio.dialog.DialogManager;
import base.social.SocialMgr;
import nme.events.MouseEvent;

import base.social.SinaWeibo;
class SinaBinderDlg extends CommDialog{

    public function new (dd:DialogData, dm:ListDialogMgr):Void{
        super(dd);
        dialogManager = dm;
        dm.addDialog(this);
        this.addEventListener( MouseEvent.CLICK, onMouseClick);
    }

    public override function onMouseClick(evt:MouseEvent):Void{
        trace("onMouseClick");
        var sina:SinaWeibo = SocialMgr.getInst()._socials.get( Type.getClassName(SinaWeibo));
        trace(  Type.getClassName(base.social.SinaWeibo));
        if ( sina != null && sina.isBound() ) {
            sina.unBound();

            var dm:ListDialogMgr= cast dialogManager;
            var str= "绑定新浪微博";
            var s:Sprite = CommDialogMgr.getElement( str, 0);
            var dd:DialogData = dialogData;
            dd.display = s;
            dm.remove(this);
            var sd = new SinaBinderDlg( dd, dm);
            sd.show();
            clear();
        }
        else{
            SocialMgr.getInst().bindSina();
            //trace("bindSina");
            //var dm:ListDialogMgr= cast dialogManager;
            //var str= "解除绑定新浪微博";
            //var s:Sprite = CommDialogMgr.getElement( str, 0);
            //var dd:DialogData = dialogData;
            //dd.display = s;
            //dm.remove(this);
            //var sd = new SinaBinderDlg( dd, dm);
            //sd.show();
            //trace("add dialog1");
        }
    }
}

class SocialBinderDlg extends ListDialog {


    public function new ( cmdDlgMgr:ListDialogMgr){
        var str:String = "绑定SNS";
        var id:Int = 0;
        var s:Sprite = cmdDlgMgr.createElement( str, id);
        var dd:DialogData = cmdDlgMgr.createListDialogData( s, str+id );
        super( dd, cmdDlgMgr);
        cmdDlgMgr.addDialog( this);
        createDlgs();
    }

    public function createDlgs():Void{
        var sina= SocialMgr.getInst()._socials.get( Type.getClassName(base.social.SinaWeibo));
        var str:String = null;
        if ( sina.isBound() == false ){
            str= "绑定新浪微博";
        }else{
            str= "解除绑定新浪微博";
        }
        var id:Int = 0;
        var s:Sprite = _listDialogMgr.createElement( str, id);
        var dd:DialogData = _listDialogMgr.createListDialogData( s, str+id );
        var s = new SinaBinderDlg( dd, _listDialogMgr);
    }

    public function resetDlgs():Void{
        clear();
        createDlgs();

    }

}
