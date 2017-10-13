
#include <stdio.h>
#include "cache.h"

void test1() {
    struct cache_t cache;
    cache_init(&cache);
    cache_print(&cache);
    
    struct slice_t slice;
    slice.offset = 0;
    slice.length = 10;
    slice.data = NULL;

    cache_put(&cache, &slice);
    cache_print(&cache);
    
    printf("total_length: %zd\n", cache_total_length(&cache));
    printf("consecutive_length: %zd\n", cache_consecutive_length(&cache));

    struct cache_t result;
    cache_consecutive_get(&cache, &result); 
    cache_print(&result);
    printf("\n");
    cache_print(&cache);
    
    printf("total_length: %zd\n", cache_total_length(&cache));
    printf("consecutive_length: %zd\n", cache_consecutive_length(&cache));
}

void test2() {
    struct cache_t cache;
    cache_init(&cache);
    cache_print(&cache);
    
    printf("total_length: %zd\n", cache_total_length(&cache));
    printf("consecutive_length: %zd\n", cache_consecutive_length(&cache));

    struct cache_t result;
    cache_consecutive_get(&cache, &result); 
    cache_print(&result);
    printf("\n");
    cache_print(&cache);
    
    printf("total_length: %zd\n", cache_total_length(&cache));
    printf("consecutive_length: %zd\n", cache_consecutive_length(&cache));
}

void test3() {
    struct cache_t cache;
    cache_init(&cache);
    cache_print(&cache);
    
    printf("total_length: %zd\n", cache_total_length(&cache));
    printf("consecutive_length: %zd\n", cache_consecutive_length(&cache));
    
    struct slice_t slice1;
    slice1.offset = 0;
    slice1.length = 10;
    slice1.data = NULL;
    cache_put(&cache, &slice1);
    
    struct slice_t slice2;
    slice2.offset = 10;
    slice2.length = 10;
    slice2.data = NULL;
    cache_put(&cache, &slice2);
    
    struct slice_t slice3;
    slice3.offset = 20;
    slice3.length = 10;
    slice3.data = NULL;
    cache_put(&cache, &slice3);
    
    printf("total_length: %zd\n", cache_total_length(&cache));
    printf("consecutive_length: %zd\n", cache_consecutive_length(&cache));

    struct cache_t result;
    cache_consecutive_get(&cache, &result); 
    cache_print(&result);
    printf("\n");
    cache_print(&cache);
    
    printf("total_length: %zd\n", cache_total_length(&cache));
    printf("consecutive_length: %zd\n", cache_consecutive_length(&cache));
}

int main() {
    test3();

    return 0;
}
