/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   gabriel@migtron.com   *
 ***************************************************************************/

#include <QApplication>
#include "Interface.h"

//comentario prueba github

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
        
    Interface form;   
    form.show();

    return app.exec();
}
