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
    void analiza();
    int estado, columna;
    int relacionaCaracteres(char);
    QString tokens(int);
    QString errores(int);
    char aCaracter;
    QString acumulador;
    bool seAgrega(void);
    QList<QString> palabraR;
    bool verificarReservada(QString acumulador);
    int compara;
   bool esReservada;
   QChar palR;


private slots:
    void on_btnAnaliza_clicked();

    void on_action_Abrir_archivo_triggered();

    void on_action_Salir_triggered();


private:
    Ui::MainWindow *ui;
    QString filename;
    QString cadena;
};

#endif // MAINWINDOW_H
