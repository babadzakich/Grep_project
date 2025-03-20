Implementation of grep linux utility in C using aho-corassic algorithm.

To start using you need to use commande line.

1. Build project using Make.
2. In command line type "./grep pattern1 pattern2 ..."
3. Inputfile comes from stdin.
4. After using grep the result of searching is printed in stdout.
5. Common use-case: cat input.txt | ./grep <pattern1> <pattern2> ... <patternN> >> output.txt
