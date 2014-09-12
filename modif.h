#ifndef MODIF_H
#define MODIF_H
#include <gtk/gtk.h>
gboolean modifAdd(gpointer call , GtkWidget* parent);
gboolean modifEdi(GtkWidget* , gpointer);
gboolean modifDel(GtkWidget* , gpointer);
//! saat applikasi mati panggil ini
void modifQuit();
#endif

