package base.ui;

import com.eclecticdesignstudio.motion.actuators.GenericActuator;
import com.eclecticdesignstudio.motion.Actuate;

import nme.display.Sprite;
import nme.display.DisplayObject;
import nme.events.MouseEvent;


class CommDialog extends Sprite{


    //一些需要集体添加显示删除隐藏的自定义的图像
    var _elements:Array<DisplayObject>;
    public var _mgr:CommDialogMgr;

    public var _alignOffsetX:Float;
    public var _alignOffsetY:Float;
    public var _fadeInTime:Float;
    public var _fadeOutTime:Float;
    public var _uniqueId:String;

    public function new( mgr:CommDialogMgr){
        super();
        mouseEnabled = true;
        mouseChildren = true;
        visible = true;
#if flash buttonMode = true; #else #end

        _elements = new Array<DisplayObject>();
        _mgr = mgr;
        _fadeOutTime = 0;
        _fadeInTime= 0;

        mgr.addDialog( this);
    }

    public function show ( ):IGenericActuator {
        if (_fadeInTime> 0) {
            return Actuate.tween (this, _fadeInTime, { alpha: 1} ).autoVisible(true);
        } else {
            return Actuate.apply (this, { alpha: 1} ).autoVisible(true);
        }
    }
    public function hide ():IGenericActuator {
        if (_fadeOutTime> 0) {
            return Actuate.tween (this, _fadeOutTime, { alpha: 0} ).autoVisible(false);
        } else {
            return Actuate.apply (this, { alpha: 0} ).autoVisible(false);
        }
    }

    public function showElements():Void{
        if (_elements == null) return;
        for ( i in _elements){
            if ( i.parent == null ) nme.Lib.current.addChild( i);
        }
    }
    public function hideElements():Void{
        if (_elements == null) return;
        for ( i in _elements){
            if ( i.parent != null ) nme.Lib.current.removeChild( i);
        }
    }

    public function clear():Void{
        _mgr = null;
        hideElements();
        if ( parent != null){
            parent.removeChild(this);
        }
        //trace("cleared dialog: " + );
        _elements = null;
    }

    public function showParent():Void{
        _mgr.showListDialog();
    }
    public function hideParent():Void{
        _mgr.hideListDialog();
    }
    public function onMouseClick():Void{ }



}
