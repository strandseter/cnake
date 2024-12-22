CC = gcc
CFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
SNAKE_SRCS = main.c
INTRO_SRCS = intro.c
SNAKE_TARGET = snake
INTRO_TARGET = intro

all: $(SNAKE_TARGET) $(INTRO_TARGET)

$(SNAKE_TARGET): $(SNAKE_SRCS)
	$(CC) -o $(SNAKE_TARGET) $(SNAKE_SRCS) $(CFLAGS)

$(INTRO_TARGET): $(INTRO_SRCS)
	$(CC) -o $(INTRO_TARGET) $(INTRO_SRCS) $(CFLAGS)

run-snake: $(SNAKE_TARGET)
	./$(SNAKE_TARGET)

run-intro: $(INTRO_TARGET)
	./$(INTRO_TARGET)

clean:
	rm -f $(SNAKE_TARGET) $(INTRO_TARGET)

leaks-snake: $(SNAKE_TARGET)
	leaks --atExit -- ./$(SNAKE_TARGET)

leaks-intro: $(INTRO_TARGET)
	leaks --atExit -- ./$(INTRO_TARGET)
