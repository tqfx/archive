#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

static uint32_t lhash(const void *s)
{
    uint32_t x = 0;
    for (const unsigned char *p = (const unsigned char *)s; *p && *p != '\n'; ++p)
    {
        x = x * 131 + *p;
    }
    return x;
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        char buffer[BUFSIZ];
        FILE *in = fopen(argv[1], "r");
        FILE *out = fopen(argv[2], "wb");
        while (fgets(buffer, BUFSIZ, in))
        {
            fprintf(out, "case 0x%08" PRIX32 ": // %s    break;\n", lhash(buffer), buffer);
        }
        fclose(out);
        fclose(in);
    }
    return 0;
}
