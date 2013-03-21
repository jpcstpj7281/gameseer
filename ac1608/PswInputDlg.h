#ifndef OIDINPUTDLG_H
#define OIDINPUTDLG_H

#include <QWidget>
#include <QDialog>



namespace Ui {
class PswInputDlg;
}



class PswInputDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit PswInputDlg(QWidget *parent = 0);
    ~PswInputDlg();

	bool getNewPsw( int* oldp, int *newp);
	//static PswInputDlg *instance();
private slots:    
 
	void okClick();
	void changeClick();
	void cancelClick();

private:

	bool isChangeMode_;
	bool isPasswordChanged_;
	void closeEvent ( QCloseEvent * event );
	//QString id_, oldPsw_, newOid_;

	int * oldPsw_, * newPsw_;
	//static PswInputDlg * inst;
    Ui::PswInputDlg *ui;


};

#endif // OIDINPUTDLG_H
