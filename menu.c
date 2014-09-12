#include <gdk/gdkkeysyms.h>
#include "menu.h"
#include "table.h"
#include "global.h"
static GtkWidget *quit;
static GtkWidget *checkWib;
void menuToggleJam(){
	gboolean cek = gtk_check_menu_item_get_active (checkWib);
	if(cek)
		gtk_check_menu_item_set_active (checkWib,FALSE);
	else
		gtk_check_menu_item_set_active (checkWib,TRUE);	
}
gboolean menuIsWibShow(){
	return gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM( checkWib ) );
}
static gboolean menuMainDestroy(GtkButton *qbutton, GtkWindow *window){
	mainQuit();
}
static void menuNum2(GtkWidget* parent,GtkWidget* menuBar,GtkAccelGroup *accel_group);
GtkWidget* menuGetMenuBar(GtkWidget *parent){	
	GtkWidget *menubar;
	GtkWidget *filemenu;
	GtkWidget *file , *delete;
	GtkWidget *new;
	GtkWidget *open;
	
	GtkWidget *sep;
  
	GtkAccelGroup *accel_group = NULL;
	
	menubar = gtk_menu_bar_new();
	filemenu = gtk_menu_new();

	accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(parent), accel_group);

	file = gtk_menu_item_new_with_mnemonic("_File");
	//! menu child
	new  = gtk_image_menu_item_new_from_stock (GTK_STOCK_ADD, NULL);
	open = gtk_image_menu_item_new_from_stock(GTK_STOCK_EDIT, accel_group);
	delete = gtk_image_menu_item_new_from_stock(GTK_STOCK_DELETE, accel_group);	
	quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);
	sep = gtk_separator_menu_item_new();
	//! sub menu
	GtkWidget *showJam = gtk_image_menu_item_new_from_stock(GTK_STOCK_DND,NULL);
	GtkWidget* submenu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (showJam), submenu);
	checkWib = gtk_check_menu_item_new_with_label("Wib");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(checkWib), TRUE);
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu), checkWib);
	//! add keypress event
	gtk_widget_add_accelerator(quit		, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); 
	gtk_widget_add_accelerator(new		, "activate", accel_group, GDK_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); 
	gtk_widget_add_accelerator(open		, "activate", accel_group, GDK_e, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); 
	gtk_widget_add_accelerator(delete	, "activate", accel_group, GDK_d, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); 
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), new);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), delete);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), showJam);	
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

	g_signal_connect(G_OBJECT(new)	, "activate",G_CALLBACK(tableAddData) , NULL);
	g_signal_connect(G_OBJECT(open)	, "activate",G_CALLBACK(tableEdiData) , NULL);	
	g_signal_connect(G_OBJECT(delete)	, "activate",G_CALLBACK(tableDelData) , NULL);	
	
	menuNum2(parent,menubar,accel_group);
	return menubar;
}
void menuEvent(GtkWidget* parent){
	g_signal_connect(G_OBJECT(quit)	, "activate",G_CALLBACK(menuMainDestroy), parent);
}
static void menuNum2(GtkWidget* parent,GtkWidget* menuBar ,GtkAccelGroup *accel_group){
	GtkWidget* fileMenu = gtk_menu_new();
	GtkWidget *file , *about;	
	file = gtk_menu_item_new_with_mnemonic("_Dll");
	//! menu child
	about = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, accel_group);
	//! add keypress event
	gtk_widget_add_accelerator(about		, "activate", accel_group, GDK_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	//! create and add menubar
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), about);	
	//! add Menu 
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), file);
	//! add event
	g_signal_connect(G_OBJECT(about)	, "activate",G_CALLBACK(globalShowAbout) , NULL);
}
