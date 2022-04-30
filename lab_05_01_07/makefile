CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wpedantic -Wextra -Iinc -g3
.PHONY = clean

app.exe: out/main.o out/menu.o out/actions.o out/queue.o
	$(CC) -o $@ $^

out/main.o: src/main.c inc/constants.h inc/menu.h inc/queue.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/menu.o: src/menu.c inc/constants.h inc/actions.h inc/queue.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/actions.o: src/actions.c inc/constants.h inc/menu.h inc/queue.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/queue.o: src/queue.c inc/queue.h inc/constants.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm out/*.o