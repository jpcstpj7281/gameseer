/*
 * Copyright (c) 2005-2008, The haXe Project Contributors
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE HAXE PROJECT CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE HAXE PROJECT CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
package chx.io;

import haxe.io.BytesBuffer;
import haxe.io.Bytes;
import chx.lang.OverflowException;
import chx.lang.OutsideBoundsException;

class BytesOutput extends Output {

	#if flash9
	var b : flash.utils.ByteArray;
	#else
	var b : BytesBuffer;
	#end

	public function new() {
		#if flash9
		b = new flash.utils.ByteArray();
		b.endian = flash.utils.Endian.LITTLE_ENDIAN;
		#else
		b = new BytesBuffer();
		#end
	}

	public override function writeByte(c) : Output {
		#if flash9
		b.writeByte(c);
		#else
		b.addByte(c);
		#end
		return this;
	}

	public override function writeBytes( buf : Bytes, pos, len ) : Int {
		#if flash9
		if( pos < 0 || len < 0 || pos + len > buf.length ) throw new OutsideBoundsException();
		b.writeBytes(buf.getData(),pos,len);
		#else
		b.addBytes(buf,pos,len);
		#end
		return len;
	}

	#if flash9
	// optimized operations

	override function setBigEndian(e) {
		bigEndian = e;
		b.endian = e ? flash.utils.Endian.BIG_ENDIAN : flash.utils.Endian.LITTLE_ENDIAN;
		return e;
	}

	public override function writeFloat( f : Float ) : Output {
		b.writeFloat(f);
		return this;
	}

	public override function writeDouble( f : Float ) : Output {
		b.writeDouble(f);
		return this;
	}

	public override function writeInt8( x : Int ) : Output {
		if( x < -0x80 || x >= 0x80 )
			throw new OverflowException();
		b.writeByte(x);
		return this;
	}

	public override function writeInt16( x : Int ) : Output {
		if( x < -0x8000 || x >= 0x8000 ) throw new OverflowException();
		b.writeShort(x);
		return this;
	}

	public override function writeUInt16( x : Int ) : Output {
		if( x < 0 || x >= 0x10000 ) throw new OverflowException();
		b.writeShort(x);
		return this;
	}

	public override function writeInt31( x : Int ) : Output {
		#if !neko
		if( x < -0x40000000 || x >= 0x40000000 ) throw new OverflowException();
		#end
		b.writeInt(x);
		return this;
	}

	public override function writeUInt30( x : Int ) : Output {
		if( x < 0 || x >= 0x40000000 ) throw new OverflowException();
		b.writeInt(x);
		return this;
	}

	public override function writeInt32( x : haxe.Int32 ) : Output {
		b.writeInt(cast x);
		return this;
	}

	public override function prepare( size : Int ) : Output {
		if( size > 0 )
			b[size-1] = b[size-1];
		return this;
	}

	public override function writeString( s : String ) : Output {
		b.writeUTFBytes(s);
		return this;
	}

	#end

	public function getBytes() : Bytes {
		#if flash9
		var bytes = b;
		b = null;
		return untyped new Bytes(bytes.length,bytes);
		#else
		return b.getBytes();
		#end
	}

}
