CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wpedantic -Wextra -Iinc -g3
.PHONY = clean

app.exe: out/main.o out/menu.o out/actions.o out/stack_array.o out/stack_node.o
	$(CC) -o $@ $^

out/main.o: src/main.c inc/constants.h inc/menu.h inc/info.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/menu.o: src/menu.c inc/constants.h inc/info.h inc/actions.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/actions.o: src/actions.c inc/actions.h inc/stack_array.h inc/stack_node.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/stack_array.o: src/stack_array.c inc/stack_array.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/stack_node.o: src/stack_node.c inc/constants.h inc/stack_node.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm out/*.o