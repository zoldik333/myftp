##
## EPITECH PROJECT, 2024
## tekspice
## File description:
## Makefile
##

card=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call card,$d/,$2))

CC				:= gcc
CFLAGS 			:= -c -Wall
LDFLAGS 		:=
DEBUG_FLAGS		:= -g3
TESTS_FLAGS 	:= --coverage -lcriterion
INCLUDES 		:= -I./includes
EXECUTABLE 		:= myftp
TEST			:= tests

SOURCES_FILES 	:= $(call card,src/,*.c)
OBJECTS_FILES 	:= $(SOURCES_FILES:.c=.o)

SOURCES_LIB_FILES 	:= $(call card,lib/,*.c)
OBJECTS_LIB_FILES 	:= $(SOURCES_LIB_FILES:.c=.o)

SOURCES_TESTS_FILES 	:= $(call card,src/,*.c)
SOURCES_TESTS_FILES		:= $(SOURCES_TESTS_FILES) $(call card,$(TEST)/,*.c)
SOURCES_TESTS_FILES		:= $(SOURCES_TESTS_FILES) $(call card,lib/,*.c)
SOURCES_TESTS_FILES 	:= $(filter-out src/main.c,$(SOURCES_TESTS_FILES))

OBJECTS_TESTS_FILES 	:= $(SOURCES_TESTS_FILES:.c=.o)

GCNO_FILES 		:= $(call card,./,*.gcno)
GCDA_FILES 		:= $(call card,./,*.gcda)

all: $(SOURCES_FILES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_FILES) $(OBJECTS_LIB_FILES)
	$(CC) $(LDFLAGS) $(OBJECTS_FILES) $(OBJECTS_LIB_FILES) -o $@

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJECTS_FILES)
	rm -f $(OBJECTS_LIB_FILES)

fclean: clean clean_tests
	rm -f $(EXECUTABLE)
	rm -f test_$(EXECUTABLE)

clean_tests:
	rm -f $(GCNO_FILES)
	rm -f $(GCDA_FILES)
	rm -f $(OBJECTS_TESTS_FILES)

tests_run: CFLAGS += $(TESTS_FLAGS)
tests_run: clean_tests $(SOURCES_TESTS_FILES) $(OBJECTS_TESTS_FILES)
	$(CC) $(TESTS_FLAGS) $(INCLUDES) $(OBJECTS_TESTS_FILES)\
	 -o test_$(EXECUTABLE); ./test_$(EXECUTABLE);

coverage:
	gcovr -e tests -e lib

debug: LDFLAGS += $(DEBUG_FLAGS)
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean clean_tests tests_run coverage debug re
