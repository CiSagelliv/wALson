#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAnaliza_clicked();

    void on_action_Abrir_archivo_triggered();

    void on_action_Salir_triggered();

private:
    Ui::MainWindow *ui;
    QString filename;
};

#endif // MAINWINDOW_H