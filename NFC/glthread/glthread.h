#ifndef __GLTHREAD_H__
#define __GLTHREAD_H__

#define OFFSET(struct_name, field_name) ((unsigned long int)(&(((struct_name *)0)->field_name)))
#define GLTHREAD_NODE_ADDR(struct_name, glue_addr, glue_name) ((struct_name *)(((unsigned long)glue_addr) - OFFSET(struct_name, glue_name)))
#define BASE(glthreadptr) ((glthreadptr)->next)
#define ITERATE_GLTHREAD_BEGIN(glthreadptrstart, glthreadptr) \
    for (glthreadptr = BASE(glthreadptrstart); glthreadptr != NULL; glthreadptr = (glthreadptr)->next)

#define ITERATE_GLTHREAD_END()

typedef struct glthread_
{
    struct glthread_ *prev;
    struct glthread_ *next;
} glthread_t;

void glthread_add_next(glthread_t *base_glthread, glthread_t *new_glthread);
void glthread_add_before(glthread_t *base_glthread, glthread_t *new_glthread);
void remove_glthread(glthread_t *glthread);
void init_glthread(glthread_t *glthread);
void glthread_add_last(glthread_t *base_glthread, glthread_t *new_glthread);
unsigned int get_glthread_list_count(glthread_t *base_glthread);
#endif