package base.common;

import flash.utils.ByteArray;
import flash.utils.Endian;



import haxe.io.Bytes;
import haxe.io.BytesOutput;
import nme.display.BitmapData;
import nme.display.Bitmap;

import format.tools.Image;
import format.png.Tools;
import format.png.Writer;
import format.png.Reader;
#if sys
import sys.io.File;
#end

/**
 * ...
 * @author Wills
 */


class Base64 {
    private static var chars:String = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    public static function encode(input:String) :String{
#if neko
        return haxe.BaseCode.encode( input, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
#else
        var output:String = "",chr1:Null<Int>,chr2:Null<Int>,chr3:Null<Int>,enc1:Int,enc2:Int,enc3:Int,enc4:Int,i:Int = 0;
        while (i < input.length) {
            chr1 = input.charCodeAt(i++);
            chr2 = input.charCodeAt(i++);
            chr3 = input.charCodeAt(i++);
            enc1 = chr1 >> 2;
            enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
            enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
            enc4 = chr3 & 63;
            if (chr2 == null) {
                enc3 = enc4 = 64;
            }
            else if (chr3 == null) {
                enc4 = 64;
            }
            output = output + chars.charAt(enc1) + chars.charAt(enc2) + chars.charAt(enc3) + chars.charAt(enc4);
        }
        return output;
#end
    }

    /*
    public static function decode(input:String) {
        var output:String = "";
        var chr1:Int,chr2:Int,chr3:Int,enc1:Int,enc2:Int,enc3:Int,enc4:Int,i:Int = 0;
        var r:EReg= ~/[^A-Za-z0-9\+\/=]/g;
        input = r.replace(input, "");
        while (i < input.length) {
            enc1 = chars.indexOf(input.charAt(i++));
            enc2 = chars.indexOf(input.charAt(i++));
            enc3 = chars.indexOf(input.charAt(i++));
            enc4 = chars.indexOf(input.charAt(i++));
            chr1 = (enc1 << 2) | (enc2 >> 4);
            chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
            chr3 = ((enc3 & 3) << 6) | enc4;
            output = output + String.fromCharCode(chr1);
            if (enc3 != 64) output = output + String.fromCharCode(chr2);
            if (enc4 != 64) output = output + String.fromCharCode(chr3);
        }
#if cpp
        output = haxe.Utf8.decode(output);
#end
        return output;
    }
    */
}

class Tools 
{

    public inline static var MAX_INT = 1 << 28;
    public inline static var OutOfWorld = MAX_INT;

    function new() 
    {
    }

    public static function uniqueStr():String {
        var v0:Int = Std.random( MAX_INT);
        var v1:Int = Std.random( MAX_INT);

        var str:String = Std.string( v0) + Std.string( v1) + Std.string( v0) + Std.string( v1);
        return str.substr( 0, 32);
    }


    inline public static function base64_HMAC_SHA1(  insecret:String, inmessage:String ):String {
        return hash_Base64( hash_HMAC_SHA1 (insecret, inmessage) );
    }
    inline public static function hash_Base64( instr:String):String {
#if php
        var code = base64_encode ( instr );
#else
        var code = Base64.encode( instr);
#end
        return code;
    }

    inline public static function hash_HMAC_SHA1( insecret:String, inmessage:String):String {
#if php
        var code = hash_hmac ( "sha1" , inmessage , insecret );
#elseif neko
        var hmac = new chx.hash.HMAC( null);
        var bcode = hmac.calculate( Bytes.ofString(insecret), Bytes.ofString(inmessage));
        var code ="";
        for ( b in 0...bcode.length){
            code+= String.fromCharCode(bcode.get(b));
        }
#else
        //var code = HMAC.hash(insecret, inmessage);		
        var sha1 = new chx.hash.Sha1();
        var hmac = new chx.hash.HMAC( sha1);
        var bcode = hmac.calculate( Bytes.ofString(insecret), Bytes.ofString(inmessage));
        var code ="";
        for ( b in 0...bcode.length){
            code+= String.fromCharCode(bcode.get(b));
        }
#end
        return code;
    }
    //
    //inline public static function salt_SHA1( data:Bytes):Bytes{ 
    //#if neko
    //trace("unsupport neko algorithm");
    //return Bytes.ofString("");
    //#else
    //return chx.hash.Sha1.encode( data); 
    //#end
    //}
    //inline public static function base64_salt_SHA1( data:String):String{ 
    //#if neko
    //trace("unsupport neko algorithm");
    //return ("");
    //#else
    //var b = Bytes.ofString(data);
    //var s = chx.hash.Sha1.encode( b);
    //
    //trace( s.toHex());
    //
    //var code ="";
    //for ( b in 0...s.length){
    //code+= String.fromCharCode(s.get(b));
    //}
    //var base64 = Base64.encode(code); 
    //return base64;
    //#end
    //}

    inline public static function sortString (a : String, b : String) : Int {
        return if ( a < b ) -1 else if ( a > b ) 1 else 0;
    }   

    inline public static function assert (cond : Bool, ?pos : haxe.PosInfos) : Void {
#if debug
        if( !cond )
            haxe.Log.trace("Assert in " + pos.className + "::" + pos.methodName, pos);
#end
    }   

    public static function converToPNGBytes( bmd:BitmapData, w:Int = 0, h:Int = 0):Bytes{
#if js  return null; 
#else
        if ( w == 0) w = bmd.width;
        if ( h == 0) h = bmd.height;
        var rect = new nme.geom.Rectangle( 0, 0, w, h);

#if sys
        var argb:Bytes = bmd.getPixels( rect);
#elseif flash
        var argb:Bytes = Bytes.ofData(bmd.getPixels( rect));
#end

        var d = format.png.Tools.build32BE( w, h, argb);
        var bo:BytesOutput = new BytesOutput();
        var w:Writer = new Writer( bo );
        w.write(d);
        var strpng:Bytes = bo.getBytes();

        return strpng;
#end
    }
    public static function converToJPEGBytes( bmd:BitmapData, w:Int = 0, h:Int = 0):Bytes{
#if js
        return null;
#else
        if ( w == 0) w = bmd.width;
        if ( h == 0) h = bmd.height;
        var rect = new nme.geom.Rectangle( 0, 0, w, h);
#if sys
        var argb:Bytes = bmd.getPixels( rect);
#elseif flash
        var argb:Bytes = Bytes.ofData(bmd.getPixels( rect));
#end
        //var d = format.jpg.Tools.build32BE( 100, 100, argb);
        //var d = new format.jpg.Data();
        //d.width = bmd.width;
        //d.height= bmd.height;
        //d.quality = 1;
        //d.pixels = argb;
        var bo:BytesOutput = new BytesOutput();
        var wt:format.jpg.Writer = new format.jpg.Writer( bo );
        wt.write({width:w, height:h, quality:1.0, pixels:argb});
        var strpng:Bytes = bo.getBytes();

        return strpng;
#end
    }
}
