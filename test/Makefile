all: test_dbus

test_dbus: main.c
	gcc -o $@ $< `pkg-config --cflags --libs dbus-1 dbus-glib-1`
clean:
	rm test_dbus
