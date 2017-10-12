
#include <stdio.h>
#include "cache.h"

int main() {

    struct cache_t cache;
    cache_init(&cache);
    cache_print(&cache);
    
    struct slice_t slice1;
    slice1.offset = 0;
    slice1.length = 10;
    slice1.data = NULL;

    cache_put(&cache, &slice1);
    cache_print(&cache);

    struct slice_t slice2;
    slice2.offset = 2;
    slice2.length = 11;
    slice2.data = NULL;
    
    cache_put(&cache, &slice2);
    cache_print(&cache);
    
    struct slice_t slice3;
    slice3.offset = 5;
    slice3.length = 17;
    slice3.data = NULL;
    
    cache_put(&cache, &slice3);
    cache_print(&cache);
    
    struct slice_t slice4;
    slice4.offset = 100;
    slice4.length = 2;
    slice4.data = NULL;
    
    cache_put(&cache, &slice4);
    cache_print(&cache);
    
    struct slice_t slice5;
    slice5.offset = 102;
    slice5.length = 3;
    slice5.data = NULL;
    
    cache_put(&cache, &slice5);
    cache_print(&cache);

    printf("total_length: %zd\n", cache_total_length(&cache));
    printf("consecutive_length: %zd\n", cache_consecutive_length(&cache));

    struct cache_t result1;
    cache_consecutive_get(&cache, &result1); 
    cache_print(&result1);
    cache_print(&cache);
    
    printf("total_length: %zd\n", cache_total_length(&cache));
    printf("consecutive_length: %zd\n", cache_consecutive_length(&cache));
    
    struct cache_t result2;
    cache_consecutive_get(&cache, &result2); 
    cache_print(&result2);
    cache_print(&cache);

    return 0;
}
