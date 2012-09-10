
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
import haxe.io.BytesBuffer;


class Connection{
#if sys
    public var _socket:BaseSocket;
#else
    public var _socket:Socket;
#end
    public var _isFailed:Bool;
    public var _ipv4:String;
    public var _port:Int;
    public function new( ipv4:String, port:Int){
#if sys
        _socket = new BaseSocket();
#else
        _socket = new Socket();
#end
        _ipv4 = ipv4;
        _port = port;
        _isFailed = true;
    }

    inline public function connect(){
        _isFailed = false;

#if flash
        //_socket.endian = flash.utils.Endian.LITTLE_ENDIAN;
        _socket.connect(_ipv4, _port) ;
        _socket.addEventListener( SecurityErrorEvent.SECURITY_ERROR, connectFailed);
#else
        try{
            //_socket.setBlocking( false);
            //最小可以分辨毫秒
            _socket.setTimeout( 0.001);
            _socket.connect(new Host(_ipv4), _port) ;
        }catch( e:Dynamic){
            _isFailed = true;
        }
#end

    }

#if flash
    inline private function connectFailed( e:SecurityErrorEvent){
        _isFailed = true;
    }
#end

    inline public function read( ):Bytes{
#if flash
        var ba:ByteArray = new ByteArray();
        _socket.readBytes(ba);
        var b:Bytes = Bytes.ofData(ba);
        return b;
#elseif (cpp||neko)

        //时间最小是微秒，timeout以秒为单位
        var arr = Socket.select([_socket], [], [], 0.000001 );
        if (arr.read.length > 0 ) { return _socket.readBytes();}
        else return null;
#else
        var arr = Socket.select([_socket], [], [], 0.000001 );
        if (arr.read.length > 0 ) { return Bytes.ofString(_socket.read());}
        else return null;
#end

    }
    inline public function write( data:Bytes):Void{
        if ( isConected()) {
#if flash
            var ba = data.getData();
            _socket.writeBytes( ba, 0, ba.length );
            _socket.flush();
#elseif sys
            _socket.writeBytes( data);
#else
            _socket.write( data.toString() );
#end
        }
    }

    public function isConected():Bool{
#if flash
        return _socket.connected;
#else
        return !_isFailed;
#end
    }

    inline public function close():Void{
        _socket.close();
#if sys
        _socket = new BaseSocket();
#else
        _socket = new Socket();
#end
        _isFailed = true;
    }
    public function sendData():Bool{

        return false;
    }
}

