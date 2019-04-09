#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAnaliza_clicked()
{
    QMessageBox::about(this,
                      "Soy un mensaje",
                      tr("Mensajito"));

}

void MainWindow::on_action_Abrir_archivo_triggered()
{
    filename = QFileDialog::getOpenFileName(
                this,
                "Prueba2 - Abrir archivo",
                "C:/Users/cinth/Documents/Tecnológico/Sexto Semestre/Lenguajes y autómatas/AL/wALson",
                "Text Files (*.eye)");
    if (!filename.isEmpty()){
        QFile file(filename);
        if (file.open(QFile::ReadOnly)){
            ui->AreaArchivo->setPlainText(file.readAll());
        }else {
            QMessageBox::warning(this,
                                 "Advertencia",
                                 tr("No se puede leer el archivo"));
      }
    }
}

void MainWindow::on_action_Salir_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                         "Mensaje",
                         tr("¿Seguro que desea salir?"),
                          QMessageBox::Yes | QMessageBox::No);
    if(reply== QMessageBox::Yes){
        QApplication::quit();
    }
}
