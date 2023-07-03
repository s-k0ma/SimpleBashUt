CC=gcc
CFLAGS=-Wall -Werror -Wextra -g

.PHONY: clean uninstall s21_grep cformat

grep.o: grep.c grep.h
	$(CC) $(CFLAGS) -c -o grep.o grep.c

system.o: ../common/system.c ../common/system.h
	$(CC) $(CFLAGS) -c -o system.o ../common/system.c

s21_grep: uninstall system.o grep.o
	$(CC) $(CFLAGS) system.o grep.o -o s21_grep

clean:
	rm -rf *.o

uninstall:
	rm -rf *.o s21_grep

copycform:
	cp ../../materials/linters/.clang-format .clang-format 

cformat: copycform
	clang-format -n *.c *.h ../common/*.c ../common/*.h
