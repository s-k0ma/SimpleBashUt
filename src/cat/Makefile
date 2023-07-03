CC=gcc
CFLAGS=-Wall -Werror -Wextra -g

.PHONY: clean uninstall s21_cat cformat

cat.o: cat.c cat.h
	$(CC) $(CFLAGS) -c -o cat.o cat.c

system.o: ../common/system.c ../common/system.h
	$(CC) $(CFLAGS) -c -o system.o ../common/system.c

s21_cat: uninstall cat.o system.o
	$(CC) $(CFLAGS) cat.o system.o -o s21_cat

clean:
	rm -rf *.o

uninstall:
	rm -rf *.o s21_cat

copycform:
	cp ../../materials/linters/.clang-format .clang-format

cformat: copycform
	clang-format -n *.c *.h ../common/*.c ../common/*.h
