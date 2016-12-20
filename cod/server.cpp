
#include "server.h"

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "inputhandler.h"
#include <signal.h>
#include <pigpio.h>

int currentData = 3276850;


void stop_running(int sig)
{
    printf("\ngpio terminated through exception\n");
    gpioTerminate();
    exit(sig);
}

Server::Server()
{
    signal(SIGINT, stop_running);

    InputHandler *iH = new InputHandler();

    struct sockaddr_in serv_addr, cli_addr;
    int portno = 1234;

    printf( "using port #%d\n", portno );

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error( const_cast<char *>("ERROR opening socket") );
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( portno );
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
      error( const_cast<char *>( "ERROR on binding" ) );
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    //--- infinite wait on a connection ---
    while ( 1 ) {
       printf( "waiting for new client...\n" );
       if ( ( newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
                   error( const_cast<char *>("ERROR on accept") );
       printf( "opened new communication with client\n" );
       while ( 1 ) {
            //---- wait for a number from client ---
            data = getData( newsockfd );

            //printf( "got %d\n", data );

            if ( data <= 0 )
               break;
           // else if( data == automatikcode)
           // {
           //     iH->autoMode();
           //     break;
           // }
            else
                iH->app(data);


            //data = func( data );
            //--- send new data back ---
            //printf( "sending back %d\n", data );
       }

       //--- if -2 sent by client, we can quit ---
       if(data == 0)
       {
           std::cout << "App closed" << std::endl;
           iH->app(3276850);
           sleep(1);
           break;
       }
       else if ( data < 0 )
       {
           std::cout << "lost connection" << std::endl;
           iH->app(3276850);
           sleep(1);
           continue;
       }
    }
}

void Server::error( char *msg ) {
  perror(  msg );
  exit(1);
}

int Server::func( int a ) {
   return 2 * a;
}

int Server::getData( int sockfd ) {
  char buffer[32];
  int n;

  if ( (n = read(sockfd,buffer,31) ) < 0 )
    error( const_cast<char *>( "ERROR reading from socket") );
  buffer[n] = '\0';
  return atoi( buffer );
}
