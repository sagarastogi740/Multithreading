#include "../include/glthread.h"
#include <stdio.h>
#include <stdlib.h>

void glthread_add_next(glthread_t *base_glthread, glthread_t *new_glthread)
{
    if (base_glthread->next)
    {
        new_glthread->prev = base_glthread;
        new_glthread->next = base_glthread->next;
        base_glthread->next->prev = new_glthread;
        base_glthread->next = new_glthread;
    }
    else
    {
        base_glthread->next = new_glthread;
        new_glthread->prev = base_glthread;
    }
}

void glthread_add_before(glthread_t *base_glthread, glthread_t *new_glthread)
{
    if (base_glthread->prev)
    {
        new_glthread->prev = base_glthread->prev;
        new_glthread->next = base_glthread;
        base_glthread->prev->next = new_glthread;
        base_glthread->prev = new_glthread;
    }
    else
    {
        base_glthread->prev = new_glthread;
        new_glthread->next = base_glthread;
    }
}

void remove_glthread(glthread_t *glthread)
{
    if (glthread->prev)
        glthread->prev->next = glthread->next;
    if (glthread->next)
        glthread->next->prev = glthread->prev;
}
void init_glthread(glthread_t *glthread)
{
    glthread->next = NULL;
    glthread->prev = NULL;
}
void glthread_add_last(glthread_t *base_glthread, glthread_t *new_glthread)
{
    glthread_t *glthreadptr = NULL;
    glthread_t *prevglthreadptr = base_glthread;
    ITERATE_GLTHREAD_BEGIN(base_glthread, glthreadptr)
    {
        prevglthreadptr = glthreadptr;
    }
    ITERATE_GLTHREAD_END()
    glthread_add_next(prevglthreadptr, new_glthread);
}
unsigned int get_glthread_list_count(glthread_t *base_glthread)
{
    unsigned int count = 0;
    glthread_t *glthreadptr = NULL;
    ITERATE_GLTHREAD_BEGIN(base_glthread, glthreadptr)
    {
        count++;
    }
    ITERATE_GLTHREAD_END()
    return count;
}