CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wfloat-equal -Wpedantic -Wextra -Iinc -g3
.PHONY = clean

app.exe: out/main.o out/actions.o out/node.o out/graph.o
	$(CC) -o $@ $^

out/main.o: src/main.c inc/constants.h inc/actions.h inc/node.h inc/graph.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/actions.o: src/actions.c inc/constants.h inc/actions.h inc/node.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/node.o: src/node.c inc/constants.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/graph.o: src/graph.c inc/constants.h inc/graph.h inc/node.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm out/*.o
