#ifndef ALARM_H
#define ALARM_H
#include <gtk/gtk.h>
void alarmCreate(GtkWidget*);
void alarmQuit();
void alarmTimer(gint);
void alarmUpdateListWis();
void alarmUpdateList();
#endif
