gcc -c ahoCorassic.c -o first.o
gcc -c stringArray.c -o second.o
gcc -c grep.c -o grep.o
gcc grep.o first.o second.o -o grep
rm *.o