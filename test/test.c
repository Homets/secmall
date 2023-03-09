#include <criterion/criterion.h>
#include <criterion/redirect.h>
#define _GNU_SOURCE
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "my_secmalloc.h"
#include "my_secmalloc_private.h"

Test(mmap, test_simple_mmap)
{
    printf("Ici on fait un test simple de mmap\n");
    void *ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    cr_expect(ptr != NULL);
    int res = munmap(ptr, 4096);
    cr_expect(res == 0);
    //char *str = my_malloc(15);
    //strncpy(str, "ca marche", 15);
    //printf("bla %s\n", str);
}


Test(log, test_log, .init=cr_redirect_stderr)
{   
    my_log("coucou %d\n",12);
    cr_assert_stderr_eq_str("coucou 12\n");

}

Test(metadata_pool, create_clean_metadata_pool)
{   
    void *ptr =  my_init_pool();
    cr_expect(ptr != NULL);
    int res = clean_metadata_pool(ptr);
    cr_expect(res == 0);

}