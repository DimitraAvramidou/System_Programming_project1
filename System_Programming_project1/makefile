all:minisearch trie.o


trie.o: trie.c
		gcc -c trie.c

minisearch:trie.h trie.o minisearch.c
			gcc -o minisearch trie.o minisearch.c
splint:
			splint trie.c minisearch.c

run:
			minisearch

clean:
				rm -f minisearch *.o
