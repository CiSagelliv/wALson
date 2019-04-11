#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>

static int matriz[22][30]= {
    {2,1,4,500,125,2,1,107,108,0,0,0,10,12,109,13,16,17,18,19,21,20,123,124,126,127,128,129,111,509},
    {2,1,2,3,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
    {2,2,2,3,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
    {2,2,2,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501},
    {102,102,4,102,5,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102},
    {502,502,6,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502,502},
    {103,103,6,103,103,7,7,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103},
    {503,503,9,503,503,503,503,8,8,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503},
    {504,504,9,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504},
    {104,104,9,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
    {11,11,11,11,11,11,11,11,11,11,11,11,505,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
    {506,506,506,506,506,506,506,506,506,506,506,506,105,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506,506},
    {12,12,12,12,12,12,12,12,12,12,12,12,12,106,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12},
    {110,110,110,110,110,110,110,110,110,110,110,110,110,110,14,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110},
    {14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14},
    {14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,112,14,14,14,14,14,14,14,14,14,14,14,14,14,14},
    {507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,507,113,507,507,507,507,507,507,507,507,507,507,507,507,507},
    {508,508,508,508,508,508,508,508,508,508,508,508,508,508,508,508,508,114,508,508,508,508,508,508,508,508,508,508,508,508},
    {115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,116,115,115,115,115,115,115,115,115,115,115},
    {122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,117,122,122,122,122,122,122,122,122,122,122},
    {118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,119,118,118,118,118,118,118,118,118,118,118},
    {120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,121,120,120,120,120,120,120,120,120,120,120}
    };



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    estado = 0;
    columna = 0;
    compara = 0;   
    palabraR = {"class","begin","end","def","as" ,"integer","float", "char", "string", "boolean", "if", "else", "elseif","endif", "for", "do ", "endfor", "while", "endwhile", "function", "endfunction","import", "null", "read", "write", "enter", "principal"};
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAnaliza_clicked()
{
    analiza();
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
            cadena = file.readAll()+ " ";
            ui->AreaArchivo->setPlainText(cadena);
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

void MainWindow::analiza(){
    for(int i=0;i<cadena.length();i++){
            aCaracter = cadena[i].toLatin1();
            columna = relacionaCaracteres(aCaracter);
            estado = matriz[estado][columna];
        if (estado >= 100 && estado <= 199){
            if (seAgrega()){
                acumulador += QString(aCaracter);
            } else {
                i--;
            }
            verificarReservada(acumulador);
            ui->AreaTokens->appendPlainText(tokens(estado));
            estado=0;
            acumulador = "";
        } else if (estado >= 500 && estado <= 550) {
            if (seAgrega()){
                acumulador += QString(aCaracter);
            } else {
                i--;
            }
            ui->AreaErrores->appendPlainText(errores(estado));
            estado=0;
            acumulador = "";
        } else if (estado > 0 && estado < 100) {
            acumulador += QString(aCaracter);
        }
    }
}

int MainWindow:: relacionaCaracteres(char c){
    if (c>='0' && c<='9'){
        return 2;
    }
    switch(c){
    //letras mayusculas
          case 'A': return 0;

          case 'B': return 0;

          case 'C': return 0;

          case 'D': return 0;

          case 'F': return 0;

          case 'G': return 0;

          case 'H': return 0;

          case 'I': return 0;

          case 'J': return 0;

          case 'K': return 0;

          case 'L': return 0;

          case 'M': return 0;

          case 'N': return 0;

          case 'O': return 0;

          case 'P': return 0;

          case 'Q': return 0;

          case 'R': return 0;

          case 'S': return 0;

          case 'T': return 0;

          case 'U': return 0;

          case 'V': return 0;

          case 'W': return 0;

          case 'X': return 0;

          case 'Y': return 0;

          case 'Z': return 0;

          //letras minúsculas
          case 'a': return 1;

          case 'b': return 1;

          case 'c': return 1;

          case 'd': return 1;

          case 'f': return 1;

          case 'g': return 1;

          case 'h': return 1;

          case 'i': return 1;

          case 'j': return 1;

          case 'k': return 1;

          case 'l': return 1;

          case 'm': return 1;

          case 'n': return 1;

          case 'o': return 1;

          case 'p': return 1;

          case 'q': return 1;

          case 'r': return 1;

          case 's': return 1;

          case 't': return 1;

          case 'u': return 1;

          case 'v': return 1;

          case 'w': return 1;

          case 'x': return 1;

          case 'y': return 1;

          case 'z': return 1;

          //signos de puntuación
          case '.': return 4;

          case ';': return 23;

          case ':': return 22;

          //agrupación
          case '(': return 24;

          case')': return 25;

          case '[': return 26;

          case']': return 27;

          //signos de operaciones
          case '+': return 7;

          case'-': return 8;

          case '*': return 14;

          case'/': return 15;

          case '%': return 28;

          //operadores relacionales
          case'<': return 20;

          case '>': return 21;

          case'=': return 19;

          //operadores lógicos
          case'&': return 16;

          case '|': return 17;

          case'!': return 18;

          //guión bajo, comillas simples y dobles
          case'_': return 3;

          case '\'': return 12;

          case'\"': return 13;

          //notación cientifica
          case 'E': return 5;

          case 'e': return 6;

          //tabulador, espacio en blanco y salto de línea
          case'\n': return 10;

          case'\t': return 11;

          case' ': return 9;
        }
        return 29;
    }

QString MainWindow::tokens(int t){
    switch (t){
        case 100:
        return acumulador + ":Palabra reservada";
        case 101:
        return acumulador + ":Identificador";
        case 102:
        return acumulador + ":Constante entera";
        case 103:
        return acumulador + ":Constante real";
        case 104:
        return acumulador + ":Constante con notación cientifica";
        case 105:
        return acumulador + ":Constante caracter";
        case 106:
        return acumulador + ":Constante string";
        case 107:
        return acumulador + ":Suma";
        case 108:
        return acumulador + ":Resta";
        case 109:
        return acumulador + ":Multiplicación";
        case 110:
        return acumulador + ":División";
        case 111:
        return acumulador + ":Módulo";
        case 112:
        return acumulador + ":Comentario";
        case 113:
        return acumulador + ":AND";
        case 114:
        return acumulador + ":OR";
        case 115:
        return acumulador + ":NOT";
        case 116:
        return acumulador + ":Diferente";
        case 117:
        return acumulador + ":Igual";
        case 118:
        return acumulador + ":Mayor";
        case 119:
        return acumulador + ":Mayor o igual";
        case 120:
        return acumulador + ":Menor";
        case 121:
        return acumulador + ":Menor o igual";
        case 122:
        return acumulador + ":Asignación";
        case 123:
        return acumulador + ":Dos puntos";
        case 124:
        return acumulador + ":Punto y coma";
        case 125:
        return acumulador + ":Punto";
        case 126:
        return acumulador + ":Paréntesis que abre";
        case 127:
        return acumulador + ":Paréntesis que cierra";
        case 128:
        return acumulador + ":Llave que abre";
        case 129:
        return acumulador + ":Llave que cierra";
        }
}

QString MainWindow::errores(int e){
    switch (e){
        case 500:
        return acumulador + "" +  "Error 500: no es una constante numérica";
        case 501:
        return acumulador + "" +  "Error 501: esperaba caracter después de _ ";
        case 502:
        return acumulador + "" +  "Error 502: esperaba digito después de .";
        case 503:
        return acumulador + "" +  "Error 503: esperaba digito +, - ";
        case 504:
        return acumulador + "" +  "Error 504: esperaba digito después de signo +,- ";
        case 505:
        return acumulador + "" +  "Error 505: esperaba digito diferente a comilla simple ";
        case 506:
        return acumulador + "" +  "Error 506: esperaba comilla después de caracter ";
        case 507:
        return acumulador + "" +  "Error 507: esperaba signo de & después de & ";
        case 508:
        return acumulador + "" +  "Error 508: esperaba signo de | después de | ";
        case 509:
        return acumulador + "" +  "Error 509: 404 not found ";

        }
}

bool MainWindow::seAgrega(){
    switch (estado){
    case 100: 
      return false;
      //"caracter : Palabra reservada";
    case 101: 
      return false;
      //"caracter: Identificador";
    case 102: 
      return false;
      //"caracter: Constante entera";
    case 103: 
      return false;
      //"caracter: Constante real";
    case 104: 
      return false;
      //"caracter: Constante con notación cientifica";
    case 105: 
      return true;
      //"caracter: Constante caracter";
    case 106: 
      return true;
      //"caracter: Constante string";
    case 107: 
      return true;
      //"caracter: Suma";
    case 108: 
      return true;
      //"caracter: Resta";
    case 109: 
      return true;
      //"caracter: Multiplicación";
    case 110: 
      return false;
      //"caracter: División";
    case 111: 
      return true;
      //"caracter: Módulo";
    case 112: 
      return true;
      //"caracter: Comentario";
    case 113: 
      return true;
      //"caracter: AND";
    case 114: 
      return true;
      //"caracter: OR";
    case 115: 
      return false;
      //"caracter: NOT";
    case 116: 
      return true;
      //"caracter: Diferente";
    case 117: 
      return true;
      //"caracter: Igual";
    case 118: 
      return true;
      //"caracter: Mayor";
    case 119: 
      return true;
      //"caracter: Mayor o igual";
    case 120: 
      return true;
      //"caracter: Menor";
    case 121: 
      return true;
      //"caracter: Menor o igual";
    case 122: 
      return true;
      //"caracter: Asignación";
    case 123: 
      return true;
      //"caracter: Dos puntos";
    case 124: 
      return true;
      //"caracter: Punto y coma";
    case 125: 
      return true;
      //"caracter: Punto";
    case 126: 
      return true;
      //"caracter: Paréntesis que abre";
    case 127: 
      return true;
      //"caracter: Paréntesis que cierra";
    case 128: 
      return true;
      //"caracter: Llave que abre";
    case 129: 
      return true;
      //"caracter: Llave que cierra";
  //aquí empiezan los errores 
    case 500:
      return true; 
      //"Error 500: no es una constante numérica";
    case 501:
      return false;  
      //"Error 501: esperaba caracter después de _ ";
    case 502:
      return false;   
      //"Error 502: esperaba digito después de .";
    case 503:
      return true;   
      //"Error 503: esperaba digito +, - ";
    case 504:
      return false;   
      //"Error 504: esperaba digito después de signo +,- ";
    case 505:
      return false;   
      //"Error 505: esperaba digito diferente a comilla simple ";
    case 506:
      return false;   
      //"Error 506: esperaba comilla después de caracter ";
    case 507:
      return false; 
      //"Error 507: esperaba signo de & después de & ";
    case 508:
      return false;  
      //"Error 508: esperaba signo de | después de | ";
    case 509:
      return true;
      //"Error 509: 404 not found ";  
  }
}





bool MainWindow::verificarReservada(QString ac){
    esReservada = false;
    if (estado == 100){
   for(int i=0; i<palabraR.length(); i++)
   {
    if (ac.contains(palabraR[i])){
        esReservada = true;
    }
   }
   return esReservada;
}
}
