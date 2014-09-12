#ifndef SOUND_AMAN_H
#define SOUND_AMAN_H
#include <gst/gst.h>
/* Structure to contain all our information, so we can pass it around */
#define SOUNDBERJALAN GST_STATE_PLAYING
#define SOUNDSIAP  GST_STATE_READY 
#define SOUNDPAUSE  GST_STATE_PAUSED
typedef struct data_music {
	const gchar * file;
	gint totalLoop ;
	gint id ; 
} data_music_;

typedef struct _CustomData {
	GstElement *playbin2;           /* Our one and only pipeline */
	gulong slider_update_signal_id; /* Signal ID for the slider update signal */   
	GstState state;                 /* Current state of the pipeline */
	gint64 duration;                /* Duration of the clip, in nanoseconds */
	gint totalLoop ;
	data_music_ *data_music;
	const gchar * file;
} CustomData;

int soundTest(int argc, char *argv[], char* filePlay);
int soundCreate(int argc, char *argv[]);
int soundPlay(char * , int);
void soundStop (gpointer *button, CustomData * point);
int soundQuit();
CustomData *soundGetGStream();
//! call after gtk_main()
void soundFreeResource();
int soundGetStatus();
#endif

