#include "snmpnetwnd.h"
#include "ui_snmpnetwnd.h"

#include <QTableWidgetItem>
#include <QTableWidget>

#include "configmgr.h"

#include <functional>
#include <qdebug>
#include <QTime>
#undef min
 

using namespace std::placeholders;



SnmpNetWnd::SnmpNetWnd(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::SnmpNetWnd)
{
	ui->setupUi(this);

	tableOids_ = findChild<QTableWidget* >("tableOids");
	tableOids_->setColumnCount(7);

	QStringList sl;
	sl.push_back( "Object");
	sl.push_back( "Response");
	sl.push_back( "Oid");
	sl.push_back( "IP");
	sl.push_back( "Community");
	sl.push_back( "unique");
	sl.push_back( "interval");



	//sl.push_back( "Connection");
	//sl.push_back( "Operation");
	tableOids_->setHorizontalHeaderLabels(sl );

	SnmpNet::instance()->listenOidBeforeSent( std::bind< std::function< void (SnmpObj*) > > (&SnmpNetWnd::beforeSent, this, _1) );
	SnmpNet::instance()->listenOidAfterResponsed( std::bind< std::function< void (SnmpObj*) > > (&SnmpNetWnd::afterResponsed, this, _1) );
	SnmpNet::instance()->listenOidBeforeRemoved( std::bind< std::function< void (SnmpObj*) > > (&SnmpNetWnd::beforeRemoved, this, _1) );
	startTimer(1000);
}

SnmpNetWnd::~SnmpNetWnd(){
	delete ui;
}

void SnmpNetWnd::beforeRemoved(SnmpObj* so){
	if (so->ip.empty() ) return;

	QString unique;// = QString::number( (int) so);
	unique.append(so->obj.c_str()).append( so->snmpoid.c_str()).append( so->ip.c_str()).append(so->community.c_str());

	QMutexLocker lk(&locker_);
	std::map<QString, ObservedOid >::iterator found = oidMap_.find( unique);
	if (found != oidMap_.end()){
		found->second.isRemoved = true;
	}else{
		qDebug()<<"Unexpected error: void SnmpNetWnd::afterResponsed!";
	}
}
void SnmpNetWnd::afterResponsed(SnmpObj* so){
	if (so->ip.empty() ) return;

	QString unique;// = QString::number( (int) so);
	unique.append(so->obj.c_str()).append( so->snmpoid.c_str()).append( so->ip.c_str()).append(so->community.c_str());

	const int len = 128;
	char buf[len];
	memset( buf, 0, len);
	snprint_variable( buf, len, so->pdu->variables->name, so->pdu->variables->name_length, so->pdu->variables);
	QMutexLocker lk(&locker_);
	std::map<QString, ObservedOid >::iterator found = oidMap_.find( unique);
	if (found != oidMap_.end()){
		if (found->second.timersp == 0){
			found->second.timersp = GetTickCount();
		}
		found->second.rsp  = buf;
	}else{
		//ObservedOid oid ;
		//oid.obj = so->obj.c_str();
		//oid.ip = so->ip.c_str();
		//oid.oid = so->snmpoid.c_str();
		//oid.community = so->community.c_str();
		//oid.rsp  = buf;
		//oidMap_[unique] = oid;
		qDebug()<<"Unexpected error: void SnmpNetWnd::afterResponsed!";
	}

}
void SnmpNetWnd::beforeSent(SnmpObj* so){
	if (so->ip.empty() ) return;
	
	QString unique;// = QString::number( (int) so);
	unique.append(so->obj.c_str()).append( so->snmpoid.c_str()).append( so->ip.c_str()).append(so->community.c_str());
	//qDebug() << list.size();

	QMutexLocker lk(&locker_);
	std::map<QString, ObservedOid >::iterator found = oidMap_.find( unique);
	if (found == oidMap_.end()){
		ObservedOid oid ;
		oid.timersp = 0;
		oid.isRemoved = false;
		oid.timereq = GetTickCount();
		oid.obj = so->obj.c_str();
		oid.ip = so->ip.c_str();
		oid.oid = so->snmpoid.c_str();
		oid.community = so->community.c_str();
		oidMap_[unique] = oid;
	}
	else{
		if (found->second.isRemoved){
			found->second.isRemoved = false;
		}
		size_t tick = GetTickCount();
		if ( found->second.timersp > 0 && tick - found->second.timersp > 1000){
			found->second.timereq = tick;
			found->second.timersp = 0;
		}
		
	}
}

void SnmpNetWnd::timerEvent ( QTimerEvent * event ){
	std::map<QString, ObservedOid > oidMap;
	{
		QMutexLocker lk(&locker_);
		oidMap = oidMap_;
		//oidMap_.clear();
	}
	for ( std::map<QString, ObservedOid >::iterator it = oidMap.begin(); it != oidMap.end(); ++it){
		QList<QTableWidgetItem *> list = tableOids_->findItems( it->first, Qt::MatchFlag::MatchExactly );
		if ( list.isEmpty()  ){
			int newCount = tableOids_->rowCount() +1;
			tableOids_->setRowCount( newCount );
			QTableWidgetItem * obj = new QTableWidgetItem;
			QTableWidgetItem * oid = new QTableWidgetItem;
			QTableWidgetItem * uniq = new QTableWidgetItem;
			QTableWidgetItem * ip = new QTableWidgetItem;
			QTableWidgetItem * rsp = new QTableWidgetItem;
			QTableWidgetItem * community = new QTableWidgetItem;
			QTableWidgetItem * interval = new QTableWidgetItem;
			obj->setText( it->second.obj );
			oid->setText( it->second.oid );
			uniq->setText(it->first);
			uniq->setToolTip(it->first);
			ip->setText( it->second.ip );
			oid->setToolTip(it->second.oid );
			community->setText(it->second.community);
			if ( it->second.timersp > 0){
				interval->setText( QString::number( it->second.timersp - it->second.timereq) );
			}
			community->setFlags( Qt::ItemIsEnabled );
			oid->setFlags( Qt::ItemIsEnabled );
			uniq->setFlags( Qt::ItemIsEnabled );
			ip->setFlags( Qt::ItemIsEnabled );
			rsp->setFlags( Qt::ItemIsEnabled );
			obj->setFlags( Qt::ItemIsEnabled );
			interval->setFlags( Qt::ItemIsEnabled );
			tableOids_->setItem( newCount -1, 0, obj);
			tableOids_->setItem( newCount -1, 1, rsp);
			tableOids_->setItem( newCount -1, 2, oid);
			tableOids_->setItem( newCount -1, 3, ip);
			tableOids_->setItem( newCount -1, 4, community);
			tableOids_->setItem( newCount -1, 5, uniq);
			tableOids_->setItem( newCount -1, 6, interval);
			if (it->second.community == "private"){
				for ( size_t i = 0; i < tableOids_->columnCount(); ++i){
					QTableWidgetItem * tmp = tableOids_->item( newCount -1, i);
					tmp->setBackground(QBrush(QColor(Qt::lightGray))); 
				}
			}
		}else if( list.size() == 1 ){
			QTableWidgetItem * item = list.front();
			if ( it->second.isRemoved){
				for ( size_t i = 0; i < tableOids_->columnCount(); ++i){
					QTableWidgetItem * tmp = tableOids_->item( item->row(), i);
					tmp->setBackground(QBrush(QColor(Qt::red))); 
				}
			}else{
				if (it->second.community == "private"){
					for ( size_t i = 0; i < tableOids_->columnCount(); ++i){
						QTableWidgetItem * tmp = tableOids_->item(item->row(), i);
						tmp->setBackground(QBrush(QColor(Qt::lightGray))); 
					}
				}else{
					for ( size_t i = 0; i < tableOids_->columnCount(); ++i){
						QTableWidgetItem * tmp = tableOids_->item( item->row(), i);
						tmp->setBackground(QBrush(QColor(Qt::white))); 
					}
				}
			}
			QTableWidgetItem * interval = tableOids_->item( item->row(), 6);
			QTableWidgetItem * rsp = tableOids_->item( item->row(), 1);
			rsp->setText( it->second.rsp);
			if ( it->second.timersp > 0){
				interval->setText( QString::number( it->second.timersp - it->second.timereq) );
			}
		}else{
			qDebug()<<"unexpected error: SnmpNetWnd::timerEvent!";
		}
	}
	oidMap.clear();
}