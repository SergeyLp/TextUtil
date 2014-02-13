#include "stdafx.h"
#include "mainwindow.h"

#include"../TextCore/Main.h"


int main(int argc, char *argv[]){
    //const int res = getFile(_T(""));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
