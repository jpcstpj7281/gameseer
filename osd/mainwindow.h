#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DevicesWnd;
//class SnmpNetWnd;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

		
    public:

		enum Mode{
			ControlMode,
			EditMode,
		};

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

		void setMode( Mode mode){
			_mode = mode;
		}
		Mode getMode(){
			return _mode ;
		}

		
    private slots:
        void on_inputGainControl_clicked();
        void on_gateNom_clicked();
        void on_highPass_clicked();
        void on_actionChangePsw_clicked(QAction*);
        void on_actionCopyParam_clicked(QAction*);
		void on_actionEdit_clicked(QAction*);

		void tabChanged (int);

    private:

		QTabWidget* _tab;
		Mode _mode;

        Ui::MainWindow *ui;

        DevicesWnd *devicesWnd_;
		//SnmpNetWnd * snmpNetWnd_;

        void closeEvent(QCloseEvent * event);
		void resizeEvent(QResizeEvent * event);

};

#endif // MAINWINDOW_H
