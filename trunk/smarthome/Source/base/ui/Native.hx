package base.ui;

import base.ui.EmbedTextField;
import nme.events.KeyboardEvent;

#if neko
import neko.Lib;
#elseif cpp
import cpp.Lib;
#end

#if android
import nme.JNI;
#end


class Native {

    static var rs:String ;


#if android
    public static function initJNI():Void{
        if (jni_get_result == null) {
            jni_get_result = JNI.createStaticMethod ("NativeCall", "getResult", "()Ljava/lang/String;");
            jni_open_input_view=  nme.JNI.createStaticMethod("NativeCall", "openInputView", "()V");
            jni_speech_input=  nme.JNI.createStaticMethod("NativeCall", "openInputSpeech", "()V");
            jni_open_browser =  nme.JNI.createStaticMethod("NativeCall", "openBrowser", "(Ljava/lang/String;)V");
            jni_open_embed_browser =  nme.JNI.createStaticMethod("NativeCall", "openEmbedBrowser", "(Ljava/lang/String;)V");
            jni_open_ui_view=  nme.JNI.createStaticMethod("NativeCall", "openUIView", "()V");
            jni_get_bitmap=  nme.JNI.createStaticMethod("NativeCall", "getBitmap", "()Landroid/graphics/Bitmap;");
            //jni_set_status=  nme.JNI.createStaticMethod("NativeCall", "setStatus", "(Ljava/lang/String)V");
            //jni_show_keyboard= JNI.createStaticMethod ("org.haxe.nme.GameActivity", "showKeyboard", "(Z)V");
        }
    }
#end

    public static function nativeInput():Void{
        rs = null;
#if android
        initJNI();
        //jni_set_status("input");
        trace("nativeInput1");
        nme.Lib.postUICallback( function() { 
                jni_open_input_view();  
                } );
        trace("nativeInput2");

        //jni_show_keyboard(true);
#elseif (cpp ||neko)
        if ( cpp_openInput == null ){ cpp_openInput = Lib.load ("native", "native_openInput", 0); }
        if ( Sys.systemName() != "Linux") {
            rs= new String(cpp_openInput());
        }
#end

    }

    public static function openUIView():Void{
#if android
        initJNI();
        nme.Lib.postUICallback( function() { jni_open_ui_view();} );
        trace("openUIView");
#end
    }

    public static function speechInput():Void{
        rs = null;
#if android
        initJNI();
        //jni_set_status("speech");
        trace("speechInput1");
        nme.Lib.postUICallback( function() { jni_speech_input();  } );
        trace("speechInput2");
#elseif (cpp || neko)
        rs= "";
#end
    }

    public static function openBrowser( address:String):Void{
        rs = null;
#if android
        initJNI();
        //jni_set_status("speech");
        trace("openBrowser");
        nme.Lib.postUICallback( function() { jni_open_browser( address);  } );
        trace("openBrowser");
#elseif (cpp || neko)
        if ( cpp_openBrowser== null ){ cpp_openBrowser= Lib.load ("native", "native_openBrowser", 1); }
        if ( Sys.systemName() != "Linux"){
            rs= cpp_openBrowser( address);
        }
#end
    }

    public static function openEmbedBrowser( address:String):Void{
        rs = null;
#if android
        initJNI();
        //jni_set_status("speech");
        trace("openEmbedBrowser");
        nme.Lib.postUICallback( function() { 
                jni_open_embed_browser( address);  
                } );
        trace("openEmbedBrowser");
#elseif (cpp || neko)
        if ( cpp_openBrowser== null ){ cpp_openBrowser= Lib.load ("native", "native_openBrowser", 1); }
        if ( Sys.systemName() != "Linux"){
            rs= cpp_openBrowser( address);
        }
#end
    }

    public static function getBitmap():Dynamic{
#if android
        return jni_get_bitmap();
#end
        return rs;
    }
    public static function inputData():String{
#if android
        return jni_get_result();
#else
        var res = rs;
        rs = null;
        return res;
#end
    }

#if android
    private static var jni_get_bitmap:Dynamic;
    private static var jni_speech_input:Dynamic;
    private static var jni_open_input_view:Dynamic;
    private static var jni_get_result:Dynamic;
    private static var jni_show_keyboard:Dynamic;
    private static var jni_open_browser:Dynamic;
    private static var jni_open_embed_browser:Dynamic;
    private static var jni_open_ui_view:Dynamic;
#elseif (cpp || neko)

    //private static var cpp_call_printf = Lib.load ("test", "test_call_printf", 1);
    private static var cpp_openInput:Dynamic;
    private static var cpp_openBrowser:Dynamic;
#end


}
