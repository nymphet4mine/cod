#ifndef SERVER_H
#define SERVER_H

class Server
{

public:
    Server();

private:
    int sockfd;
    int newsockfd;
    int clilen;
    char buffer[256];
    int n;
    int data;


    void error( char *msg );
    int func( int a );
    void sendData( int sockfd, int x );
    int getData( int sockfd );

};

#endif // SERVER_H
