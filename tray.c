#include "tray.h"
#include "global.h"
static GtkWidget *my_menu = NULL;
#include <libnotify/notify.h>
typedef struct _tray{
	GdkPixmap *pmap;	
	GtkWidget *win;
	cairo_t *cr;
	gint win_x , win_y;
	gint w, h;
	GtkWidget *window,*lbl;
	gint sisaWaktu;
	GtkWidget* tray_icon;
}tray_;
tray_* tray;
static void do_drawing(cairo_t *);
static void trayGetXy(GtkWidget *si , tray_* trayTmp){
	GdkRectangle rect;
	gint screen_w, screen_h;
	gint cursor_x, cursor_y;
	GtkDirectionType pos;
	GdkScreen *scr;
	gint win_x, win_y;
	gint x, y;
	trayTmp->w=250;
	trayTmp->h=35;
	if(gtk_status_icon_get_geometry(si, &scr, &rect, NULL)){
		cursor_x = rect.x;
		cursor_y = rect.y;
	}
	else{
		scr = gtk_status_icon_get_screen(si);
		gdk_display_get_pointer(gdk_screen_get_display(scr), NULL, &cursor_x, &cursor_y, NULL);
	}
	screen_w = gdk_screen_get_width(scr);
	screen_h = gdk_screen_get_height(scr);
	if(cursor_y < (screen_h/2)){
		pos = GTK_DIR_UP;
	}
	else{
		pos = GTK_DIR_DOWN;
	}
	/* draw the stem */
	switch(pos){
		case GTK_DIR_UP:
			if(cursor_x < (screen_w/2)){
				win_x = cursor_x;
				win_y = cursor_y;
			}
			else{
				win_x = cursor_x - trayTmp->w;
				win_y = cursor_y;
			}
			break;
		case GTK_DIR_DOWN:
			if(cursor_x < (screen_w/2)){
				win_x = cursor_x;
				win_y = cursor_y - trayTmp->h;
			}
			else{
				win_x = cursor_x - trayTmp->w;
				win_y = cursor_y - trayTmp->h;
			}
		break;
		default:
		break;
	}
	trayTmp->win_x = win_x;
	trayTmp->win_y = win_y;	
}
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{      
  cr = gdk_cairo_create(gtk_widget_get_window(widget));
  do_drawing(cr);  
  cairo_destroy(cr);

  return FALSE;
}

static void do_drawing(cairo_t *cr)
{
	cairo_set_source_rgba(cr, 0.2, 0.2, 0.2, 0.4);
	cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
	cairo_paint(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
}

static void traySetup(GtkWidget *win)
{        
	gtk_widget_set_app_paintable(win, TRUE);
	gtk_window_set_type_hint(GTK_WINDOW(win), GDK_WINDOW_TYPE_HINT_DOCK);
	gtk_window_set_keep_below(GTK_WINDOW(win), FALSE);
  
	GdkScreen *screen = gdk_screen_get_default();
	GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
  
	if (visual != NULL && gdk_screen_is_composited(screen)) {
		gtk_widget_set_visual(win, visual);
	}
}
//! tidak digunakan
void status_icon_activated(GtkStatusIcon *si, gpointer user_data){
	tray_ *trayTmp = (tray_*) user_data;
	if(trayTmp->window != NULL){
		gtk_widget_destroy(trayTmp->window);
//		gtk_widget_destroy(trayTmp->lbl);
	}
	trayTmp->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	traySetup(trayTmp->window);
	trayTmp->lbl = gtk_label_new("Fatihul Ulum manggisan");
  
	PangoFontDescription *fd = pango_font_description_from_string("Serif 10");
	pango_font_description_set_style(fd,PANGO_STYLE_OBLIQUE);
	gtk_widget_modify_font(trayTmp->lbl, fd);  
	gtk_container_add(GTK_CONTAINER(trayTmp->window), trayTmp->lbl);  
	
	GdkColor color;
	gdk_color_parse("white", &color);
	gtk_widget_modify_fg(trayTmp->lbl, GTK_STATE_NORMAL, &color);

	trayGetXy(si,trayTmp);
	gtk_widget_set_size_request(trayTmp->window, trayTmp->w, trayTmp->h);
	gtk_window_move(GTK_WINDOW(trayTmp->window), trayTmp->win_x, trayTmp->win_y);
	
	g_signal_connect(G_OBJECT(trayTmp->window), "expose-event", G_CALLBACK(on_draw_event), trayTmp);
	gtk_widget_show_all(trayTmp->window);
	//! katanya ada memory leak
	//http://www.gtkforums.com/viewtopic.php?t=1756
	pango_font_description_free (fd);
	trayTmp->sisaWaktu = 2;
}
static trayIconClick (GtkStatusIcon *status_icon, 
                        gpointer user_data)
{
	status_icon_activated(status_icon,user_data);
	printf("Clicked on tray icon\n");
}
static void trayIconMenu(GtkStatusIcon *status_icon, guint button, 
                       guint activate_time, gpointer user_data){
	GtkWidget *menu, *ediItem,*delItem,*tesItem;
    menu = gtk_menu_new();
    ediItem = gtk_menu_item_new_with_label("Edit  Item");
    delItem = gtk_menu_item_new_with_label("Hapus Item");
    tesItem = gtk_menu_item_new_with_label("Test  Item");
/*    
    g_signal_connect(ediItem, "activate",(GCallback) tableEdiData, userdata);
    g_signal_connect(delItem, "activate",(GCallback) tableDelData, userdata);
    g_signal_connect(tesItem, "activate",(GCallback) tableTesData, userdata);
*/    
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), ediItem);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), delItem);    
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), tesItem);
    gtk_widget_show_all(menu);
    gtk_menu_popup(GTK_MENU(menu),NULL,NULL,gtk_status_icon_position_menu,status_icon,button,activate_time);


}
GtkStatusIcon *trayCreateTrayIcon(GtkWidget* parent) {
	//	g_message ("Server does not support persistence; using a status icon");
	tray = struct_new(tray_);
	tray->window = NULL;
    tray->tray_icon = gtk_status_icon_new_from_pixbuf (globalCreateIcon("./image/home.png"));
    g_signal_connect(G_OBJECT(tray->tray_icon), "activate",G_CALLBACK		(trayIconClick), tray);
    g_signal_connect(G_OBJECT(tray->tray_icon),"popup-menu",G_CALLBACK	(trayIconMenu ), NULL);
    gtk_status_icon_set_tooltip_text(tray->tray_icon,globalGetAppName());
    gtk_status_icon_set_visible(tray->tray_icon, TRUE);

	/*
	notify_init ("XY");
//	NotifyNotification * hello = notify_notification_new_with_status_icon("<b>Aman</b>", "","./image/home.png",tray_icon);
	NotifyNotification * hello = notify_notification_new("<b>Aman</b>", "","",NULL);
	notify_notification_set_geometry_hints (hello,gdk_screen_get_default(),100,100);
	notify_notification_set_timeout (hello, 500);	//5 s
	notify_notification_show (hello, NULL);
    notify_notification_attach_to_status_icon (hello,tray_icon);
	*/

//	notify_notification_set_timeout(hello,1);
//	notify_notification_show(hello,NULL);
	tray->tray_icon = 5;
	return tray->tray_icon;
}
void trayTimer(GtkWidget* w){
	if(tray->sisaWaktu > 0 ){
		tray->sisaWaktu--;
	}
	else if(tray->sisaWaktu == 0){
		if(tray->window != NULL){
			gtk_widget_destroy(tray->window);
			tray->window = NULL;
		}
		tray->sisaWaktu  = - 1;
	}
}
void trayMessageSend(const gchar* pesan, gint long_in_mnt){
	tray_ *trayTmp = tray;
	trayTmp->sisaWaktu = 2;	
	if(trayTmp->window != NULL){
		gtk_widget_destroy(trayTmp->window);
//		gtk_widget_destroy(trayTmp->lbl);
	}
	trayTmp->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	traySetup(trayTmp->window);
	trayTmp->lbl = gtk_label_new(pesan);
  
	PangoFontDescription *fd = pango_font_description_from_string("Serif 10");
	pango_font_description_set_style(fd,PANGO_STYLE_OBLIQUE);
	gtk_widget_modify_font(trayTmp->lbl, fd);  
	gtk_container_add(GTK_CONTAINER(trayTmp->window), trayTmp->lbl);  
	
	GdkColor color;
	gdk_color_parse("white", &color);
	gtk_widget_modify_fg(trayTmp->lbl, GTK_STATE_NORMAL, &color);

	trayGetXy(trayTmp->tray_icon,trayTmp);
	gtk_widget_set_size_request(trayTmp->window, trayTmp->w, trayTmp->h);
	gtk_window_move(GTK_WINDOW(trayTmp->window), trayTmp->win_x, trayTmp->win_y);
	
	g_signal_connect(G_OBJECT(trayTmp->window), "expose-event", G_CALLBACK(on_draw_event), trayTmp);
	gtk_widget_show_all(trayTmp->window);
	//! katanya ada memory leak
	//http://www.gtkforums.com/viewtopic.php?t=1756
	pango_font_description_free (fd);
}
//! untuk test
void trayTest(GtkStatusIcon *tray_icon){
//    trayIconClick(tray_icon,tray);
//	void *ptr = malloc(sizeof(tray_));
//	((tray_*)ptr)->sisaWaktu = 5;
//	*((tray_*)ptr)->sisaWaktu = 5;
//	printf("%d\n", ((tray_*)ptr)->sisaWaktu );
}
