#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

// static void *thread_fn_callback(void *args)
// {
//     char *input = (char *)args;
//     while (1)
//     {
//         printf("Input String = %s\n", input);
//         sleep(1);
//     }
// }

// void thread1_create()
// {
//     pthread_t pthread1;
//     static char *thread_input1 = "I am thread number 1";
//     int rc = pthread_create(&pthread1,
//                             NULL,
//                             thread_fn_callback,
//                             (void *)thread_input1);
//     if (rc)
//     {
//         printf("Error occured, thread could not be created, errno = %d\n", rc);
//         exit(0);
//     }
// }

// void thread2_create()
// {
//     pthread_t pthread2;
//     static char *thread_input2 = "I am thread number 2";
//     int rc = pthread_create(&pthread2,
//                             NULL,
//                             thread_fn_callback,
//                             (void *)thread_input2);
//     if (rc)
//     {
//         printf("Error occured, thread could not be created, errno = %d\n", rc);
//         exit(0);
//     }
// }

static void *sqr(void *arg)
{
    int cnt = 10;
    int input = *(int *)arg;
    int *output = (int *)calloc(1, sizeof(int));
    free(arg);
    *output = input * input;
    while (cnt--)
    {
        printf("Working for input = %d\n", input);
        sleep(input);
    }
    return (void *)output;
}

void thread_create(pthread_t *pthread_handle, int thread_input)
{
    pthread_attr_t attr;
    int *_thread_input = (int *)calloc(1, sizeof(int));
    *_thread_input = thread_input;
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(pthread_handle, &attr, sqr, (void *)_thread_input);
}

int main(int argc, char **argv)
{
    pthread_t t1;
    pthread_t t2;
    void *result1;
    void *result2;
    thread_create(&t1, 2);
    thread_create(&t2, 5);
    pthread_join(t1, &result1);
    pthread_join(t2, &result2);
    if (result1)
    {
        printf("Return result from thread 1 = %d\n", *(int *)result1);
        free(result1);
        result1 = NULL;
    }
    if (result2)
    {
        printf("Return result from thread 2 = %d\n", *(int *)result2);
        free(result2);
        result2 = NULL;
    }
    pthread_exit(0);
    return 0;
}