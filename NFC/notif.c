#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <strings.h>
#include "notif.h"

void nfc_register_notif_chain(notif_chain_t *nfc,
                              notif_chain_elem_t *nfce)
{
    notif_chain_elem_t *new_nfce = calloc(1, sizeof(notif_chain_elem_t));
    memcpy(new_nfce, nfce, sizeof(notif_chain_elem_t));
    init_glthread(&new_nfce->glue);
    glthread_add_next(&nfc->notif_chain_head, &new_nfce->glue);
}

void nfc_invoke_notif_chain(notif_chain_t *nfc,
                            void *arg,
                            size_t arg_size,
                            char *key,
                            size_t key_size,
                            nfc_op_t nfc_op_code)
{
    glthread_t *itr = NULL;
    notif_chain_elem_t *nfce;
    assert(key_size <= MAX_NOTIF_KEY_SIZE);
    ITERATE_GLTHREAD_BEGIN(&nfc->notif_chain_head, itr)
    {
        nfce = GLTHREAD_GLUE_TO_NOTIF_CHAIN_NODE_ADDR(itr);
        if (!(key && key_size && nfce->is_key_set && (key_size == nfce->key_size)))
        {
            nfce->app_cb(arg, arg_size, nfc_op_code, nfce->subs_id);
        }
        else
        {
            if (memcmp(key, nfce->key, key_size) == 0)
            {
                nfce->app_cb(arg, arg_size, nfc_op_code, nfce->subs_id);
            }
        }
    }
    ITERATE_GLTHREAD_END()
}

notif_chain_t *
nfc_create_new_notif_chain(char *notif_chain_name)
{
    notif_chain_t *ptr = (notif_chain_t *)calloc(1, sizeof(notif_chain_t));
    strcpy(ptr->nfc_name, notif_chain_name);
    init_glthread(ptr);
    return ptr;
}

void nfc_delete_all_nfce(notif_chain_t *nfc)
{
    notif_chain_elem_t *nfce = NULL;
    glthread_t *itr = NULL;
    ITERATE_GLTHREAD_BEGIN(&nfc->notif_chain_head, itr)
    {
        nfce = GLTHREAD_GLUE_TO_NOTIF_CHAIN_NODE_ADDR(itr);
        remove_glthread(&nfce->glue);
        free(nfce);
    }
    ITERATE_GLTHREAD_END()
    nfc->notif_chain_head.next = NULL;
}
