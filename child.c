//	#include <cairo.h>
#include "child.h"
#include "menu.h"
#include "waktu.h"
static gint height = 60 ;
//static char buffer[256];
static char *buffer;
static void childEvent(GtkWidget *drawArea,GtkWidget*);
static void chilGradient2(cairo_t*, GtkWidget*);
gboolean childOnDrawEvent(GtkWidget *widget, GdkEventExpose *event, gpointer data);
gboolean childOnClick(GtkWidget *widget, GdkEventButton *event, gpointer func_data)
{
	menuToggleJam();
	return TRUE;
}
GtkWidget* childCreate(GtkWidget* parent){
	GtkWidget *event_box;
	GtkWidget *b;
	event_box = gtk_event_box_new ();
	b = gtk_drawing_area_new();
	gtk_widget_add_events (b,GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK	);
	int width, height_;
	gtk_window_get_size(GTK_WINDOW(parent), &width, &height_);
	gtk_widget_set_size_request(b, width,height);
	
	childEvent(b,parent);
	return b;
}
static void childEvent(GtkWidget *drawArea,GtkWidget* parent){
	g_signal_connect(G_OBJECT(drawArea), "expose_event", G_CALLBACK(childOnDrawEvent), parent); 
	g_signal_connect(G_OBJECT(drawArea), "button_release_event",G_CALLBACK(childOnClick), NULL);

//	g_signal_connect(G_OBJECT(drawArea), "draw", G_CALLBACK(childOnDrawEvent), NULL); 
}
//! dipanggil otomatis melalui event di main.c
gboolean childOnDrawEvent(GtkWidget *widget, GdkEventExpose *event, gpointer data){
	cairo_t *cr;
	cr = gdk_cairo_create(widget->window);
//	cairo_move_to(cr, 30, 30);
	buffer = waktuGet(	menuIsWibShow()	);
	/*
	else{
		g_snprintf(buffer, sizeof(buffer), "%s WIS", istiwakGet(loctime));
	}
	*/
//	cairo_show_text(cr, buffer);
	chilGradient2(cr , data);
	cairo_destroy(cr);
	g_free(buffer);
	return FALSE;
}

static void chilGradient2(cairo_t* cr , GtkWidget* parent){
	cairo_text_extents_t extents;
	gint w, h;
	gtk_window_get_size(GTK_WINDOW(parent), &w, &h); 

	cairo_select_font_face(cr, "Courier",
	CAIRO_FONT_SLANT_NORMAL,
    CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 40);
	cairo_text_extents(cr, buffer, &extents);
	
	gint height_local= (height/2)+10;
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_move_to(cr, w/2 - extents.width/2, height_local);  
	cairo_show_text(cr, buffer);

	cairo_set_source_rgb(cr, 0.5, 0.5, 0.5)	;
	cairo_move_to(cr, (w/2 - extents.width/2)+2, height_local+2);  
	cairo_show_text(cr, buffer);
}
gboolean childTimer(GtkWidget* widget){
	
}
