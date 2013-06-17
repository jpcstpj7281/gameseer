#include "ConfigMgr.h"
#include <qdebug.h>


ConfigMgr* ConfigMgr::inst = 0;
ConfigMgr *ConfigMgr::instance(){
	if ( inst) return inst;
	return inst = new ConfigMgr();
}


void ConfigMgr::makeDefault(){
	QDomElement root = doc_->firstChildElement();
	if (root == QDomElement()){
		QDomElement root = doc_->createElement("root");
		doc_->appendChild(root);
	}
}
ConfigMgr::ConfigMgr()
{
	doc_  = new QDomDocument();
	QFile file( "osd.xml" );

	if ( !file.open( QIODevice::ReadOnly  ) || !doc_->setContent( &file) )
	{
		file.close();
		makeDefault();
		return ;
	}
	file.close();
}
ConfigMgr::~ConfigMgr()
{	
	save();
	delete doc_;
}
void ConfigMgr::save(){
	QFile file1( "osd.xml" );
	if ( !file1.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;

	QTextStream out( &file1 );
	doc_->save( out, 4 );
}
