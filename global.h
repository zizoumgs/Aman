#ifndef GLOBAL_H
#define GLOBAL_H
#include <gtk/gtk.h>
//! yang di bawah ini ada di file main
typedef struct _parent {
  GtkWidget *window;
  gboolean appReady;
}parent_;
gboolean mainQuit();
// hanya pemesanan
parent_ *parent;
//! yang ini berada di global.c
//gchar *name = g_strdup_printf ("%s %s", *fname, *sname);
#define count(a) 		sizeof(a)/sizeof(*a) 
#define struct_new(x) 	g_malloc (sizeof (x))
gchar globalGetListHari(gchar **text	);
gchar *globalConIntToStr(gint value);

gint globalConStrToInt(gchar *text);
gfloat globalConStrToFlo(gchar *text);

void globalShowError(GtkWidget *widget, gpointer window,const gchar *pesan);
GtkWidget* globalGetParent();
gchar *globalPutZeroToWkt( gint);
GtkWidget *globalGetSimpleQues(GtkWidget *,char*,char*);
gchar *globalGetAppName();
gchar *globalGetVersion();
gchar *globalGetAppNameNVersion();
void globalSetCurrentIndexCombo(GtkWidget*,gchar*);
gchar* globalGetDefCom();
GdkPixbuf *globalCreateIcon(const gchar *);
void globalShowAbout(GtkWidget *, gpointer);
gchar *globalGetCurDir();
void globalSetGtkrc(const gchar*);
void globalAddGValue(GValue *val , GType type,gchar* text , gboolean changeType);

gboolean globalIsAppReady();
void globalSetAppReady(gboolean status);
void globalCreate();
#endif



