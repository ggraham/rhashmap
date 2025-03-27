/*
 * Copyright (c) 2017 Mindaugas Rasiukevicius <rmind at noxt eu>
 * All rights reserved.
 *
 * Use is subject to license terms, as specified in the LICENSE file.
 */

#ifndef _RHASHMAP_H_
#define _RHASHMAP_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>
#include <assert.h>

#define	RHM_NOCOPY		0x01
#define	RHM_NONCRYPTO		0x02
#define RHM_RAPIDHASH       0x04


__BEGIN_DECLS

typedef struct {
	void *		key;
	void *		val;
	uint64_t	hash	: 32;
	uint64_t	psl	: 16;
	uint64_t	len	: 16;
} rh_bucket_t;

typedef struct rhashmap {
	unsigned	size;
	unsigned	nitems;
	unsigned	flags;
	unsigned	minsize;
	uint64_t	divinfo;
	rh_bucket_t *	buckets;
	uint64_t	hashkey;

	/*
	 * Small optimisation for a single element case: allocate one
	 * bucket together with the hashmap structure -- it will generally
	 * fit within the same cache-line.
	 */
	rh_bucket_t	init_bucket;
} rhashmap_t;

rhashmap_t *	rhashmap_create(size_t, unsigned);
void		rhashmap_destroy(rhashmap_t *);

void *		rhashmap_get(rhashmap_t *, const void *, size_t);
void *		rhashmap_put(rhashmap_t *, const void *, size_t, void *);
void *		rhashmap_del(rhashmap_t *, const void *, size_t);

#define	RHM_WALK_BEGIN		((uintmax_t)0)

void *		rhashmap_walk(rhashmap_t *, uintmax_t *, size_t *, void **);

__END_DECLS

#endif
