#include "tool.h"
#include "main.h"
#include "table.h"
#include "local.h"
#include "global.h"
GtkWidget* 	comboHari;
int (*pt2Function)(float, char, char) = NULL; 
static gboolean toolDestroy(GtkButton *qbutton, GtkWindow *window){
	mainQuit();
}
static gboolean toolEnterSig(){
	GdkCursor *cursor =  gdk_cursor_new (GDK_HAND2);
	gdk_window_set_cursor( gtk_widget_get_root_window(globalGetParent()) , cursor);
	gdk_cursor_unref(cursor);
	return FALSE;
}
static gboolean toolLeaveSig(){
	localSetDefCur(globalGetParent());
	return FALSE;
}
static gboolean button_press_callback (GtkWidget      *event_box,
                       GdkEventButton *event,
                       gpointer        data)
{
	gint id = GPOINTER_TO_INT(data);
	if(data==0){
		tableAddData(event_box , NULL);
	}
	else if(data==1){
		tableEdiData(event_box , NULL);
	}
	else{
		tableDelData(event_box , NULL);
	}
	return TRUE;
}
static GtkWidget* toolAddEvent_ema(const gchar *stock_id , const gint dest){
	GtkWidget* image 	 = gtk_image_new_from_stock (stock_id,GTK_ICON_SIZE_SMALL_TOOLBAR);
	GtkWidget* event_box = gtk_event_box_new ();
//	gtk_widget_add_events( event_box, GDK_POINTER_MOTION_MASK );
	gtk_container_add (GTK_CONTAINER (event_box), image);
	g_signal_connect (G_OBJECT (event_box),"button_press_event",G_CALLBACK (button_press_callback),dest);
	g_signal_connect(G_OBJECT(event_box), "enter-notify-event", G_CALLBACK(toolEnterSig), NULL);
	g_signal_connect(G_OBJECT(event_box), "leave-notify-event", G_CALLBACK(toolLeaveSig), NULL);
	return event_box;
}
gboolean toolComboHariCha(GtkWidget* widget , gpointer p){
}
GtkWidget *toolCreateNGet(GtkWidget* parent){
	GtkWidget *tool[4];
	GtkToolItem *sep;
	GtkToolItem *exit;

	GtkWidget* toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);

	sep = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1); 

	exit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exit, -1);

	tool[0] 	 = toolAddEvent_ema(GTK_STOCK_NEW		,0);
	tool[1] 	 = toolAddEvent_ema(GTK_STOCK_EDIT		,1);
	tool[2] 	 = toolAddEvent_ema(GTK_STOCK_DELETE	,2);
	tool[3]      = gtk_vseparator_new   ();
	
	comboHari 	  	= localGetComboHari(-3);
	gtk_widget_set_size_request (comboHari,100,30);
	/*
	GtkWidget* combobox = gtk_hbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(combobox), w);
	GtkWidget* halignbox = gtk_alignment_new(-1, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(halignbox), combobox);
	*/
	GtkWidget* hbox 	= gtk_hbox_new(FALSE, 1);
	int i;
	for(i=0;i<4;i++){
		gtk_box_pack_start(GTK_BOX(hbox), tool[i], FALSE,FALSE, 5);
	}
	gtk_box_pack_start(GTK_BOX(hbox), comboHari, FALSE, FALSE, 5);
	GtkWidget* halign = gtk_alignment_new(-1, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(halign), hbox) ;
	
	GtkWidget* boss = gtk_vbox_new(TRUE,1);
	gtk_box_pack_start(GTK_BOX(boss), halign, FALSE, FALSE, 0);

	g_signal_connect(comboHari, "changed", G_CALLBACK (tableChangeHari) , NULL); /* dirty */ 
	
	return boss;
}
void toolEvent(GtkWidget* parent){
}
gchar* toolGetNameHariActif(){
	if(comboHari== NULL)
		return "<all>";
	return gtk_combo_box_get_active_text(comboHari);
}
