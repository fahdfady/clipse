CC := gcc
CFLAGS := -Wall -Wextra -Oz -pedantic -fsanitize=address -ggdb
TARGET := a.out
EXAMPLE_OBJS := example/main.o example/sum.o

.PHONY: all run clean

all: $(TARGET) $(EXAMPLE_OBJS)

$(TARGET): main.c
	$(CC) $(CFLAGS) $< -o $@

example/%.o: example/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) $(EXAMPLE_OBJS)

clean:
	rm -f $(TARGET) $(EXAMPLE_OBJS)
