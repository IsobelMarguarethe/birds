//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//------------------------- DISPLAYWINDOW ------------------------//

//  This class provides the neccessary functions to provide visual
//  proof of the current locations of each object within the air-
//                             space.

//----------------------------------------------------------------//

#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

#include "aviationsystem.h"

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QWidget
{
    Q_OBJECT

public:

    //--The constructor, defined as explicit to prevent accidental
    //--implicit type conversions by the compiler
    explicit DisplayWindow(AviationSystem *system,
                           QWidget *parent = 0);

    //--Real destruction
    ~DisplayWindow();

private slots:

    //--Slot called every time window is signalled to update by timer
    //--defined in constructor. Paints current position of all players
    //--to the window.
    void paintEvent(QPaintEvent *event);

    //--Slot called every time on-window check box is checked or
    //--unchecked.
    //--If checked, the z-component of the position vectors of objects
    //--are represented by their visible opacity.
    void on_ThreeD_toggled(bool checked);

private:

    //--Pointer to the memory containing the DisplayWindow ui form
    Ui::DisplayWindow *ui;

    //--Pointer to current aviation system data
    AviationSystem *fSystem;

    //--Vector of objects to paint
    std::vector< BirdPlayer* > fModelSystem;

    //--Boolean defining whether to scale opacity of objects to the
    //--z-component of their position vector.
    bool fOpacity;
};

#endif // DISPLAYWINDOW_H
