#ifndef CONFIGMGR_H
#define CONFIGMGR_H
#include <QDomDocument>
#include <QFile>
#include <QTextStream>


#define XML_ROOT "root"
#define XML_ADDRESSES "addresses"
#define XML_ADDRESS "address"
#define XML_DEVICES "devices"
#define XML_DEVICE	"device"

class ConfigMgr{
	static ConfigMgr* inst;
	ConfigMgr();

	QDomDocument *doc_;
	QFile *_file;

	
	void loadDefaultConfig();
public :


	~ConfigMgr();

	static ConfigMgr *instance();

	inline QDomDocument* getDoc(){ return doc_;}
	void save();
	void makeDefault();
};
#endif // CONFIGMGR_H