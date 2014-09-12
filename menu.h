#ifndef MENU_H
#define MENU_H
#include <gtk/gtk.h>
GtkWidget* menuGetMenuBar(GtkWidget *parent);
void menuEvent(GtkWidget *parent);
gboolean menuIsWibShow();
void menuToggleJam();
#endif

