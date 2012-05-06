package base.ui;

import com.blueseer.ui.UIMgr;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import base.network.SMConnection;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.network.NetworkMgr;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;

import base.ui.CommDialog;
import base.ui.ListDialogMgr;
class ConnDialog extends CommDialog{
    var _ipInput:EmbedTextField ;
    var _hint:EmbedTextField ;
    var _OK:EmbedTextField ;
    var _cancel:EmbedTextField ;

    public function new ( mgr:ListDialogMgr ){
        var str:String = "连接";
        var id:Int = 0;
        _uniqueId = str+id;
        var s:Sprite = mgr.createElement( str, id);
        super(  mgr);
        addChild(s);
    }

    override function onMouseClick(){
        if ( _mgr.isAnimating()) return;

        if ( _ipInput == null ){
            _ipInput= new EmbedTextField();
            _hint= new EmbedTextField();
            _OK= new EmbedTextField();
            _cancel= new EmbedTextField();
            _OK.text = "OK";
            _OK.scaleX = 3;
            _OK.scaleY = 3;
            _OK.y = 180;
            _OK.x = 100;
            _OK.height = 20;
            _OK.width = 20;
            _OK.setBorder(true);
            _OK.selectable = false;
            _cancel.text = "Cancel";
            _cancel.scaleX = 3;
            _cancel.scaleY = 3;
            _cancel.y = 180;
            _cancel.x = 200;
            _cancel.setBorder(true);
            _cancel.height = 20;
            _cancel.width = 20;
            _cancel.selectable = false;
            _OK.setBorder(true);
            _hint.selectable = false;
            _hint.text = "Input the ip of Controller";
            _hint.scaleX = 3;
            _hint.scaleY = 3;
            _hint.width = nme.Lib.current.stage.stageWidth;
            _hint.height= 20;
            _ipInput.text = "";
            _ipInput.type = INPUT;
            _ipInput.scaleX = 3;
            _ipInput.scaleY = 3;
            _ipInput.width = nme.Lib.current.stage.stageWidth;
            _ipInput.height= 20;
            _ipInput.setBorder(true);
            _ipInput.y= 100;
            _OK.addEventListener( MouseEvent.CLICK, onOK);
            _cancel.addEventListener( MouseEvent.CLICK, onCancel);

            _elements.push( _OK);
            _elements.push( _cancel);
            _elements.push( _hint);
            _elements.push( _ipInput);
        }

        showElements();
        nme.Lib.current.stage.focus = _ipInput;
        cast(_mgr, ListDialogMgr).hideListDialog( );
    }

    public function swichBackToCMDView():Void{
        hideElements();
        cast(_mgr, ListDialogMgr).showListDialog( );
    }

    //public override function clear():Void{
    //super.clear();
    //}

    public function onOK(evt:MouseEvent):Void{
        if( _ipInput.text != null && _ipInput.text.substr(0,2) != "__" ){
            var str = _ipInput.text;
            if (str.length == 0 ){
                str = base.conf.Config.connIP;
            }

            if ( str.length > 0){
                trace("reconnect to ip: "+ str);
                base.conf.Config.connIP = str;
                hideElements();
                base.state.StateMachine.getInst().toState( "InitBaseState");
            }
        }
        else{
            hideElements();
            swichBackToCMDView();
        }
    }

    public function onCancel(evt:MouseEvent){
        swichBackToCMDView();
    }
}

