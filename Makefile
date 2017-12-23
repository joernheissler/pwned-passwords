all: hex2bin checkpw

hex2bin: hex2bin.c
	gcc -std=c99 -Wall -Werror -pedantic -Werror -O2 -o $@ $^

checkpw: checkpw.c
	gcc -std=c99 -Wall -Werror -pedantic -Werror -O2 -o $@ $^ `pkg-config --cflags --libs libcrypto`
