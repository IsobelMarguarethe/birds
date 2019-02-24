//Isobel Romero-Shaw ---------------------------------- 26.11.2016//

//------------------------- DISPLAYWINDOW ------------------------//

//  This class provides the neccessary functions to provide visual
//  proof of the current locations of each object within the air-
//                             space.

//----------------------------------------------------------------//

#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(AviationSystem * system, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWindow), fSystem(system)
{
    //--Set initial appearance and position of the display window:
    ui->setupUi(this);
    //--Black background
    setStyleSheet("background-color:black");
    //--Upper left corner of window has co-ordinates (500, 50) on screen,
    //--and window size is set by virtual space defined in BirdPlayer
    setGeometry(500, 50, Width, Height);
    setAutoFillBackground(false);
    //--Title of Display Window
    setWindowTitle("Birds flocking in 3D");
    //--Set colour of text adjacent to check-box
    ui->ThreeD->setStyleSheet("color:white");
    //--Set initial state of check-box
    ui->ThreeD->setCheckState(Qt::Checked);

    //--Initialise timer controlling update rate of the display
    QTimer *Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(update()));
    //--Send timeout signal every 10 milliseconds
    Timer->start(10);

    //--Show window
    show();
    setAttribute(Qt::WA_OpaquePaintEvent);
}

void DisplayWindow::paintEvent(QPaintEvent *event)
{
    //--Declare unused parameters void to prevent compiler warnings
    (void) event;
    //--Declare painter to this window
    QPainter painter(this);
    //--Declare a seperate pen for each player type
    QPen preypen, predpen, obspen;

    //--Initialise pen types for use with specific player types:
    //--Small, circular, white pen for prey
    preypen.setCapStyle(Qt::RoundCap);
    preypen.setWidth(4);
    preypen.setColor(Qt::white);
    //--Medium, circular, red pen for predators
    predpen.setCapStyle(Qt::RoundCap);
    predpen.setWidth(6);
    predpen.setColor(Qt::red);
    //--Large, square, yellow pen for objects
    obspen.setCapStyle(Qt::SquareCap);
    obspen.setWidth(8);
    obspen.setColor(Qt::yellow);

    //--Repaint black background to remove previously drawn positions
    painter.fillRect(QRect(0, 0, Width, Height), QPalette::Text);

    int NPrey = fSystem->PreyNumber();
    int NPred = fSystem->PredNumber();
    int NObs = fSystem->ObsNumber();

    //--Clear vector of BirdPlayer pointers
    fModelSystem.clear();

    //--Fill BirdPlayer vector with all players in the system
    for (int i = 0; i < NPrey; i++)
    {
        fModelSystem.push_back(fSystem->GetPrey(i));
    }
    for (int j = 0; j < NPred; j++)
    {
        fModelSystem.push_back(fSystem->GetPredator(j));
    }
    for (int l = 0; l < NObs; l++)
    {
        fModelSystem.push_back(fSystem->GetObstacle(l));
    }

    int NAll = fModelSystem.size();

    ThreeVector Position;

    for (int i = 0; i < NAll; i++)
    {
        //--Draw every player in the system, determining which pen to use based
        //--on their PlayerType

        Position = fModelSystem[i]->GetPos();

        if (fModelSystem[i]->GetPlayerType() == BirdPlayer::Friendly)
        {
            painter.setPen(preypen);
        }
        else if (fModelSystem[i]->GetPlayerType() == BirdPlayer::Dangerous)
        {
          painter.setPen(predpen);
        }
        else if (fModelSystem[i]->GetPlayerType() == BirdPlayer::Neutral)
        {
            painter.setPen(obspen);
        }
        //--Set the opacity of the pen proportional to the z-component of the
        //--player position
        if (fOpacity == true)
        {
            painter.setOpacity(Position.Z()/Depth);
        }

        painter.drawPoint(Position.X(), Position.Y());
    }

}

void DisplayWindow::on_ThreeD_toggled(bool checked)
{
    //--Allows user option to view the depth of the system
    if (checked)
    {
        fOpacity = true;
    }
    else
    {
        fOpacity = false;
    }
}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}
