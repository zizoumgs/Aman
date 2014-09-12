#include <stdbool.h>
#include "sound.h"
//! pakai global data , siapa takut
CustomData data;


static void play_uri(const char *uri);
CustomData *soundGetGStream(){
	return &data;
}
static void soundError(GstBus *bus, GstMessage *msg, CustomData *data){
	GError *err;
	gchar *debug_info;
   
	/* Print error details on the screen */
	gst_message_parse_error (msg, &err, &debug_info);
	g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
	g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
	g_clear_error (&err);
	g_free (debug_info);
   
	/* Set the pipeline to READY (which stops playback) */
	gst_element_set_state (data->playbin2, GST_STATE_READY);
}
//! eos
static void soundEos(GstBus *bus, GstMessage *msg, CustomData *data){
	data->totalLoop--;
	if(data->totalLoop<=0){
		g_message("Selesai");
   		soundStop(NULL,data);
	}
	else{
   		g_message("lagi");
   		soundStop(NULL,data);
   		play_uri(data->file);
	}
}
//!This function is called when the pipeline changes states. We use it to
//! keep track of the current state.
static void soundStateChanged (GstBus *bus, GstMessage *msg, CustomData *data) {
	GstState old_state, new_state, pending_state;
	gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
	if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data->playbin2)) {
		data->state = new_state;
		g_print ("State set to %s\n", gst_element_state_get_name (new_state));
		if (old_state == GST_STATE_READY && new_state == GST_STATE_PAUSED) {
		}
	}
}
int soundGetStatus(){
	return data.state	;
}
/* This function is called when new metadata is discovered in the stream */
static void tags_cb (GstElement *playbin2, gint stream, CustomData *data) {
	//!We are possibly in a GStreamer working thread, so we notify the main
	//!thread of this event through a message in the bus
	gst_element_post_message (playbin2,gst_message_new_application (GST_OBJECT (playbin2),gst_structure_new ("tags-changed", NULL)));
}
//! This function is called when the STOP button is clicked
void soundStop (gpointer *button, CustomData *data) {
	gst_element_set_state (data->playbin2, GST_STATE_READY);
}
//! sementara useless
static void analyze_streams(CustomData *data){
	gint i;
	GstTagList *tags;
	gchar *str, *total_str;
	guint rate;
	gint n_audio;
	//! read property
	g_object_get (data->playbin2, "n-audio", &n_audio, NULL);
	for (i = 0; i < n_audio; i++) {
		tags = NULL;
		//! Retrieve the stream's audio tags 
		g_signal_emit_by_name (data->playbin2, "get-audio-tags", i, &tags);
		if (tags) {
			total_str = g_strdup_printf ("\naudio stream %d:\n", i);
//			gtk_text_buffer_insert_at_cursor (text, total_str, -1);
			g_free (total_str);
			if (gst_tag_list_get_string (tags, GST_TAG_AUDIO_CODEC, &str)) {
				total_str = g_strdup_printf ("  codec: %s\n", str);
//				gtk_text_buffer_insert_at_cursor (text, total_str, -1);
				g_free (total_str);
				g_free (str);
			}
			if (gst_tag_list_get_string (tags, GST_TAG_LANGUAGE_CODE, &str)) {
				total_str = g_strdup_printf ("  language: %s\n", str);
//				gtk_text_buffer_insert_at_cursor (text, total_str, -1);
				g_free (total_str);
				g_free (str);
			}
			if (gst_tag_list_get_uint (tags, GST_TAG_BITRATE, &rate)) {
				total_str = g_strdup_printf ("  bitrate: %d\n", rate);
//				gtk_text_buffer_insert_at_cursor (text, total_str, -1);
				g_free (total_str);
			}	
			gst_tag_list_free (tags);
		}
	}
}
//! sementara useless 
static void application_cb (GstBus *bus, GstMessage *msg, CustomData *data) {
	if (g_strcmp0 (gst_structure_get_name (msg->structure), "tags-changed") == 0) {
		analyze_streams (data);
	}
}
//! pla
static void play_uri(const char *uri){
    if (uri){
	    g_object_set(G_OBJECT(data.playbin2), "uri", uri, NULL);
		int ret = gst_element_set_state(GST_ELEMENT(data.playbin2), GST_STATE_PLAYING);
		if(ret == GST_STATE_CHANGE_FAILURE){
			g_message("GAGAL");
		}
	}
}
//! use for testing
int soundTest(int argc, char *argv[] , char* filePlay){
//	soundTest(&argc, &argv, argv[1]);
	gst_init(&argc, &argv);
    play_uri(filePlay);
}
int soundCreate(int argc, char *argv[]){
	/* Initialize our data structure */
	memset (&data, 0, sizeof (data));	
	gst_init(&argc, &argv);	
    GstBus *bus;
    data.playbin2 = gst_element_factory_make("playbin", "player");
	if (!data.playbin2) {
		g_printerr ("Not all elements could be created.\n");
		return;
	}
	/* Connect to interesting signals in playbin2 */
//	g_signal_connect (G_OBJECT (data.playbin2), "video-tags-changed", (GCallback) tags_cb, &data);
//	g_signal_connect (G_OBJECT (data.playbin2), "audio-tags-changed", (GCallback) tags_cb, &data);
//	g_signal_connect (G_OBJECT (data.playbin2), "text-tags-changed", (GCallback) tags_cb, &data);


	//! Instruct the bus to emit signals for each received message, and connect to the interesting signals
	bus = gst_element_get_bus (data.playbin2);
	gst_bus_add_signal_watch (bus);
	//! untuk yang otomatis memanggil
//	gst_bus_add_watch(bus, bus_call, NULL);
	g_signal_connect (G_OBJECT (bus), "message::error"				, (GCallback)soundError, &data);
	g_signal_connect (G_OBJECT (bus), "message::eos"				, (GCallback)soundEos, &data);
	g_signal_connect (G_OBJECT (bus), "message::state-changed"		, (GCallback)soundStateChanged, &data);
//	g_signal_connect (G_OBJECT (bus), "message::application"		, (GCallback)application_cb, &data);
	gst_object_unref (bus);
	return 0;
}
//! untuk menghidupkan sound
int soundPlay(char * filePlay , int totalPlay){
	char* file = g_strdup_printf ("%s/music/%s",g_get_current_dir (), filePlay ); 	
	if(  ! g_file_test (file,G_FILE_TEST_EXISTS | G_FILE_TEST_IS_DIR)  ){
		char* file_2 = g_strdup_printf ("File tidak di temukan! %s/music/%s",g_get_current_dir (), filePlay ); 	
		globalShowError(NULL,NULL,file_2);
		g_free(file);
		g_free(file_2	);
		return;
	}
	g_free(file);
	data.file = g_strdup_printf ("file:%s/music/%s",g_get_current_dir (), filePlay ); 	
	data.totalLoop = totalPlay;
    play_uri(data.file);
    return 0;
}
//! panggil ini ketika applikasi keluar 
int soundQuit(){
	soundStop(NULL,&data);
	return 0;
}
//! ini harus ditempatkan di tempat khusus
void soundFreeResource(){
	//! Free resources
	gst_element_set_state (data.playbin2, GST_STATE_NULL);
	gst_object_unref (data.playbin2);	
}

/**
	(1) make
	(2) ./main "file:/home/sas/sound/Alarm.mp3"
	Note:
	(1) pastikan linux sudah bisa memainkan mp3
	(2) pastikan file ada!
**/
