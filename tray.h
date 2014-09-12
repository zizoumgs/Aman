#ifndef TRAY_AMAN_H
#define TRAY_AMAN_H
#include <gtk/gtk.h>
void trayTimer(GtkWidget* w);
GtkStatusIcon *trayCreateTrayIcon(GtkWidget* );
void trayTest(GtkStatusIcon *);
void trayMessageSend(const gchar* , gint);

#endif

