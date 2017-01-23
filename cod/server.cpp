
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

int currentData = 12850;
bool automode = false;


void stop_running(int sig)
{
    printf("\ngpio terminated through exception\n");
    gpioPWM(24, 0);
    sleep(1);
    gpioTerminate();
    exit(sig);
}

Server::Server()
{
    signal(SIGINT, stop_running);

    InputHandler *iH = new InputHandler();
    // TEST
   // iH->microcontroller();
    // TEST
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
       iH->app(12850);
       printf( "waiting for new client...\n" );
       if ( ( newsockfd = accept( sockfd, (struct sockaddr *) &cli_addr, (socklen_t*) &clilen) ) < 0 )
                   error( const_cast<char *>("ERROR on accept") );
       printf( "opened new communication with client\n" );
       automode = false;
       while ( 1 ) {
            //---- wait for a number from client ---
            data = getData( newsockfd );

            // Uebertragungs Fehler
            if(data == 2147483647 || data == 5019776)
            {
                printf("Uebertragungs Fehler!!! ( %d )\n", data);
                continue;
            }

            // App crash
            if(data == 0)
                break;

            // Lost connection
            if ( data == -1 )
            {
                std::cout << "lost connection" << std::endl;
                iH->app(12850);
                sleep(1);
                break;
            }

            //if((data == 12850 || data == 1285012850) && automode == false)
            if(data == -2 && automode == false)
            {
                printf("Starte automodus...\n");
                iH->start();
                automode = true;
                continue;
            }
            //else if(data != 12850 && automode == true)
            else if(data == -3 && automode == true)
            {
                printf("Beende automodus...\n");
                automode = false;
                iH->stop();
                iH->wait();
                continue;
            }
            else if(automode == true)
                continue;

            iH->app(data);


            //data = func( data );
            //--- send new data back ---
            //printf( "sending back %d\n", data );
       }

       //--- if -2 sent by client, we can quit ---
      // if(data == 0)
      // {
      //     std::cout << "App closed" << std::endl;
      //     iH->app(12850);
      //     sleep(1);
      //     break;
      // }
     // if ( data <= 0 )
     // {
     //     std::cout << "lost connection" << std::endl;
     //     iH->app(12850);
     //     sleep(1);
     //     continue;
     // }
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
