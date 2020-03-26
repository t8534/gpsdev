// gpsdev.c
//
// TODO:
//
// 1.
// Remove tcpip end run pure pthread code from sfml_serv.
// Check is wait/signal working.
// Check is mutexes on buffer working.
// All in 2 variants:
// - 2 separate threads.
// - single thread and main process 
//
// 2.
// Run tcpip server on 2 separate threads, as in sfml.
//
// 3.
// If sockets are not working on thread try single thread for gpsev and socket server in main
// process.
// 


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "gpsdev.h"
#include "server.h"
#include "gpsmod.h"

pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;



int main(int argc, char* argv[]) {
	
	
		// Test if this is only signle thread for gpsdev
	pthread_t thread2;
	pthread_create(&thread2, NULL, gpsmod, NULL);  //todo: check should we do something more for this thread here, like a join or so.
	Server();
	//pthread_create(&thread1, NULL, Server, NULL);
	//pthread_create(&thread2, NULL, Gpsdev, NULL);

	//pthread_join( thread2, NULL);  // todo: what about this join

	return 0;	// Change to exit success
}

# if0
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <thread>
#include <iostream>


#define PORT 7000
#define QUEUE 20

int conn;

void thread_task() {
}

int main() {
    //printf("%d\n",AF_INET);
    //printf("%d\n",SOCK_STREAM);
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    //printf("%d\n",ss);
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    //printf("%d\n",INADDR_ANY);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(ss, (struct sockaddr* ) &server_sockaddr, sizeof(server_sockaddr))==-1) {
        perror("bind");
        exit(1);
    }
    if(listen(ss, QUEUE) == -1) {
        perror("listen");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    /// Successful return of non-negative descriptor, error Return-1
    conn = accept(ss, (struct sockaddr*)&client_addr, &length);
    if( conn < 0 ) {
        perror("connect");
        exit(1);
    }

    char buffer[1024];
    //Create another thread
    //std::thread t(thread_task);
    //t.join();
    //char buf[1024];
    //Main thread
    while(1) {

        // memset(buf, 0 ,sizeof(buf));
        // if(fgets(buf, sizeof(buf),stdin) != NULL) {
        //     send(conn, buf, sizeof(buf), 0);    
        // }

        memset(buffer, 0 ,sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0);
        if(strcmp(buffer, "exit\n") == 0) break;
        printf("%s", buffer);
        //You have to return data to make a complete request.
        send(conn, buffer, len , 0);
    }
    close(conn);
    close(ss);
    return 0;
}

#endif