//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//------------------------------- MAIN ---------------------------//

//         The main program simply runs the MainWindow widget.

//----------------------------------------------------------------//

#include "mainwindow.h"
#include "displaywindow.h"

#include <QApplication>

#include "obstacle.h"
#include "predator.h"
#include "prey.h"

#include <stdio.h>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
