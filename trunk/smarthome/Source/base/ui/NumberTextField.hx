package base.ui;


import nme.Assets;
import nme.text.TextField;
import base.data.DataLoader;
import nme.events.KeyboardEvent;

class Number60TextField extends NumberTextField{
    public function new (){
        super();
        addEventListener( KeyboardEvent.KEY_UP, onKeyInput);
    }
    override function onKeyInput( key:KeyboardEvent){
        var val = Std.parseInt( text);
        if (val > 60){
            text = ""+60;
        }
    }
}
class NumberTextField extends EmbedTextField {

    public function new (){
        super();
        addEventListener( KeyboardEvent.KEY_DOWN, onKeyInput);
    }

    function onKeyInput( key:KeyboardEvent){
        if ( key.keyCode >= 48 && key.keyCode <= 57){
            if(text.length == 2){
                key.stopPropagation();
            }
        }else if ( key.keyCode == 8 || key.keyCode == 46){
        }else{
            key.stopPropagation();
        }
    }
}
