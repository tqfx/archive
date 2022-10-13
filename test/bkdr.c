#include "a/a.h"
#include <stdio.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
    for (int idx = 1; idx < argc; ++idx)
    {
        a_u32_t val = (a_u32_t)a_hash_bkdr(argv[idx], 0);
        printf("case 0x%08" PRIX32 ": // %s\n    break;\n", val, argv[idx]);
    }
    return 0;
}
