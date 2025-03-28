#include "ConfigMgr.h"
#include <qdebug.h>


ConfigMgr* ConfigMgr::inst = 0;
ConfigMgr *ConfigMgr::instance(){
	if ( inst) return inst;
	return inst = new ConfigMgr();
}
QDomDocument* ConfigMgr::getDoc(){ return doc_;}

void ConfigMgr::makeDefault(){

	QFile file( "config.xml" );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;

	delete doc_;
	QDomDocument &doc = *(doc_ = new QDomDocument() );

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
	doc_  = new QDomDocument();
	QFile file( "config.xml" );
	QDomDocument &doc(*doc_);

	if ( !file.open( QIODevice::ReadOnly  ) || !doc_->setContent( &file) )
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
	loadDefaultConfig();
}

void ConfigMgr::loadDefaultConfig(){
	defaultDoc_  = new QDomDocument();
	QFile file( "default.xml" );
	QDomDocument &doc(*defaultDoc_);

	if ( !file.open( QIODevice::ReadOnly  ) || !doc_->setContent( &file) )
	{
		defaultDoc_ = doc_;
		file.close();
		return ;
	}
	file.close();

	QDomElement root = doc.documentElement();
	if ( root.nodeName()!= XML_ROOT){
		defaultDoc_ = doc_;
		return;
	}
}

ConfigMgr::~ConfigMgr()
{	
	save();

	if ( defaultDoc_ != doc_ ) delete defaultDoc_;

	delete doc_;
	
}

void ConfigMgr::save(){
	QFile file1( "config.xml" );
	if ( !file1.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;

	QTextStream out( &file1 );
	doc_->save( out, 4 );
}


QDomElement ConfigMgr::getAddressElem(){
	QDomElement root = doc_->documentElement();
	if ( root.nodeName()!= XML_ROOT){
		return QDomElement();
	}

	QDomElement addresses = root.firstChildElement();
	if ( addresses.nodeName() != XML_ADDRESSES ){
		return QDomElement();
	}

	return addresses;
}

QString getOidFromDoc( QString &id, QDomDocument * doc){
	if ( id.isEmpty() ) return "";
	QDomElement root = doc->documentElement();

	QDomNodeList items = root.elementsByTagName("component");
	QString oid;
	for(int i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomNode n1 = node.attributes().item(1);
		if ( "id" == n1.nodeName()&& id == n1.nodeValue() ){
			oid = node.attributes().item(0).nodeValue();
		}

	}
	return oid;
}

QString ConfigMgr::getOid( QString &id){
	return getOidFromDoc(id, doc_);
}

QString ConfigMgr::getDefaultOid( QString &id){
	return getOidFromDoc(id, defaultDoc_);
}

void ConfigMgr::setOid( QString &id, QString &oid){
	QDomElement root = doc_->documentElement();

	

	QDomNodeList items = root.elementsByTagName("component");
	bool found = false;
	for(int i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomElement elem = node.toElement();
		if ( elem.attribute("id") == id ){
			elem.setAttribute("id", id);
			elem.setAttribute("oid", oid);
			found = true;
			break;
		}
	}
	if ( found == false){
		QDomNodeList items = root.elementsByTagName("components");
		QDomNode node = items.at(0);
		QDomElement elm = doc_->createElement( "component");
		elm.setAttribute ("id", id);
		elm.setAttribute( "oid", oid);
		node.insertAfter( elm, QDomElement());

	}

}

