
package base.network;

#if neko
import neko.net.Socket;
import neko.net.Host;
#elseif cpp
import cpp.net.Socket;
import cpp.net.Host;
#elseif flash
import nme.events.SecurityErrorEvent;
import flash.net.Socket;
import flash.utils.ByteArray;
import flash.system.Security;
#end
import haxe.io.Bytes;


class Acceptor{
    public var _socket:Socket;
    public var _isFailed:Bool;
    //public var _ipv4:String;
    public var _port:Int;
    public function new( port:Int){
        _socket = new Socket();
        //_ipv4 = ipv4;
        _port = port;
        _socket.bind(new Host("0.0.0.0"), _port) ;
        _socket.listen(8);
    }

    public function accept():Socket{
        var arr = Socket.select([_socket], [], [], 0.01 );
        if (arr.read.length > 0 ){
            return _socket.accept();
        }
        return null;
    }
}
