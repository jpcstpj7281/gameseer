package base.ui;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import nme.display.Sprite;

import com.eclecticdesignstudio.dialog.DialogManager;
import base.social.SocialMgr;
import nme.events.MouseEvent;

import base.social.SinaWeibo;
class SinaBinderDlg extends CommDialog{

    var _content:Sprite;
    public function new ( dm:ListDialogMgr):Void{
        _uniqueId = Type.getClassName( SinaBinderDlg);
        super(dm);
        resetDlgs();
    }

    public function resetDlgs():Void{
        var sina:SinaWeibo = SocialMgr.getInst()._socials.get( Type.getClassName(SinaWeibo));
        //trace(  Type.getClassName(base.social.SinaWeibo));
        var str= null;
        var dm:ListDialogMgr= cast _mgr;
        if ( sina != null && sina.isBound() ) {
            str= "解除绑定新浪微博";
        }
        else{
            str= "绑定新浪微博";
        }
        if ( _content!= null && _content.parent != null ){
            _content.parent.removeChild(_content);
        }
        _content = CommDialogMgr.getElement( str, 0);
        addChild( _content);
    }

    override function onMouseClick():Void{
        //trace("onMouseClick");
        var sina:SinaWeibo = SocialMgr.getInst()._socials.get( Type.getClassName(SinaWeibo));
        if ( sina != null && sina.isBound() ) {
            sina.unBound();
        }else{
            SocialMgr.getInst().bindSina();
            trace("bindSina");
        }
        resetDlgs();
    }
}

class SocialBinderDlg extends ListDialog {

    var _binder:SinaBinderDlg;

    public function new ( mgr:ListDialogMgr){
        var str:String = "绑定SNS";
        var id:Int = 0;
        _uniqueId = str+id;
        var s:Sprite = mgr.createElement( str, id);
        super(  mgr);
        addChild(s);
        _binder = new SinaBinderDlg(  _listDialogMgr);
    }

    public function createDlgs():Void{
        //var sina= SocialMgr.getInst()._socials.get( Type.getClassName(base.social.SinaWeibo));
        //var str:String = null;
        //if ( sina.isBound() == false ){
        //str= "绑定新浪微博";
        //}else{
        //str= "解除绑定新浪微博";
        //}
        //var id:Int = 0;
        //var s:Sprite = _listDialogMgr.createElement( str, id);
    }

    override function onMouseClick():Void{
        trace("onMouseClick");
        _binder.resetDlgs();
        super.onMouseClick();
    }
    //public function resetDlgs():Void{
        //createDlgs();
        //}

}
