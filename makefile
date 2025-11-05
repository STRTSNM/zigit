CC = gcc
CFLAGS = -O2 -s
TARGET = zigit

all: $(TARGET)

$(TARGET): zigit.c
	$(CC) $(CFLAGS) zigit.c -o $(TARGET)

install: $(TARGET)
	sudo install -m 755 $(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	echo "run sudo rm -f /usr/local/bin/$(TARGET)"

clean:
	rm -f $(TARGET)
