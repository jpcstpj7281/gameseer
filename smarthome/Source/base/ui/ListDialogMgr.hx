package base.ui;

import nme.events.MouseEvent;
import nme.events.KeyboardEvent;
import nme.events.Event;
import base.ui.EmbedTextField;
import nme.display.Sprite;
import base.data.DataLoader;
import com.eclecticdesignstudio.dialog.DialogType;
import com.eclecticdesignstudio.dialog.DialogData;

import haxe.Timer;

class ListDialogMgr extends CommDialogMgr{

    var _downy:Float;
    var _downx:Float;
    var _movey:Float;
    var _movex:Float;

    var _oldx:Float;
    var _oldy:Float;

    var _isDown:Bool;

    var _view:Sprite;

    var _isListening:Bool;

    var _fixedElement:Array<Sprite>;

    public function new (droppoint:Sprite ){

        _view= new Sprite();
        //_view.mouseChildren = false;
        //_view.mouseEnabled= true;
        _view.visible = true;
        droppoint.addChild(_view);
        super( _view );
        _oldx = _view.x;
        _oldy = _view.y;
        _isDown = false;
        _isListening= false;

        _fixedElement = new Array<Sprite>();
    }

    public override function clear():Void{
        hideListDialog();
        if( _view.parent != null){
            _view.parent.removeChild( _view);
        }
        _fixedElement.splice(0, _fixedElement.length);
        super.clear();
    }

    public function onMouseDown(evt:MouseEvent){ 
        //trace( "list onMouseDown");
        for ( i in _fixedElement){
            if( i.hitTestPoint(evt.stageX, evt.stageY) ) return;
        }
        _downx = evt.stageX;
        _downy = evt.stageY;
        _movex= evt.stageX;
        _movey= evt.stageY;
        _isDown = true;
    }
    public function onMouseMove(evt:MouseEvent){ 
        if( (evt.stageX- _downx) > 50 ){
        }else if ( _isDown  ){
            moveListDialog1( 0, evt.stageY - _movey);
            _movey = evt.stageY;
            _movex = evt.stageX;
        }
    }
    
    public function onMouseUp(evt:MouseEvent){ 
        if( _isDown && getInstancesByDisplayOrder().length > 0 && (evt.stageY - _downy) <50 && (evt.stageY - _downy ) > -50 ){
            for ( i in getInstancesByDisplayOrder()){
                if( i.hitTestPoint(_downx, _downy) ) {
                    i.onMouseClick();
                    return;
                }
            }
        }
        else if ( (evt.stageY - _downy) > 50 && (evt.stageY - _downy) >=0){
            _downx = 10000;
            _downy = 10000;
        }
        else if ( (evt.stageY - _downy) < -50 && (evt.stageY - _downy) <=0){
            _downx = 10000;
            _downy = 10000;
        }
        _isDown = false;
    }

    public function showListDialog():Void{
        if ( _isListening == false  ){
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            setAnimationNum( getInstancesByDisplayOrder().length);
            for ( i in 0...getInstancesByDisplayOrder().length){//must use int! for i number
                var d = getInstancesByDisplayOrder()[i];
                d.show().delay(0.05 * i).onComplete(decreaseAnimationNum, []);
                trace("show dialog: "+ d._uniqueId);

#if flash
                //d.x = d.width /2;
                //d.y = d.height/2 + d.height* i;
                d.y = d.height* i;
#else
                //d.x = d.width * d.scaleX /2;
                //d.y= d.height* d.scaleY/2 + d.height*d.scaleY *i;
                d.y=  d.height*d.scaleY *i;
#end

            }
            for ( i in _fixedElement){ if ( i.parent == null ) nme.Lib.current.addChild(i); }
            _isDown = false;
            _isListening = true;
        }
    }

    public function hideListDialog( ):Void{
        if( _isListening == true  ){
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            for ( i in getInstancesByDisplayOrder()){
                i.hide();
            }
            for ( i in _fixedElement){ if(i.parent != null ) nme.Lib.current.removeChild(i); }
            _isDown = false;
            _isListening = false;
        }
    }

    //scroll up and down
    public function moveListDialog1( x:Float, y:Float){
        if ( getInstancesByDisplayOrder().length > 10){
            var updiff:Float = getInstancesByDisplayOrder()[0].y + y + _view.y;
            var downdiff:Float = getInstancesByDisplayOrder()[getInstancesByDisplayOrder().length -1].y +y +_view.y;
            if ( updiff<=0 && downdiff >= (nme.Lib.current.stage.stageHeight - nme.Lib.current.stage.stageHeight / 10) ){
                _view.y += _oldy + y;
            }
        }
    }
    /*
       public function moveListDialog( x:Float, y:Float ):Void{
       if (getInstancesByDisplayOrder().length > 1){
       var updiff:Float = getInstancesByDisplayOrder()[0].y + y;
       var downdiff:Float = getInstancesByDisplayOrder()[getInstancesByDisplayOrder().length -1].y +y;
       if ( updiff <=0 && downdiff >= (nme.Lib.current.stage.stageHeight - nme.Lib.current.stage.stageHeight / 10) ){
       var interval:Float = getInstancesByDisplayOrder()[1].y - getInstancesByDisplayOrder()[0].y;
//var interval:Float  = nme.Lib.current.stage.stageHeight/10;
var h:Float = nme.Lib.current.stage.stageHeight;
for ( i in 0...getInstancesByDisplayOrder().length){
getInstancesByDisplayOrder()[i].y += _oldy + y ;
//trace( interval);
}
}
}
else{
getInstancesByDisplayOrder()[0] = _oldy +y;
}
}
     */
public function createListDialog(name:String, id:Int):CommDialog{
    var dd:DialogData ;
    var s:Sprite = createElement(name, id );
    //dd = createListDialogData(s, name);
    //d = createDialog(dd);
    var d = new ListDialog(this);
    d.addChild(s);
    d.hide();
    return d;
}
static public function getListDialogData( offsetx, offsety, displayObj:Sprite, name:String): DialogData{

    var dd:DialogData = new DialogData(displayObj, name, DialogType.FIXED);
    //dd.alignOffsetY = displayObj.height/2;
    dd.alignOffsetX = offsetx;
    dd.alignOffsetY = offsety;
    dd.fadeInTime = 0.5;
    dd.fadeOutTime = 0 ;
    return dd;

}


public function createListDialogData( displayObj:Sprite, name:String): DialogData{
#if flash
    //dd.alignOffsetY = displayObj.height/2;
    var alignOffsetX = displayObj.width /2;
    var alignOffsetY = displayObj.height/2 + displayObj.height*(getInstancesByDisplayOrder().length);
#else
    var alignOffsetX = displayObj.width * displayObj.scaleX /2;
    //dd.alignOffsetY = displayObj.height* displayObj.scaleY/2;
    var alignOffsetY = displayObj.height* displayObj.scaleY/2 + displayObj.height*displayObj.scaleY *(getInstancesByDisplayOrder().length);
#end
    return getListDialogData( alignOffsetX, alignOffsetY, displayObj, name);
}

}
