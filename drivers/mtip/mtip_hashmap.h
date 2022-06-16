//SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */ 

#ifndef _MTIP_HASHMAP_H
#define _MTIP_HASHMAP_H

#include <linux/slab.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>

#define MTIP_HASHMAP_TABLE_SIZE   16  // the maximum number of concurrent key/value pairs in use
#define MTIP_HASHMAP_HASH         17  // use a prime number greater than size

#define MTIP_HASHMAP_EMPTY        -1
#define MTIP_HASHMAP_DELETED      -2

/* 
 The mtip_hashmap structure 
 */ 
struct mtip_hashmap_struct
{
   int key[MTIP_HASHMAP_TABLE_SIZE];
   u32 value[MTIP_HASHMAP_TABLE_SIZE];
   spinlock_t lock;
};

int mtip_hashmap_initialize(void);
int mtip_hashmap_destroy(void);
int mtip_hashmap_insert(u32 key, u32 value);
int mtip_hashmap_remove(u32 key);
int mtip_hashmap_find(u32 key, u32* value);

#endif // _MTIP_HASHMAP_H
