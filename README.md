### Philosophers

## External functions

# memset - fill a byte string with a byte value
SYNOPSIS
    #include <string.h>
    void	*memset(void *b, int c, size_t len);

DESCRIPTION
	The memset() function writes len bytes of value c (converted to an unsigned char) to the string b.

RETURN VALUES
     The memset() function returns its first argument.


# usleep - suspend thread execution for an interval measured in microseconds
SYNOPSIS
    #include <unistd.h>
    int		usleep(useconds_t microseconds);

DESCRIPTION
     The usleep() function suspends execution of the calling thread until either microseconds microseconds have elapsed or a signal is delivered to the thread and its action is to invoke a signal-catching
     function or to terminate the process.  System activity or limitations may lengthen the sleep by an indeterminate amount.

RETURN VALUES
     The usleep() function returns the value 0 if successful; otherwise the value -1 is returned and the global variable errno is set to indicate the error.

# gettimeofday - get date and time
SYNOPSIS
    #include <sys/time.h>
    int		gettimeofday(struct timeval *restrict tp, void *restrict tzp);

DESCRIPTION
     The system's notion of the current Greenwich time and the current time zone is obtained with the gettimeofday() call. The time is expressed in seconds and microseconds since midnight (0 hour), January 1, 1970.  The resolution of the system clock is hardware dependent, and the time may be updated continuously or in ``ticks.''  If tp is NULL and tzp is non-NULL,
     gettimeofday() will populate the timezone struct in tzp.  If tp is non-NULL and tzp is NULL, then only the timeval struct in tp is populated. If both tp and tzp are NULL, nothing is returned.

     struct timeval {
             time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
             suseconds_t  tv_usec;  /* and microseconds */
     };

RETURN
     A 0 return value indicates that the call succeeded.  A -1 return value indicates an error occurred, and in this case an error code is stored into the global variable errno.

# pthread_create - create a new thread
SYNOPSIS
     #include <pthread.h>
     int	pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

ESCRIPTION
     The pthread_create() function is used to create a new thread, with attributes specified by attr, within a process.  If attr is NULL, the default attributes are used.  If the attributes specifie attr
     are modified later, the thread's attributes are not affected.  Upon successful completion pthread_create() will store the ID of the created thread in the location specified by thread.

     The thread is created executing start_routine with arg as its sole argument.  If the start_routine returns, the effect is as if there was an implicit call to pthread_exit() using the return value of
     start_routine as the exit status.  Note that the thread in which main() was originally invoked differs from this.  When it returns from main(), the effect is as if there was an implicit call to 
	 exit() using the return value of main() as the exit status.

     Upon thread exit the storage for the thread must be reclaimed by another thread via a call to pthread_join().  Alternatively, pthread_detach() may be called on the thread to indicate that the system may automatically reclaim the thread storage upon exit.  The pthread_attr_setdetachstate() function may be used on the attr argument passed to pthread_create() in order to achieve the same effect as a call to pthread_detach() on the newly created thread.

     The signal state of the new thread is initialized as:

           o   The signal mask is inherited from the creating thread.

           o   The set of signals pending for the new thread is empty.

RETURN VALUES
     If successful, the pthread_create() function will return zero.  Otherwise an error number will be returned to indicate the error.

# pthread_detach - detach (ablösen) a thread
SYNOPSIS
     #include <pthread.h>
     int	pthread_detach(pthread_t thread);


DESCRIPTION
     The pthread_detach() function is used to indicate to the implementation that storage for the thread thread can be reclaimed (zurückgefordet) when the thread terminates.  
	 If thread has not terminated, pthread_detach() will not cause it to terminate.  The effect of multiple pthread_detach() calls on the same target thread is unspecified.

RETURN VALUES
     If successful, the pthread_detach() function will return zero.  Otherwise an error number will be returned to indicate the error.  Note that the function does not change the value of errno as it did for some drafts of the standard.  These early drafts also passed a pointer to pthread_t as the argument.  Beware!

# pthread_join - wait for thread termination
SYNOPSIS
     #include <pthread.h>
     int	pthread_join(pthread_t thread, void **value_ptr);

DESCRIPTION
     The pthread_join() function suspends (aussetzen) execution of the calling thread until the target thread terminates unless the target thread has already terminated.

     On return from a successful pthread_join() call with a non-NULL value_ptr argument, the value passed to pthread_exit() by the terminating thread is stored in the location referenced by value_ptr.  When a pthread_join() returns successfully, the target thread has been terminated.  The results of multiple simultaneous calls to pthread_join() specifying the same target thread are undefined.  If the thread calling pthread_join() is cancelled, then the target thread is not detached.

RETURN VALUES
     If successful, the pthread_join() function will return zero.  Otherwise, an error number will be returned to indicate the error.

# pthread_mutex_destroy & pthread_mutex_init
SYNOPSIS
     #include <pthread.h>
	 int 	pthread_mutex_destroy(pthread_mutex_t *mutex);
	 int	pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);

DESCRIPTION
	 The pthread_mutex_destroy() function shall destroy the mutex object referenced by mutex; the mutex object becomes, in effect, uninitialized. An implementation may cause pthread_mutex_destroy() to set the object referenced by mutex to an invalid value. A destroyed mutex object can be reinitialized using pthread_mutex_init(); the results of otherwise referencing the object after it has been destroyed are undefined.

	 It shall be safe to destroy an initialized mutex that is unlocked. Attempting to destroy a locked mutex results in undefined behavior. 

	 The pthread_mutex_init() function shall initialize the mutex referenced by mutex with attributes specified by attr. If attr is NULL, the default mutex attributes are used; the effect shall be the same as passing the address of a default mutex attributes object. Upon successful initialization, the state of the mutex becomes initialized and unlocked. 

RETURN VALUES
     If successful, the pthread_mutex_destroy() and pthread_mutex_init() functions shall return zero; otherwise, an error number shall be returned to indicate the error. 

# pthread_mutex_lock - lock a mutex
SYNOPSIS
     #include <pthread.h>
     int	pthread_mutex_lock(pthread_mutex_t *mutex);

DESCRIPTION
     The pthread_mutex_lock() function locks mutex.  If the mutex is already locked, the calling thread will block until the mutex becomes available.

RETURN VALUES
     If successful, pthread_mutex_lock() will return zero, otherwise an error number will be returned to indicate the error.

# pthread_mutex_unlock - unlock a mutex
SYNOPSIS
     #include <pthread.h>
     int	qpthread_mutex_unlock(pthread_mutex_t *mutex);

DESCRIPTION
     If the current thread holds the lock on mutex, then the pthread_mutex_unlock() function unlocks mutex.

     Calling pthread_mutex_unlock() with a mutex that the calling thread does not hold will result in undefined behavior.

RETURN VALUES
     If successful, pthread_mutex_unlock() will return zero, otherwise an error number will be returned to indicate the error.

## Input
./philo : "number_of_philosophers" "time_to_die" "time_to_eat" "time_to_sleep" "[number_of_times_each_philosopher_must_eat]"