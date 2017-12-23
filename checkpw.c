#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <openssl/sha.h>

static int cmp(const void *a, const void *b)
{
    return memcmp(a, b, 20);
}

int main(void)
{
    int fd = open("pwned-passwords.bin", O_RDONLY);
    if (fd < 0) {
        perror("fstat");
        abort();
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("fstat");
        abort();
    }

    if (st.st_size % 20 != 0) {
        fprintf(stderr, "Size not a multiple of 20: %lu\n", (unsigned long) st.st_size);
        abort();
    }

    size_t count = st.st_size / 20;

    unsigned char *buf = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (buf == MAP_FAILED) {
        perror("mmap");
        abort();
    }

    char plain[256];
    if (!fgets(plain, sizeof plain, stdin)) {
        perror("fgets");
        abort();
    }

    size_t plen = strlen(plain);
    if (plen == 0) {
        fprintf(stderr, "String empty\n");
        abort();
    }
    if (plain[plen - 1] != '\n') {
        fprintf(stderr, "No newline suffix\n");
        abort();
    }

    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, plain, plen - 1);
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1_Final(hash, &ctx);

    printf("%s\n",
        bsearch(hash, buf, count, 20, cmp)
        ? "Found"
        : "Not found"
    );
}
