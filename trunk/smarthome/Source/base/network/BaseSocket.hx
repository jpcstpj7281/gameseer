package base.network;
import sys.net.Socket;



class BaseSocket extends Socket{

    public function new ( s:Socket = null){
        super();
        if ( s != null){
            __s = s.__s;
            input = s.input;
            output = s.output;
        }
    }
#if sys
    public function writeBytes( bytes:haxe.io.Bytes):Void{ socket_write_bytes( __s, bytes.getData() ); }
    public function readBytes( ):haxe.io.Bytes { 
        try{
            var b = socket_read_bytes( __s ); 
            if(b == null) return null; else return haxe.io.Bytes.ofData(b) ; 
        }catch( e:Dynamic){
            trace(e);
        }
        return null;
    }


#if cpp
    private static var socket_write_bytes= cpp.Lib.load("std", "socket_write", 2);
    private static var socket_read_bytes= cpp.Lib.load("std", "socket_read", 1);
#else 
    private static var socket_write_bytes= neko.Lib.load("std", "socket_write", 2);
    private static var socket_read_bytes= neko.Lib.load("std", "socket_read", 1);
#end
#end
}
