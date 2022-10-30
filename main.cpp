#include <iostream>
#include <curses.h>


#include "listen.h"

using namespace std;







int main()
{

    int sayi;

    pthread_t threadId;



    int err = pthread_create(&threadId, NULL, ListenFunc, (void*)&sayi );

    printf("Running...");
    char szBuffer[100];
   scanf("%s",szBuffer);
    //wgetch();
    return 0;
}
