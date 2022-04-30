CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wpedantic -Wextra -Iinc -g3
.PHONY = clean

app.exe: out/main.o out/actions.o out/avl_node.o out/bst_node.o out/node.o out/hash.o
	$(CC) -o $@ $^

out/main.o: src/main.c inc/constants.h inc/actions.h inc/avl_node.h inc/bst_node.h inc/node.h inc/hash.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/actions.o: src/actions.c inc/constants.h inc/actions.h inc/node.h inc/bst_node.h inc/avl_node.h inc/hash.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/avl_node.o: src/avl_node.c inc/constants.h inc/actions.h inc/avl_node.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/bst_node.o: src/bst_node.c inc/constants.h inc/actions.h inc/bst_node.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/node.o: src/node.c inc/constants.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/hash.o: src/hash.c inc/constants.h inc/actions.h inc/node.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm out/*.o
