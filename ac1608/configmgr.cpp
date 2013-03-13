#include "ConfigMgr.h"
#include <qdebug.h>


ConfigMgr* ConfigMgr::inst = 0;
ConfigMgr *ConfigMgr::instance(){
	if ( inst) return inst;
	return inst = new ConfigMgr();
}

void ConfigMgr::makeDefault(){

	QFile file( "ac1608.xml" );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;

	delete _doc;
	QDomDocument &doc = *(_doc = new QDomDocument() );

	QDomProcessingInstruction instruction;
	instruction = doc.createProcessingInstruction( "xml", "version = \'1.0\'" );
	doc.appendChild( instruction );

	QDomElement root = doc.createElement( XML_ROOT );
	doc.appendChild( root );
	QDomElement addresses = doc.createElement( XML_ADDRESSES );
	root.appendChild( addresses );

	QDomElement address = doc.createElement( XML_ADDRESS );
	addresses.appendChild( address );
	address.setAttribute( "location", "home");
	address.setAttribute( "ip", "192.168.1.100");

	QDomElement devices = doc.createElement( XML_DEVICES );
	root.appendChild( devices );
	QDomElement device = doc.createElement( XML_DEVICE );
	devices.appendChild( device );
	device.setAttribute( "title", "password");
	device.setAttribute( "ip", "192.168.1.100");

	QTextStream out( &file );
	doc.save( out, 4 );

	file.close();
}

ConfigMgr::ConfigMgr():isOidEditable_(false)
{
	_doc  = new QDomDocument();
	QFile file( "ac1608.xml" );
	QDomDocument &doc(*_doc);

	if ( !file.open( QIODevice::ReadOnly  ) || !_doc->setContent( &file) )
	{
		file.close();
		makeDefault();
		return ;
	}
	file.close();

	QDomElement root = doc.documentElement();
	if ( root.nodeName()!= XML_ROOT){
		this->makeDefault();
		return;
	}

	QDomElement addresses = root.firstChildElement();
	if ( addresses.nodeName() != XML_ADDRESSES ){
		addresses = doc.createElement( XML_ADDRESSES );
		root.insertBefore(addresses, root.firstChildElement() );
	}

	//QDomElement address1 = doc.createElement( XML_ADDRESS );
	//addresses.appendChild( address1 );
	//address1.setAttribute( "location", "home");
	//address1.setAttribute( "ip", "192.168.1.101");

	//QDomElement address = addresses.firstChildElement();
	//qDebug()<<address.nodeName();


}
ConfigMgr::~ConfigMgr()
{	
	QFile file1( "ac1608.xml" );
	if ( !file1.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;

	QTextStream out( &file1 );
	_doc->save( out, 4 );
}


QDomElement ConfigMgr::getAddressElem(){
	QDomElement root = _doc->documentElement();
	if ( root.nodeName()!= XML_ROOT){
		return QDomElement();
	}

	QDomElement addresses = root.firstChildElement();
	if ( addresses.nodeName() != XML_ADDRESSES ){
		return QDomElement();
	}

	return addresses;
}