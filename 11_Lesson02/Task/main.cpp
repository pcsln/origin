#include <QCoreApplication>
#include <QTcpSocket>
#include <QSqlDatabase>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpSocket socket;

    QSqlDatabase connect;

    return a.exec();
}
