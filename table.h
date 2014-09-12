#ifndef TABLE_H
#define TABLE_H
#include <gtk/gtk.h>
GtkWidget* table_create();
void tableEvent(GtkWidget* parent);
void table_on_changed(GtkWidget *widget, gpointer label);
void tableTestMemLeak();
void tableEdiData(GtkWidget*,gpointer);
void tableDelData(GtkWidget*,gpointer);
void tableAddData(GtkWidget*,gpointer);
gboolean tableChangeHari(GtkWidget*, gpointer);
#endif

