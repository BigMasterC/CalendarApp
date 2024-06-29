CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all -Wextra

#ALL = all


# Target for building all executables
all: public01 public02 public03 public04 public05 student_tests

# Public tests targets
##################### PUBLIC TESTS: 1 ###########################
public01: public01.o calendar.o my_memory_checker_216.o
	$(CC) -o public01 public01.o calendar.o my_memory_checker_216.o 

public01.o: public01.c my_memory_checker_216.h calendar.h event.h
	$(CC) $(CFLAGS) -c public01.c
##################### PUBLIC TESTS: 2 ###########################
public02: public02.o calendar.o my_memory_checker_216.o
	$(CC) -o public02 public02.o calendar.o my_memory_checker_216.o 

public02.o: public02.c my_memory_checker_216.h calendar.h event.h
	$(CC) $(CFLAGS) -c public02.c
##################### PUBLIC TESTS: 3 ###########################
public03: public03.o calendar.o my_memory_checker_216.o
	$(CC) -o public03 public03.o calendar.o my_memory_checker_216.o 

public03.o: public03.c my_memory_checker_216.h calendar.h event.h
	$(CC) $(CFLAGS) -c public03.c
##################### PUBLIC TESTS: 4 ###########################
public04: public04.o calendar.o my_memory_checker_216.o
	$(CC) -o public04 public04.o calendar.o my_memory_checker_216.o 

public04.o: public04.c my_memory_checker_216.h calendar.h event.h
	$(CC) $(CFLAGS) -c public04.c
##################### PUBLIC TESTS: 5 ###########################
public05: public05.o calendar.o my_memory_checker_216.o
	$(CC) -o public05 public05.o calendar.o my_memory_checker_216.o 

public05.o: public05.c calendar.h event.h
	$(CC) $(CFLAGS) -c public05.c

#################### STUDENT TEST ###########################
student_tests: student_tests.o my_memory_checker_216.o
	gcc -o student_tests student_tests.o my_memory_checker_216.o calendar.o
# Object files
student_tests.o: student_tests.c calendar.h event.h
	$(CC) $(CFLAGS) -c student_tests.c -o student_tests.o

calendar.o: calendar.c calendar.h
	$(CC) $(CFLAGS) -c calendar.c -o calendar.o

my_memory_checker_216.o: my_memory_checker_216.c my_memory_checker_216.h
	$(CC) $(CFLAGS) -c my_memory_checker_216.c -o my_memory_checker_216.o

.PHONY: clean
# Clean target to remove object files and executables
clean:
	rm -f *.o public01 public02 public03 public04 public05 student_tests a.out
