CC=gcc

CFLAGS=-Wall -Werror -Wextra -std=c11
#CFLAGS=
LIBS=-lcheck -lm -lsubunit 
DEV_LIBS=-lm

SOURCE_DIRS=matrix
SOURCE=$(wildcard s21*.c)
OBJECTS=$(SOURCE:.c=.o)

TEST_DIR=tests

LIB=s21_matrix.a

TEST_EXE=$(LIB:.a=_test)
PREV_TEST=test.txt

.PHONY: clean

all: $(LIB)

$(LIB): $(OBJECTS)
	ar r $@ $^
	ranlib $@

#$(OBJECTS): $(SOURCE)
#	$(CC) $(CFLAGS) -c -o $@ $< 

$(SOURCE_DIRS): $(LIB)
	$(CC) $(CFLAGS) -o $@ $(wildcard $(TEST_DIR)/*.c) $(wildcard $(TEST_DIR)/*/*.c) $(LIB) $(LIBS)  

test: $(LIB) $(SOURCE_DIRS)
	for test in $(SOURCE_DIRS); do ./$$test; done

clean:
	rm -f $(SOURCE_DIRS)
	rm -f $(OBJECTS) $(LIB)
	rm -f $(TEST_EXE) 
	rm -f *.gcov *.gcno *.gcda */*.gcov */*.gcno */*.gcda */*/*.gcov */*/*.gcno */*/*.gcda
	rm -f coverage.info
	rm -rf report

gcov_report: CFLAGS += -coverage
gcov_report: test
	gcov $(SOURCE)
	mkdir report
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory report

format:
	clang-format -i *.c */*/*.c 
	clang-format -n *.c */*/*.c 
	
leak_check: CFLAGS += -DVALGRIND
leak_check: clean $(LIB) $(SOURCE_DIRS)
	for test in $(SOURCE_DIRS); do CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$$test; done

dev_test: clean $(LIB)
	$(CC) test.c $(LIB) -o $(TEST_EXE) $(DEV_LIBS)
	@echo "============PREVIOUS=============="
	@cat $(PREV_TEST)
	@echo "=================================="
	@echo "============CURRENT==============="
	@./$(TEST_EXE) > $(PREV_TEST)
	@cat $(PREV_TEST)
	@echo "=================================="
