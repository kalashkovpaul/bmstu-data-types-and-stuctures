CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wpedantic -Wextra -Iinc -g3
.PHONY = clean

app.exe: out/app.o out/menu.o out/print_list.o out/read_list.o out/add_element.o out/delete_element.o out/find_element.o out/sort_list.o
	$(CC) -o $@ $^

out/app.o: src/main.c inc/constants.h inc/menu.h inc/book.h 
	$(CC) $(CFLAGS) -o $@ -c $<

out/menu.o: src/menu.c inc/constants.h inc/book.h inc/print_list.h inc/read_list.h inc/delete_element.h inc/sort_list.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/print_list.o: src/print_list.c inc/book.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/read_list.o: src/read_list.c inc/book.h inc/constants.h inc/read_list.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/add_element.o: src/add_element.c inc/book.h inc/constants.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/delete_element.o: src/delete_element.c inc/book.h inc/constants.h inc/read_list.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/find_element.o: src/find_element.c inc/book.h inc/constants.h inc/print_list.h inc/read_list.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/sort_list.o: src/sort_list.c inc/book.h inc/constants.h inc/print_list.h
	$(CC) $(CFLAGS) -o $@ -c $<

create_list.exe: out/create_list.o
	$(CC) -o $@ $^

out/create_list.o: src/create_list.c inc/book.h inc/constants.h
	$(CC) $(CFLAGS) -o $@ -c $<

timer.exe: out/timer.o out/read_list.o
	$(CC) -o $@ $^

out/timer.o: src/timer.c inc/constants.h inc/read_list.h inc/book.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm out/*.o