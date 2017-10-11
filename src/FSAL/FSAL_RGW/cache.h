#ifndef FSAL_FSAL_RGW_CACHE_H
#define FSAL_FSAL_RGW_CACHE_H

#include <stdint.h>
#include "gsh_list.h"

struct slice_t {
    struct glist_head node;
    uint64_t offset;
    size_t length;
    void *data;
};

struct cache_t {
    uint64_t offset;
    struct glist_head head;
};

void cache_init(struct cache_t *cache);
void cache_put(struct cache_t *cache, struct slice_t slice);
int cache_empty(struct cache_t *cache);
size_t cache_total_length(struct cache_t *cache);
size_t cache_available_length(struct cache_t *cache);
struct cache_t cache_get(struct cache_t *cache);

#endif // FSAL_FSAL_RGW_CACHE_H
