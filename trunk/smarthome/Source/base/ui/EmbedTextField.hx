package base.ui;


import nme.text.TextField;
import base.data.DataLoader;
import com.eclecticdesignstudio.dialog.IDialogDisplay;


class EmbedTextField extends TextField {
    public function new (){

        super();
#if android
        if( cpp.Sys.systemName() == "Linux" || cpp.Sys.systemName() == "android"  ){
            if ( DataLoader.inst.textFormat_ != null){
                defaultTextFormat = DataLoader.inst.textFormat_;
                embedFonts = true;
            }
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
