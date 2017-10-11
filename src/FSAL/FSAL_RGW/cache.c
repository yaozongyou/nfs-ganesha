#include "cache.h"

void cache_init(struct cache_t *cache) {
    cache->offset = 0;
    glist_init(&cache->head);
}

int slice_compare(struct glist_head *s1, struct glist_head *s2) {
    struct slice_t *node1 = glist_entry(s1, struct slice_t, node);
    struct slice_t *node2 = glist_entry(s2, struct slice_t, node);

    if (node1->offset == node2->offset) {
        return 0;
    } else if (node1->offset > node2->offset) {
        return 1;
    } else {
        return -1;
    }
}

void cache_put(struct cache_t *cache, struct slice_t slice) {
    glist_insert_sorted(&cache->head, &slice.node, slice_compare);
}

int cache_empty(struct cache_t *cache) {
    return glist_empty(&cache->head);
}

size_t cache_total_length(struct cache_t *cache) {
    size_t length = 0;
    struct glist_head *node = NULL;

    glist_for_each(node, &cache->head) {
        struct slice_t *slice = glist_entry(node, struct slice_t, node);
        length += slice->length;
    }
    return length;
}

size_t cache_available_length(struct cache_t *cache) {
    size_t length = 0;
    struct glist_head *node = NULL;
    uint64_t last_offset = cache->offset;

    glist_for_each(node, &cache->head) {
        struct slice_t *slice = glist_entry(node, struct slice_t, node);
        if ((slice->offset <= last_offset) && 
                (slice->offset + slice->length >= last_offset)) {
            last_offset = slice->offset;
            length += slice->length;
        } else {
            break;
        }
    }
    return length;
}

struct cache_t cache_get(struct cache_t *cache) {
    struct cache_t result;
    result.offset = cache->offset;
    glist_init(&result.head);
    
    uint64_t last_offset = cache->offset;
    struct glist_head *node = NULL;
    struct glist_head *noden = NULL;

    glist_for_each_safe(node, noden, &cache->head) {
        struct slice_t *slice = glist_entry(node, struct slice_t, node);
        if ((slice->offset <= last_offset) && 
                (slice->offset + slice->length >= last_offset)) {
            last_offset = slice->offset;
            cache->offset = slice->offset + slice->length;
        } else {
            break;
        }
    }

    if (node != NULL) {
        glist_split(&cache->head, &result.head, node);
        glist_swap_lists(&cache->head, &result.head);
        return result;
    }

    return result;
}
