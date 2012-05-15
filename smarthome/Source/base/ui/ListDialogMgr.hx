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

    var _movableView:Sprite;
    var _view:Sprite;

    var _isListening:Bool;

    public var _movableInstances:Array<CommDialog>;

    public function new (droppoint:Sprite ){

        _view= new Sprite();
        _movableView= new Sprite();

        _movableInstances = new Array<CommDialog>();
        //_movableView.mouseChildren = false;
        //_movableView.mouseEnabled= true;
        _movableView.visible = true;
        droppoint.addChild(_view);
        _view.addChild(_movableView);
        super( _view );
        _oldx = _movableView.x;
        _oldy = _movableView.y;
        _isDown = false;
        _isListening= false;

    }

    public override function contains (id:String):Bool {
        for ( d in _movableInstances){
            if (d._uniqueId == id){
                return true;
            }
        }
        return super.contains( id);
    }
    public override function addDialog(  instance:CommDialog ):Void{
        if ( Std.is( instance, base.ui.FixedDlg)) { 
            //trace("add FixedDlg: "+ instance);
            super.addDialog(instance); return; 
        }
        if ( instance._uniqueId == null){
            instance._uniqueId = Std.string(haxe.Timer.stamp())+ Type.getClassName( Type.getClass(instance));
            //trace("no _uniqueId dialog: " + Type.getClassName( Type.getClass(instance)) + " "+instance._uniqueId );
        }
        if ( contains(instance._uniqueId) ) {
            trace("already add dialog: " + Type.getClassName( Type.getClass(instance)) );
            return;
        }
        trace("add dialog: " + Type.getClassName( Type.getClass(instance)) + " "+instance._uniqueId );

        _movableInstances.push(instance);
        _movableView.addChild (instance);
        instance.hide();
    }
    public override function clear():Void{
        hideListDialog();
        removeAllMovables();
        if( _movableView.parent != null){
            _movableView.parent.removeChild( _movableView);
        }
        _movableInstances.splice(0, _movableInstances.length);
        super.clear();
    }

    public function removeAllMovables():Void{
        for ( d in _movableInstances){
            d.clear();
        }
        _movableInstances = [];
    }

    public function onMouseDown(evt:MouseEvent){ 
        //trace( "list onMouseDown");
        _downx = evt.stageX;
        _downy = evt.stageY;
        for ( i in _instancesByDisplayOrder ){ 
            if( i.hitTestPoint(evt.stageX, evt.stageY) ) {
                return; 
            }
        }
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
        if(  (evt.stageY - _downy) <50 && (evt.stageY - _downy ) > -50 &&  (evt.stageX - _downx) <50 && (evt.stageX - _downx ) > -50 ){
            for ( i in _instancesByDisplayOrder){
                if( i.hitTestPoint(_downx, _downy) ) {
                    i.onMouseClick();
                    _isDown = false;
                    return;
                }
            }
            for ( i in _movableInstances){
                if( i.hitTestPoint(_downx, _downy) ) {
                    i.onMouseClick();
                    _isDown = false;
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

    public override function showListDialog():Void{
        if ( _isListening == false  ){
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.addEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            setAnimationNum( _movableInstances.length);
            for ( i in 0..._movableInstances.length){//must use int! for i number
                var d = _movableInstances[i];
                d.show().delay(0.05 * i).onComplete(decreaseAnimationNum, []);
                //trace("show dialog: "+ d._uniqueId);
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
            _isDown = false;
            _isListening = true;
            //trace("super show: "+ _instancesByDisplayOrder.length);
            super.showListDialog();
        }
    }

    public override function hideListDialog( ):Void{
        if( _isListening == true  ){
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_DOWN, onMouseDown);
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_MOVE, onMouseMove);
            nme.Lib.current.stage.removeEventListener( MouseEvent.MOUSE_UP, onMouseUp);
            for ( i in _movableInstances){ i.hide(); }
            _isDown = false;
            _isListening = false;
            super.hideListDialog();
        }
    }

    //scroll up and down
    public function moveListDialog1( x:Float, y:Float){
        if ( _movableInstances.length > 10){
            var updiff:Float = _movableInstances[0].y + y + _movableView.y;
            var downdiff:Float = _movableInstances[_movableInstances.length -1].y +y +_movableView.y;
            if ( updiff<=0 && downdiff >= (nme.Lib.current.stage.stageHeight - nme.Lib.current.stage.stageHeight / 10) ){
                _movableView.y += _oldy + y;
            }
        }
    }
    /*
       public function moveListDialog( x:Float, y:Float ):Void{
       if (_instancesByDisplayOrder.length > 1){
       var updiff:Float = _instancesByDisplayOrder[0].y + y;
       var downdiff:Float = _instancesByDisplayOrder[_instancesByDisplayOrder.length -1].y +y;
       if ( updiff <=0 && downdiff >= (nme.Lib.current.stage.stageHeight - nme.Lib.current.stage.stageHeight / 10) ){
       var interval:Float = _instancesByDisplayOrder[1].y - _instancesByDisplayOrder[0].y;
//var interval:Float  = nme.Lib.current.stage.stageHeight/10;
var h:Float = nme.Lib.current.stage.stageHeight;
for ( i in 0..._instancesByDisplayOrder.length){
_instancesByDisplayOrder[i].y += _oldy + y ;
//trace( interval);
}
}
}
else{
_instancesByDisplayOrder[0] = _oldy +y;
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
    var alignOffsetY = displayObj.height/2 + displayObj.height*(_movableInstances.length);
#else
    var alignOffsetX = displayObj.width * displayObj.scaleX /2;
    //dd.alignOffsetY = displayObj.height* displayObj.scaleY/2;
    var alignOffsetY = displayObj.height* displayObj.scaleY/2 + displayObj.height*displayObj.scaleY *(_movableInstances.length);
#end
    return getListDialogData( alignOffsetX, alignOffsetY, displayObj, name);
}

}
