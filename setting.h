#ifndef SETTING_H
#define SETTING_H
//! file ini berhubungan dengan setting aaplikasi sat mati dan hidup
#include <gtk/gtk.h>
gboolean 	settingCreate();
gboolean 	settingQuit(GtkWidget*);
void	 	settingGetSize(int*,int*);
void		settingGetPos(int*,int*);
void 		settingSetSize(int,int);
void 		settingSetPos(int,int);
void 		settingResizeWidget(GtkWidget*,const char*);
void 		settingSaveWidget(GtkWidget*,const gint	);

#endif

