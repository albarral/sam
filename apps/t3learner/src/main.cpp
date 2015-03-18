/*
 * File:   main.cpp
 * Author: ainoa
 *
 * Created on March 12, 2015, 9:35 AM
 */

#include <QApplication>
#include "Window.h"

int main(int argc, char *argv[]) 
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    Window win;
    win.show();

    return app.exec();
}
