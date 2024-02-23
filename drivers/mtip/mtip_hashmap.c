//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/init.h>

#include "mtip_hashmap.h"

static struct mtip_hashmap_struct mtip_hashmap;

static u32 mtip_hashmap_hash_function(u32 key)
{
    return key%MTIP_HASHMAP_HASH;
}

// go through the hashmap and find index if key exists
static int mtip_hashmap_find_key(u32 key)
{
    int i = 0;
    int ret = 0;
    u32 index = mtip_hashmap_hash_function(key);
    for (i = 0; i < MTIP_HASHMAP_TABLE_SIZE; ++i) {
        index = (index + i)%MTIP_HASHMAP_TABLE_SIZE;
        if (mtip_hashmap.key[index] == key) {
            // found the key
            ret = index;
            break;
        }
        else if (mtip_hashmap.key[index] == MTIP_HASHMAP_EMPTY) {
            ret = -1;
            break;
        }
    }
    return ret;
}

// Initialize the hashmap
int mtip_hashmap_initialize(void)
{
    int i;

    for (i = 0; i < MTIP_HASHMAP_TABLE_SIZE; ++i) {
        mtip_hashmap.key[i] = MTIP_HASHMAP_EMPTY;
        mtip_hashmap.value[i] = 0;
    }
    return 0;
}

// cleanup the hashmap
int mtip_hashmap_destroy(void)
{
    // cleanup here
    return 0;
}

// insert a key, value pair into the map
int mtip_hashmap_insert(u32 key, u32 value)
{
    int i;
    bool inserted = false;
    int ret = 0;
    int index;
    u32 hashed_index;

    // first check if the key is already in the map
    index = mtip_hashmap_find_key(key);

    if (index < 0) {
        // did not find the key in the map
        // add the key/value pair
        hashed_index = mtip_hashmap_hash_function(key);
        for (i = 0; i < MTIP_HASHMAP_TABLE_SIZE; ++i) {
            index = (hashed_index + i)%MTIP_HASHMAP_TABLE_SIZE;
            if ((mtip_hashmap.key[index] == MTIP_HASHMAP_EMPTY) || (mtip_hashmap.key[index] == MTIP_HASHMAP_DELETED)) {
                mtip_hashmap.key[index] = key;
                mtip_hashmap.value[index] = value;
                inserted = true;
                break;
            }
        }
    }
    else
    {
        mtip_hashmap.value[index] = value;
        mtip_hashmap.key[index] = key;
        inserted = true;
    }

    if (inserted == false) {
        ret = -1;
    }

    return ret;
}

// remove a key, value pair from the map
int mtip_hashmap_remove(u32 key)
{
    int ret = 0;
    int index;

    // first check if the key is already in the map
    index = mtip_hashmap_find_key(key);

    if (index >= 0) {
        mtip_hashmap.key[index] = MTIP_HASHMAP_DELETED;
        ret = 0;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

// find the value using key
int mtip_hashmap_find(u32 key, u32* value)
{
    int ret = 0;
    int index;

    // first check if the key is already in the map
    index = mtip_hashmap_find_key(key);

    if (index < 0) {
        // did not find the key in the map
        ret = -1;
    }
    else
    {
        *value = mtip_hashmap.value[index];
        ret = 0;
    }

    return ret;
}


