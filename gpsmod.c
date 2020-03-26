
//

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>	// sleep

#include "gpsmod.hpp"
#include "gpsdev.hpp"
#include "server.hpp"  // todo: is it necessary ?


void *gps(void *x_void_ptr)
{
	
	for(;;)
	{
		// todo: add check for return, 0 should be returned if succesfull
		pthread_mutex_lock(&condition_mutex);  //todo: probably condition_mutex is not necessary here, as we are not using condition variable but only signals.
		pthread_cond_signal(&condition_cond);
		pthread_mutex_unlock(&condition_mutex);

		printf("Test: Gpsmod: After pthread_cond_signal(&condition_cond)" \n};
		fflush(stdout);
		
		// Linux: sleep(seconds)
		sleep(1);  // 1 sec .Emulate blocking call.

	}  // End of for(;;)

}
