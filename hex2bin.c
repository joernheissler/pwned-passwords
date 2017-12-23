#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char line[64];
    unsigned char buf[20];
    unsigned char h2i[256];

    for (int i = 0; i < 256; ++i) {
        h2i[i] = -1;
    }
    h2i['0'] = 0;
    h2i['1'] = 1;
    h2i['2'] = 2;
    h2i['3'] = 3;
    h2i['4'] = 4;
    h2i['5'] = 5;
    h2i['6'] = 6;
    h2i['7'] = 7;
    h2i['8'] = 8;
    h2i['9'] = 9;
    h2i['A'] = 10;
    h2i['B'] = 11;
    h2i['C'] = 12;
    h2i['D'] = 13;
    h2i['E'] = 14;
    h2i['F'] = 15;

    while (fgets(line, sizeof line, stdin)) {
        char *p = line;
        unsigned char *b = buf;
        for (int i = 0; i < 20; ++i) {
            if (h2i[(unsigned char)p[0]] == (unsigned char) -1) {
                abort();
            }
            if (h2i[(unsigned char)p[1]] == (unsigned char) -1) {
                abort();
            }
            *b++ = h2i[(unsigned char)p[0]] << 4 | h2i[(unsigned char)p[1]];
            p += 2;
        }
        if (*p != '\r') abort();
        fwrite(buf, sizeof buf, 1, stdout);
    }
}
