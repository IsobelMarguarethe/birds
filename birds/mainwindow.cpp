//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//--------------------------- MAINWINDOW -------------------------//

//  This class provides the neccessary initialisation values for
//  the simuation of the airspace and allows the user to influence
//                 the objects within the airspace.

//----------------------------------------------------------------//

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //--Declare initial number of players of individual player types
    int PreyFlockSize = 15;
    int PredFlockSize = 0;
    int ObsFlockSize = 1;

    //--Set initial position, appearance, and parameters of components
    //--in the main window
    ui->setupUi(this);
    //--Green run button
    ui->Run->setStyleSheet("background-color:green");    
    //--Set range of obstacle momentum sliders:
    //--X-component slider
    ui->ObsMomX->setRange(0, 200);
    //--Y-component slider
    ui->ObsMomY->setRange(0, 200);
    //--Z-component slider
    ui->ObsMomZ->setRange(0, 200);    
    //--Set intial range of spin-box
    ui->spinBox->setRange(1, ObsFlockSize);
    //--Upper left corner of window has co-ordinates (50, 50) on screen,
    //--and window size is defined by that set in the mainwindow.ui form
    setGeometry(50, 50, width(), height());
    //--Title of Main Window
    setWindowTitle("Birds Flocking in 3D - Control Window");
    //--Initial running status of simulation
    fRunStatus = Idle;
    //--Implement a new instance of an Aviation System
    fAviationSystem = new AviationSystem(PreyFlockSize,
                                         fPreyMaxMom,
                                         PredFlockSize,
                                         fPredMaxMom,
                                         ObsFlockSize,
                                         fObsMaxMom);
    //--Initialise timer to control the rate of evolution of the new system
    QTimer *Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(Animate()));
    //--Send timeout signal every 10 milliseconds
    Timer->start(10);
}

void MainWindow::Animate()
{
    //--Call the aviation system to evolve if the user has set the simulation
    //--status to Running by clicking the Run button
    if(fRunStatus == Running)
    {
        fAviationSystem->Simulate();
    }
}

void MainWindow::on_Run_clicked()
{
    if (fRunStatus == Idle)
    {
        //--Set appearance of main window during simulation:
        //--Change Run button colour to red
        ui->Run->setStyleSheet("background-color:red");
        //--Change Run button text to 'Stop'
        ui->Run->setText("Stop");
        //--Open a new display window showing the system
        //--intialised by the main window
        DisplayWindow *newwindow =
                new DisplayWindow(fAviationSystem);
        fCurrentWindow = newwindow;
        //--Change the simulation status
        fRunStatus = Running;
    }else
    {
        //--Set appearance of main window when simulation is idle:
        //--Change Run button colour to green
        ui->Run->setStyleSheet("background-color:green");
        //--Change Run button text to 'Run'
        ui->Run->setText("Run");
        //--Delete the current window
        fCurrentWindow->~DisplayWindow();
        //--Change the simulation status
        fRunStatus = Idle;
    }

}

void MainWindow::on_AddPrey_clicked()
{
    //--Create a new instance of Prey
    Prey *newprey = new Prey(ThreeVector(),
                             ThreeVector(),
                             fPreyMaxMom);
    //--Assign random position
    newprey->SetPos(newprey->RandPos());
    //--Insert pointer into the current system
    fAviationSystem->AddPrey(newprey);
}

void MainWindow::on_AddPred_clicked()
{
    //--Create a new instance of Predator and insert into the
    //--current system
    Predator *newpred = new Predator(ThreeVector(),
                                     ThreeVector(),
                                     fPredMaxMom);
    //--Assign random position
    newpred->SetPos(newpred->RandPos());
    //--Insert pointer into the current system
    fAviationSystem->AddPred(newpred);
}

void MainWindow::on_AddObs_clicked()
{
    //--implement a new instance of Obstacle and insert into the
    //--aviation system
    Obstacle *newobs;

    newobs = new Obstacle(ThreeVector(),
                            ThreeVector(),
                            fObsMaxMom);
    //--Assign random position
    newobs->SetPos(newobs->RandPos());
    //--Assign random momentum scaled to maximum obstacle momentum
    newobs->SetMom(newobs->RandomVector()*fObsMaxMom);
    //--Insert pointer into the current system
    fAviationSystem->AddObs(newobs);
    //--Update range of spin box to new number of obstacles in system
    ui->spinBox->setRange(1, fAviationSystem->ObsNumber());
}

void MainWindow::on_DelPrey_clicked()
{
    //--Call the destructor of the most recently created Prey
    if (fAviationSystem->PreyNumber() > 0)
    {
        fAviationSystem->ErasePrey(0);
    }
}

void MainWindow::on_DelPred_clicked()
{
    //--Call the destructor of the most recently created Predator
    if (fAviationSystem->PredNumber() > 0)
    {
        fAviationSystem->ErasePred(0);
    }
}



void MainWindow::on_DelObs_clicked()
{
    //--Call the destructor of the most recently created Obstacle
    if (fAviationSystem->ObsNumber() > 0)
    {
        fAviationSystem->EraseObs(0);
        //--Update the range of the spin-box to new number of obstacles in system
        ui->spinBox->
            setRange(1, fAviationSystem->ObsNumber());
    }
}



void MainWindow::on_ObsMomX_sliderMoved(int position)
{
    //--Allow the user to control the x-component of the momentum of the
    //--obstacle referenced by the spin-box value
    int ThisObs = ui->spinBox->value()-1;
    //--Store current momentum
    ThreeVector OldMom = fAviationSystem->
                         GetObstacle(ThisObs)->
                         GetMom();
    //--Define maximum as 1/2 total slider range such that central position
    //--is equivelent to zero
    double Maximum = double (ui->ObsMomX->maximum())/2.0;
    //--Set new momentum component based on slider position as fraction of
    //--Maximum
    double NewX =
            double(position - Maximum)*(1.0/Maximum)*fObsMaxMom;
    //--Declare new momentum
    ThreeVector NewMom = ThreeVector(NewX, OldMom.Y(), OldMom.Z());
    //--Assign new momentum
    fAviationSystem->GetObstacle(ThisObs)->SetMom(NewMom);
    //--Apply momentum restrictions
    fAviationSystem->GetObstacle(ThisObs)->RestrictMom();
}

void MainWindow::on_ObsMomY_sliderMoved(int position)
{
    //--Allow the user to control the y-component of the momentum of the
    //--obstacle referenced by the spin-box value
    int ThisObs = ui->spinBox->value()-1;
    //--Store current momentum
    ThreeVector OldMom = fAviationSystem->
                         GetObstacle(ThisObs)->
                         GetMom();
    //--Define maximum as 1/2 total slider range such that central position
    //--is equivelent to zero
    double Maximum = double (ui->ObsMomY->maximum())/2.0;
    //--Set new momentum component based on slider position as fraction of
    //--Maximum
    double NewY =
            double(position - Maximum)*(1.0/Maximum)*fObsMaxMom;
    //--Declare new momentum
    ThreeVector NewMom = ThreeVector(OldMom.X(), NewY, OldMom.Z());
    //--Assign new momentum
    fAviationSystem->GetObstacle(ThisObs)->SetMom(NewMom);
    //--Apply momentum restrictions
    fAviationSystem->GetObstacle(ThisObs)->RestrictMom();
}

void MainWindow::on_ObsMomZ_sliderMoved(int position)
{
    //--A the user to control the z-component of the momentum of the
    //--obstacle referenced by the spin-box value
    int ThisObs = ui->spinBox->value()-1;
    //--Store current momentum
    ThreeVector OldMom = fAviationSystem->
                         GetObstacle(ThisObs)->
                         GetMom();
    //--Define maximum as 1/2 total slider range such that central position
    //--is equivelent to zero
    double Maximum = double (ui->ObsMomZ->maximum())/2.0;
    //--Set new momentum component based on slider position as fraction of
    //--Maximum
    double NewZ =
            double(position - Maximum)*(1.0/Maximum)*fObsMaxMom;
    //--Declare new momentum
    ThreeVector NewMom = ThreeVector(OldMom.X(), OldMom.Y(), NewZ);
    //--Assign new momentum
    fAviationSystem->GetObstacle(ThisObs)->SetMom(NewMom);
    //--Apply momentum restrictions
    fAviationSystem->GetObstacle(ThisObs)->RestrictMom();
}

MainWindow::~MainWindow()
{
    delete ui;
}
