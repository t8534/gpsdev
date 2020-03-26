#ifndef GPSDEV_H_
#define GPSDEV_H_

#include <pthread.h>

extern pthread_mutex_t gpsmsg_mutex;
extern pthread_mutex_t condition_mutex;
extern pthread_cond_t  condition_cond;


#endif /* GPSDEV_H_ */





