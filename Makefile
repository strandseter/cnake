CC = gcc
CFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
SRCS = main.c
TARGET = build

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

leaks: $(TARGET)
	leaks --atExit -- ./$(TARGET)
