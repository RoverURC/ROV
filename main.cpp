#include <QCoreApplication>
#include <rov.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    ROV rov;

    return a.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
