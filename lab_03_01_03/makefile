CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wpedantic -Wextra -Iinc -g3
.PHONY = clean

app.exe: out/app.o out/menu.o out/matrix.o out/node.o
	$(CC) -o $@ $^

out/app.o: src/main.c inc/constants.h inc/menu.h inc/matrix.h inc/info.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/menu.o: src/menu.c inc/constants.h inc/matrix.h inc/node.h inc/info.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/matrix.o: src/matrix.c inc/constants.h inc/node.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/node.o: src/node.c inc/node.h
	$(CC) $(CFLAGS) -o $@ -c $<

generate_matrix.exe: out/generate_matrix.o
	$(CC) -o $@ $^

out/generate_matrix.o: src/generate_matrix.c
	$(CC) $(CFLAGS) -o $@ -c $<

generate_column.exe: out/generate_column.o
	$(CC) -o $@ $^

out/generate_column.o: src/generate_column.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm out/*.o