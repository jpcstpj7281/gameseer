package base.ui;


import nme.text.TextField;
import base.data.DataLoader;
import com.eclecticdesignstudio.dialog.IDialogDisplay;


class EmbedTextField extends TextField {
    public function new (){

        super();
#if cpp
        if( cpp.Sys.systemName() == "Linux" || cpp.Sys.systemName() == "android"  ){
            defaultTextFormat = DataLoader.inst.textFormat_;
            embedFonts = true;
        }
#end

    }

    public function setBorder( flag:Bool):Void{

#if cpp
        if( cpp.Sys.systemName() != "Linux" ){
            border = flag;
        }else{
#if android
        border = flag;
#end
        }
#end
    }

}
