package base.ui;

import com.blueseer.cmd.Command;
import com.blueseer.cmd.CommandMgr;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogData;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.network.NetworkMgr;
import com.eclecticdesignstudio.motion.actuators.GenericActuator;

import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;

class ComponentDlg extends CommDialog{

    public var _downx:Float;
    public var _downy:Float;
    public var _isDown:Bool;

    public var _id:Int;

    public function new ( mgr:ComponentDlgMgr, name:String, id:Int ){
        var str:String = name;
        _id = id;
        _uniqueId = str+id;
        var s:Sprite = mgr.createElement( str, id);
        super( mgr);
        addChild(s);
        _isDown =false;
    }

    public override function showParent():Void{
        var dm:ComponentDlgMgr= cast (_mgr);
        dm.showListDialog();
    }
    public override function hideParent():Void{
        var dm:ComponentDlgMgr = cast (_mgr);
        dm.hideListDialog();
    }
}

