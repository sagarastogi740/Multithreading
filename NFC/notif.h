#ifndef __NOTIF_H__
#define __NOTIF_H__

#include <stddef.h>
#include "../utils.h"
#include "glthread/glthread.h"

#define MAX_NOTIF_KEY_SIZE 64

#define GLTHREAD_GLUE_TO_NOTIF_CHAIN_NODE_ADDR(glthreadaddr) \
    GLTHREAD_NODE_ADDR(notif_chain_elem_t, glthreadaddr, glue)

typedef void (*nfc_app_cb_t)(void *, size_t, nfc_op_t, subscriber_id_t);

typedef struct notif_chain_elem_
{
    char key[MAX_NOTIF_KEY_SIZE];
    size_t key_size;
    subscriber_id_t subs_id;
    bool_t is_key_set;
    nfc_app_cb_t app_cb;
    glthread_t glue;
} notif_chain_elem_t;

typedef struct notif_chain_
{
    char nfc_name[64];
    glthread_t notif_chain_head;
} notif_chain_t;

typedef enum
{
    NFC_UNKNOWN,
    NFC_ADD,
    NFC_MOD,
    NFC_DEL,
} nfc_op_t;

void nfc_register_notif_chain(notif_chain_t *nfc,
                              notif_chain_elem_t *nfce);

void nfc_invoke_notif_chain(notif_chain_t *nfc,
                            void *arg,
                            size_t arg_size,
                            char *key,
                            size_t key_size,
                            nfc_op_t nfc_op_code);

notif_chain_t *
nfc_create_new_notif_chain(char *notif_chain_name);

void nfc_delete_all_nfce(notif_chain_t *nfc);

#endif /*__NOTIF_H__*/