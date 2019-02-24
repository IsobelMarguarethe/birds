//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//--------------------------- MAINWINDOW -------------------------//

//  This class provides the neccessary initialisation values for
//  the simuation of the airspace and allows the user to influence
//                 the objects within the airspace.

//----------------------------------------------------------------//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "displaywindow.h"
#include "aviationsystem.h"

namespace Ui {
class MainWindow;
}
//--Declare the DisplayWindow class
class DisplayWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    //--The constructor, defined as explicit to prevent accidental
    //--implicit type conversions by the compiler
    explicit MainWindow(QWidget *parent = 0);

    //--Real destructor
    ~MainWindow();

private slots:

    //--Slot connected to timer defined in constructor. Calls
    //--current aviation system to evolve by one timestep.
    void Animate();

    //--Slots connected to actions performed on window controls:
    //--Run button
    void on_Run_clicked();
    //--Add Prey button
    void on_AddPrey_clicked();
    //--Add Predator button
    void on_AddPred_clicked();
    //--Add Obstacle button
    void on_AddObs_clicked();
    //--Delete Prey button
    void on_DelPrey_clicked();
    //--Delete Predator button
    void on_DelPred_clicked();
    //--Delete Obstacle button
    void on_DelObs_clicked();

    //--Obstacle momentum sliders:
    //--X-component
    void on_ObsMomX_sliderMoved(int position);
    //--Y-component
    void on_ObsMomY_sliderMoved(int position);
    //--Z-component
    void on_ObsMomZ_sliderMoved(int position);

private:

    //--Pointer to memory storing data of the MainWindow ui form
    Ui::MainWindow *ui;

    //--Enumerated list of possible states of the simulation
    enum RunStatus{Idle,
                   Running};
    //--Variable storing current simulation state
    int fRunStatus;

    //--Pointer to current Aviation System object data
    AviationSystem *fAviationSystem;

    //--Pointer to current Display Window object data
    DisplayWindow *fCurrentWindow;

    //--Maximum momentum of each player type:
    //--Prey maximum momentum
    double const fPreyMaxMom = 0.15;
    //--Predator maximum momentum
    double const fPredMaxMom = 0.7;
    //Obstacle maximum momentum
    double const fObsMaxMom = 0.6;

}

;

#endif // MAINWINDOW_H
