#include <stdio.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus.h>

gboolean callback()
{
	g_print ("This is a test!\n");
	return TRUE;
}

int main(int argc, char **argv)
{
  GMainLoop *loop = NULL;

	loop = g_main_loop_new (NULL, FALSE);
  
	g_timeout_add(1000, callback, NULL);

	g_main_loop_run (loop);

  return 0;
}
