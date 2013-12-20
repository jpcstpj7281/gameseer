#ifndef OIDINPUTDLG_H
#define OIDINPUTDLG_H

#include <QWidget>
#include <QDialog>

#include <Snmpnet.h>

namespace Ui {
class PswInputDlg;
}
class Ac1608Address;


static QString OldPswStr = "@$%J&$:784ASFGPKY(KW%E$Y%#HWTEHU*57uj5U$^UHW$AweZv><GUIKYT*";

class PswInputDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit PswInputDlg(QWidget *parent = 0);
    ~PswInputDlg();

	bool getNewPsw( Ac1608Address*  oldp);
	bool changePsw( Ac1608Address*  oldp);
	//static PswInputDlg *instance();
private slots:    
 
	void okClick();
	void changeClick();
	void cancelClick();

private:
	virtual void	timerEvent ( QTimerEvent * event )override;

	void setPswCallback(SnmpObj* so);
	void getPswCallback(SnmpObj* so);
	void getPsw( Ac1608Address* aa);
	void reset(Ac1608Address* aa );
	void setAllEnabled( bool flag);
	bool isChangeMode_;
	bool isPasswordChanging_;
	bool isLoading_;
	void closeEvent ( QCloseEvent * event );
	
	int * oldPsw_, * newPsw_;
	int pswCount_;
	size_t timeStartChanging_;

	Ac1608Address* currConnAddress_;

    Ui::PswInputDlg *ui;


};

#endif // OIDINPUTDLG_H
