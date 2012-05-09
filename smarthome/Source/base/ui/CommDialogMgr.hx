package base.ui;
import com.eclecticdesignstudio.dialog.DialogType;
import com.eclecticdesignstudio.dialog.DialogData;

import nme.display.DisplayObject;
import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;

class CommDialogMgr  {

    var _animatingNum:Int;
    var _instancesByDisplayOrder:Array <CommDialog>;
    private var _dropPoint:Sprite;

    public function new ( dropPoint:Sprite){
        _animatingNum = 0;
        _dropPoint = dropPoint;
        _instancesByDisplayOrder = [];
    }

    public function contains (id:String):Bool {
        for ( d in _instancesByDisplayOrder){
            if (d._uniqueId == id){
                return true;
            }
        }
        return false;
    }

    public function remove (instance:CommDialog):Void {
        for ( d in _instancesByDisplayOrder){
            if (d._uniqueId == instance._uniqueId){
                _instancesByDisplayOrder.remove(instance);
                break;
            }
        }
    }

    public function showListDialog():Void{
        for ( i in _instancesByDisplayOrder){ i.show(); trace("show: " + i);}
    }
    public function hideListDialog( ):Void{
        for ( i in _instancesByDisplayOrder){ i.hide(); }
    }

    public function removeAll():Void{
        for ( d in _instancesByDisplayOrder){
            d.clear();
        }
        _instancesByDisplayOrder = [];
    }

    public function decreaseAnimationNum():Void{
        --_animatingNum;
    }
    public function setAnimationNum( num:Int):Void{
        _animatingNum = num;
    }
    public function isAnimating():Bool{
        return _animatingNum >0;
    }

    public function clear():Void{
        for ( i in _instancesByDisplayOrder ){
            trace("clearing dialog: "+ Type.getClassName( Type.getClass(i) ) );
            i.clear();
            trace("cleared dialog: "+ Type.getClassName( Type.getClass(i) ) );
        }
        _instancesByDisplayOrder=[];
    }

    public function getSpecificDialog( name:String, id:Int):CommDialog{
        var n = name + id;
        for ( d in _instancesByDisplayOrder){
            if ( d._uniqueId == n){
                return d;
            }
        }
        return null;
    }

    public function addDialog(  instance:CommDialog ):Void{
        if ( instance._uniqueId == null){
            instance._uniqueId = Std.string(haxe.Timer.stamp())+ Type.getClassName( Type.getClass(instance));
            trace("no _uniqueId dialog: " + Type.getClassName( Type.getClass(instance)) + " "+instance._uniqueId );
        }
        if ( contains(instance._uniqueId) ) {
            trace("already add dialog: " + Type.getClassName( Type.getClass(instance)) );
            return;
        }
        trace("add Fixed dialog: " + Type.getClassName( Type.getClass(instance)) + " "+instance._uniqueId );
        _instancesByDisplayOrder.push(instance);
        //trace(_instancesByDisplayOrder.length);
        _dropPoint.addChild (instance);
        instance.hide();
    }

    static public function getElement( name:String, id:Int):Sprite{
        var txt:EmbedTextField = new EmbedTextField();
        txt.text = name;
        txt.scaleX = 3;
        txt.scaleY = 3;
        txt.x = 220;
        txt.width = nme.Lib.current.stage.stageWidth/txt.scaleX - 220/txt.scaleX;
        txt.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;
        txt.setBorder(true);
        txt.selectable = false;

        var txt1:EmbedTextField = new EmbedTextField();
        txt1.text = Std.string(id);
        txt1.scaleX = 1;
        txt1.scaleY = 3;
        txt1.width = 100;
        txt1.setBorder(true);
        txt1.x = 120;
        txt1.height = nme.Lib.current.stage.stageHeight/10/txt1.scaleY;
        txt1.selectable = false;

        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("cmd") );
        //bm.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;

        var s:Sprite = new Sprite();
        s.addChild( bm);
        s.addChild( txt1);
        s.addChild( txt);
        //var w:Float = nme.Lib.current.stage.stageWidth / txt.width;
        //s.width=  nme.Lib.current.stage.stageWidth;
        s.height = nme.Lib.current.stage.stageHeight/10;
        //txt.scaleY = 2;
        return s;
    }

    public function createElement(name:String, id:Int):Sprite{
        return getElement(name, id);
    }
}
