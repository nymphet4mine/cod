
#include "server.h"

//Server::Server(QObject *parent) :
//    QObject(parent)
//{
//    myserver = new QTcpServer(this);
//
//    connect(myserver,SIGNAL(newConnection()), this,SLOT(newConnection()));
//
//    if(!myserver->listen(QHostAddress::Any,1234))
//    {
//        //std::cout << "Server could not start!";
//    }
//    else
//    {
//        //std::cout << "Server started";
//    }
//}


void Server::newConnection()
{

    QTcpSocket *socket = myserver->nextPendingConnection();


    socket->write(("hello client\r\n"));
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
}
