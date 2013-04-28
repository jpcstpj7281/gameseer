#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DevicesWnd;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

		
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:

        Ui::MainWindow *ui;

        DevicesWnd *devicesWnd_;
		//std::vector< QWidget*> modules_;

        void closeEvent(QCloseEvent * event);
		void resizeEvent(QResizeEvent * event);

};

#endif // MAINWINDOW_H
