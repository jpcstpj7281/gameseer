#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "inputGainCtrlWnd.h"
#include "ChangePasswordWnd.h"
#include "CopyParamWnd.h"
#include "DevicesWnd.h"
#include "GateNOMWnd.h"
#include "HighPassWnd.h"
#include "Level8CHWnd.h"
#include "MatrixMixerWnd.h"
#include "MetersWnd.h"
#include "PEQ4BandWnd.h"
#include "PEQ5BandWnd.h"
#include "PresetWnd.h"
#include <QAction.h>
#include <QLineEdit.h>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,inputGainCtrlWnd_(new InputGainCtrlWnd)
    ,gateNOMWnd_(new GateNOMWnd)
    ,highPassWnd_(new HighPassWnd)
    ,peq4BandWnd_(new PEQ4BandWnd)
    ,changePasswordWnd_(new ChangePasswordWnd)
{
    ui->setupUi(this);
    connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionChangePsw_clicked(QAction*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete inputGainCtrlWnd_;
    delete gateNOMWnd_;
    delete highPassWnd_;
    delete peq4BandWnd_;
    delete changePasswordWnd_;
}

void MainWindow::on_inputGainControl_clicked()
{
    if ( inputGainCtrlWnd_->isVisible()){
        inputGainCtrlWnd_->hide();
    }else{
        inputGainCtrlWnd_->show();
    }
}

void MainWindow::on_highPass_clicked(){
    if ( highPassWnd_->isVisible()){
        highPassWnd_->hide();
    }else{
        highPassWnd_->show();
    }

}


void MainWindow::on_gateNom_clicked()
{

    if ( gateNOMWnd_->isVisible()){
        gateNOMWnd_->hide();
    }else{
        gateNOMWnd_->show();
    }
}

void MainWindow::on_peq4Band_clicked()
{
    if ( peq4BandWnd_->isVisible()){
        peq4BandWnd_->hide();
    }else{
        peq4BandWnd_->show();
    }

}

void MainWindow::on_actionChangePsw_clicked( QAction* action){
    if (action->objectName() != "actionChangePsw" ) return;


    if ( changePasswordWnd_->isVisible()){
        changePasswordWnd_->raise();
    }else{
        changePasswordWnd_->show();
    }
}

void MainWindow::closeEvent(QCloseEvent * ){
    QCoreApplication::exit();
}
