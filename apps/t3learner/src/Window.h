/* 
 * File:   Window.h
 * Author: ainoa
 *
 * Created on March 12, 2015, 10:13 AM
 */

#ifndef WINDOW_H
#define	WINDOW_H

#include <QWidget>

#include <QPushButton>
#include <QMessageBox>

QT_FORWARD_DECLARE_CLASS(QGraphicsScene)
QT_FORWARD_DECLARE_CLASS(QGraphicsView)

class Window : public QWidget
{
    
    Q_OBJECT
    
    private:         
        QGraphicsScene *scene;
        QGraphicsView *view;
        
    private slots:
        void clear();
        void recuperar();
            
    private:
        
        QPushButton *buttonIniciar;
        QPushButton *buttonRecuperar;
        QMessageBox* msgBox; 
            
    public:
        Window(QWidget *parent = 0);

};

#endif	/* WINDOW_H */

