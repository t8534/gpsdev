//


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "gpsdev.h"
#include "server.h"
#include "gpsmod.h"



void Server()
{
	bool connection = true;
	
	while (connection)
	{
		std::cout << "Test: Server: Before pthread_cond_wait(&condition_cond, &condition_mutex);" << std::endl;

		//todo: add check for return, 0 should be returned if succesfull
		//todo: The mutexes here are used as a condition variables, so we could use buffer
		// as a condition variable. And save a mutex which could be separately dedicated for that.
		//
		// The pthread_mutex_lock() lock mutex intentionally.
		// This is because pthread_cond_wait() will unlock this mutex in order to allow
		// another thread operate on common condition variable and send signal.
		// After pthread_cond_wait() receive signal it lock mutex again, and exit.
		// This is why finally we have to unlock mutex again.
		// So both mutexes are necessary.
		// todo: perhaps variable condition could be used in any way, following description above ?
		pthread_mutex_lock( &condition_mutex );
		pthread_cond_wait(&condition_cond, &condition_mutex);
		// todo: perhaps GPSDEV_GetMsg(buff) shoudl be here ?
		pthread_mutex_unlock( &condition_mutex );  //todo: Why do we have unlock mutex here if unlock is realised by pthread_condition_wait()

		printf("Test: Server: After pthread_cond_wait(&condition_cond, &condition_mutex)" \n};
		fflush(stdout);
	}
	
}

