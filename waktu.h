#ifndef WAKTU_H
#define WAKTU_H
/**
 * Sangat di butuhkan oleh alarm.h dan child.h
 * 				________waktu________
 * 				|					|
 * 			  alarm			  	  child
**/
#include <gtk/gtk.h>
#include <time.h>
gchar * waktuGet( gboolean wib );
gchar * waktuGetIstiwak(gboolean);
gchar * waktuGetWib(gboolean);
void waktuCreate(GtkWidget*);
void waktuQuit();
void waktuTimer(GtkWidget*);
gint * 	waktuGetWis();
gint 	waktuGetHari(); 
gchar * waktuGetTanggal();
#endif

