#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    return a.exec();
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myExtSerialPort= new QextSerialPort("/dev/ttyAMA0");
    myExtSerialPort->setBaudRate(BAUD115200);
    myExtSerialPort->setFlowControl(FLOW_OFF);
    myExtSerialPort->setParity(PAR_NONE);
    myExtSerialPort->setDataBits(DATA_8);
    myExtSerialPort->setStopBits(STOP_1);
    //port->setQueryMode(QextSerialPort::Polling);
    myExtSerialPort->close();
    if (myExtSerialPort->open(QIODevice::ReadWrite) == true){
        qDebug("port is opened");
    }
    else{
        qDebug("port is not open");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QByteArray array;
    array.resize(10);
    array[0]=(char)0xe5;
    array[1]=(char)0x63;
    array[2]=(char)0x63;
    array[3]=(char)0x63;
    array[4]=(char)0x63;
    array[5]=(char)0x63;
    array[6]=(char)0x63;
    array[7]=(char)0x63;
    array[8]=(char)0x63;
    array[9]=(char)0xe6;


    myExtSerialPort->write(array);
}

FORMS    += mainwindow.ui
include(qextserialport/src/qextserialport.pri)



        #include <QMainWindow>
        #include "qextserialport.h"

        namespace Ui {
        class MainWindow;
        }

        class MainWindow : public QMainWindow
        {
            Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = 0);
            ~MainWindow();

        private slots:
            void on_pushButton_clicked();

        private:
            Ui::MainWindow *ui;
            QextSerialPort *myExtSerialPort;
        };

        #endif // MAINWINDOW_H
