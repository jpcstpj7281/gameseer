#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class InputGainCtrlWnd;
class ChangePasswordWnd;
class CopyParamWnd;
class DevicesWnd;
class GateNOMWnd;
class HighPassWnd;
class Level8CHWnd;
class MatrixMixerWnd;
class MetersWnd;
class PEQ4BandWnd;
class PEQ5BandWnd;
class PresetWnd;


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        private slots:
            void on_inputGainControl_clicked();
        void on_gateNom_clicked();
        void on_highPass_clicked();
        void on_peq4Band_clicked();

    private:
        Ui::MainWindow *ui;

        InputGainCtrlWnd *inputGainCtrlWnd_;
        ChangePasswordWnd *changePasswordWnd_;
        CopyParamWnd *copyParamWnd_;
        DevicesWnd *devicesWnd_;
        GateNOMWnd *gateNOMWnd_;
        HighPassWnd *highPassWnd_;
        Level8CHWnd *level8CHWnd_;
        MatrixMixerWnd *matrixMixerWnd_;
        MetersWnd *metersWnd_;
        PEQ4BandWnd *peq4BandWnd_;
        PEQ5BandWnd *peq5BandWnd_;
        PresetWnd *presetWnd_;

        void closeEvent(QCloseEvent * event);
};

#endif // MAINWINDOW_H
