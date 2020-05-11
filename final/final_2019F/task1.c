/* 
 * This program implements a multi-threading program:
 *Functionality Description:
	This program will start two new threads with each of them increasing a global variable "counter" by 0x1024. 
	Before a thread starts increasing "counter", it needs to acquire a global lock called "cs392_lock", and release it after the increasing
	In the master thread, it needs to join all the child threads
	In the master thread, it also needs to print the final result of "counter" (the correct results will be 0x2048)	

 * Testing points:
 You are required to find out 10 errors in the following piece of code. You need to find at least 8 errors to get full score. 

 
HINT:

 Note that all the errors are marked with hints

 Please find syntax and grammar errors that also prevent the building
 	Pay attention to compiler warnings (if all syntax and grammar errors are fixed, you will not see any compiler warnings)

 Please find the errors that mismatch the above functionality descriptions

 Please find the missing of error checking 

 Please find other errors based on the hints (you may need to change the locations of some code)


 To test this case, run "make task1"
 	After fixing all the errors, the program will terminate very quick and print the correct result
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define CNT_NUM 0x1000  //HINT 7: does this match the description

pthread_t tid[2];
int counter;
pthread_mutex_t cs392_lock;

void* cs392_count(void* noarg)  //HINT 4: maybe check the prototype and see if it matches the expected one?
{
    printf("\n A new Job has started\n");

    pthread_mutex_lock(&cs392_lock);

    unsigned long i = 0;

    for (i = 0; i < CNT_NUM; i++)
        counter++;

    //HINT 2: something is missing here?
    pthread_mutex_unlock(&cs392_lock);

    printf("\n A job has finished\n");

    return NULL;
}

int main(void) {
    int error;
    int i = 0;

    //HINT 3; think about the variable scope; this variable has to be accessible by other functions

    counter = 0;

    if (pthread_mutex_init(&cs392_lock, NULL) != 0) {  //HINT 10: check the interface definition. What does it need as the first argument?
        printf("\n cannot init the mutex\n");
        return 1;
    }

    while (i < 2) {
        error = pthread_create(&(tid[i]), NULL, cs392_count, NULL);

        //HINT 5: some checking is missing?
        if (error != 0) {
            printf("\nThread can't be created :[%s]",
                   strerror(error));
        }

        i++;

        //HINT 9: Forget to do something so that the loop can exit? This is different from HINT 5
    }

    printf("The final result of the counter is 0x%x\n", counter);  //HINT 8: can you really get reliable results by doing printing here?

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    //HINT 6: have all the threads been joined?

    pthread_mutex_destroy(&cs392_lock);

    return 0;
}
