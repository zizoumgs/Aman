#include <gdk/gdkkeysyms.h>
#include <unique/unique.h>
#include "tray.h"
#include "main.h"
#include "global.h"
#include "table.h"
#include "menu.h"
#include "database_.h"
#include "glib.h"
#include "sound.h"
#include "setting.h"
#include "waktu.h"
#include "tool.h"
//http://www.youtube.com/watch?v=5f1D9kHogq0
//http://blog.borovsak.si/2009/04
//! http://art.gnome.org/themes/gtk2?page=1
//! waktu
enum {
  COMMAND_0,

  COMMAND_FOO,
  COMMAND_BAR
};
static UniqueResponse mainSingleSig(UniqueApp         *app,
                gint               command,
                UniqueMessageData *message_data,
                guint              time_,
                gpointer           user_data);
//! tempat applikasi utama dibuat
static void mainApp(int argc, char **argv);
static gboolean mainTime(GtkWidget *widget){
	if (widget->window == NULL) 
		return FALSE;
	if (! globalIsAppReady())
		return FALSE;
	waktuTimer(widget);
	trayTimer(widget);
	return TRUE;
}
static GtkWidget* mainCreateScroll(){
	GtkWidget* scrolledwin;
	scrolledwin = gtk_scrolled_window_new(NULL,NULL);
	gtk_container_set_border_width(GTK_CONTAINER(scrolledwin), 0);
//	gtk_widget_set_size_request(scrolledwin, 800, 600);
	//! keluar hanya jika di butuhkan
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwin),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);	
	return scrolledwin;
}
//! panggil disini semua hal yang harus mati
gboolean mainQuit(){
	settingQuit(parent->window);
	databaseQuit();
	modifQuit();
	soundQuit();
	gtk_main_quit();
}
int main (int argc, char **argv){
	globalSetGtkrc("gtkrc");
	UniqueApp *app;
	gboolean new = FALSE;
	gboolean activate = FALSE;
	gboolean foo = FALSE;
	gchar **uris = NULL;
	GError *init_error = NULL;
	GOptionEntry entries[] = {
		{ "new", 'n',0,G_OPTION_ARG_NONE, &new,"Send 'new' command", NULL,},
		{ "open-uri", 'o',0,G_OPTION_ARG_STRING_ARRAY, &uris,"Send 'open' command", "URI",},
		{ "activate", 'a',0,G_OPTION_ARG_NONE, &activate,"Send 'activate' command", NULL,},
		{ "foo", 'f',0,G_OPTION_ARG_NONE, &foo,"Send 'foo' command", NULL,},
		{ NULL },
	};
	gtk_init_with_args (&argc, &argv,"Test GtkUnique",entries,NULL,&init_error);
	if (init_error){
		g_print ("*** Error: %s\n Usage: test-unique [COMMAND]\n",init_error->message);
		g_error_free (init_error);
		exit (1);
    }
	app = unique_app_new_with_commands ("org.gnome.TestUnique", NULL,"foo", COMMAND_FOO,"bar", COMMAND_BAR,NULL);
	if (unique_app_is_running (app)){
		UniqueMessageData *message = NULL;
		UniqueResponse response;
		gint command;
		if (new)
			command = UNIQUE_NEW;
		else if (uris && uris[0]){
			command = UNIQUE_OPEN;
			message = unique_message_data_new ();
			unique_message_data_set_uris (message, uris); 
        }
		else if (activate)
			command = UNIQUE_ACTIVATE;
		else if (foo){
			command = COMMAND_FOO;
			message = unique_message_data_new ();
			unique_message_data_set (message, (const guchar *) "bar", 3);
        }
		else
			command = COMMAND_BAR;
		if (message){
			response = unique_app_send_message (app, command, message);
			unique_message_data_free (message);
        }
		else
			response = unique_app_send_message (app, command, NULL);
		g_print ("Response code: %d\n", response);
		gdk_notify_startup_complete ();
		g_object_unref (app);
		return (response == UNIQUE_RESPONSE_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
	else{
		mainApp(argc,argv);
		unique_app_watch_window (app, GTK_WINDOW (globalGetParent()));
		g_signal_connect (app, "message-received",G_CALLBACK (mainSingleSig), NULL);
    }
	gtk_main();
	g_object_unref (app);
	//!
	soundFreeResource();
	return 0;
}
static UniqueResponse mainSingleSig(UniqueApp         *app,
                gint               command,
                UniqueMessageData *message_data,
                guint              time_,
                gpointer           user_data){
	GtkWidget *dialog;
	gchar *message = NULL;
	gchar *title = NULL;
	GdkScreen *screen;
	const gchar *startup_id;
	screen = unique_message_data_get_screen (message_data);
	startup_id = unique_message_data_get_startup_id (message_data);
	g_print ("Message received from screen: %d, startup-id: %s, workspace: %d\n",
           gdk_screen_get_number (screen),
           startup_id,
           unique_message_data_get_workspace (message_data));

	/* raise the window */
	gtk_window_present_with_time (GTK_WINDOW (globalGetParent()), time_);
	switch (command){
		case UNIQUE_NEW:
			title = g_strdup ("Received the NEW command");
			break;
		case UNIQUE_OPEN:{
			gchar **uris;
			gint n_uris, i;
			GString *buf;

			title = g_strdup ("Received the OPEN command");
        
			uris = unique_message_data_get_uris (message_data);
			n_uris = g_strv_length (uris);
			buf = g_string_new (NULL);
			for (i = 0; i < n_uris; i++)
				g_string_append_printf (buf, "uri: %s\n", uris[i]);
			message = g_string_free (buf, FALSE);
			g_strfreev (uris);
		}
		break;
		case UNIQUE_ACTIVATE:
		title = g_strdup ("Received the ACTIVATE command");
		break;
		case COMMAND_FOO:
			title = g_strdup ("Received the FOO command");
			message = unique_message_data_get_text (message_data);
		break;
		case COMMAND_BAR:
			title = g_strdup (globalGetAppNameNVersion());
			message = g_strdup ("Hanya satu yang bisa di jalankan");
		break;
		default:
		break;
	}
	dialog = gtk_message_dialog_new (GTK_WINDOW (globalGetParent()),
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_CLOSE,
                                   title);
	if (message)
		gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),message);
	gtk_window_set_urgency_hint (GTK_WINDOW (dialog), TRUE);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
	g_free (message);
	g_free (title);
	return UNIQUE_RESPONSE_OK;
}
static void mainApp(int argc, char **argv){
	settingCreate();
     /* Allocate memory for the data that is passed to the callbacks */
//	gtk_init(&argc, &argv);
	/* make sure the type is realized */
	g_type_class_unref (g_type_class_ref (GTK_TYPE_IMAGE_MENU_ITEM));
	g_object_set (gtk_settings_get_default (), "gtk-menu-images", TRUE, NULL);
	//!
    parent = struct_new(parent_);
	globalCreate();
	GtkWidget *view;
	GtkWidget* lab , *vbox;
	GtkWidget* hseparator;
    
	parent->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(parent->window), globalGetAppNameNVersion() );
	gtk_container_set_border_width(GTK_CONTAINER(parent->window), 5);

	//!
	//! settingResizeWidget(parent->window,"winUtama");
	//! gtk_window_set_default_size(GTK_WINDOW(parent->window), 800, 600);
	//! gtk_window_set_position(GTK_WINDOW(parent->window), GTK_WIN_POS_CENTER);
	//!
	//!
	waktuCreate(parent->window);
	gtk_window_set_default_icon(globalCreateIcon("./image/home.png"));
	vbox = gtk_vbox_new(FALSE, 0);
	GtkWidget* child = childCreate(parent->window);
	GtkWidget* Schroll = mainCreateScroll();
	view = tableCreate();
	gtk_container_add(GTK_CONTAINER(Schroll), view); // add textview into scrol

	GtkWidget *menubar	= 	menuGetMenuBar(parent->window);
	GtkWidget* toolbar 	= 	toolCreateNGet(parent->window);
	hseparator = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(vbox), menubar		, FALSE	, FALSE	, 3);	
	gtk_box_pack_start(GTK_BOX(vbox), hseparator	, FALSE	, FALSE	, 3);		
	gtk_box_pack_start(GTK_BOX(vbox), toolbar		, FALSE	, FALSE	, 3);		
	gtk_box_pack_start(GTK_BOX(vbox), Schroll		, TRUE	, TRUE	, 5);
	gtk_box_pack_start(GTK_BOX(vbox), child			, FALSE	, TRUE	, 5);

	gtk_container_add(GTK_CONTAINER(parent->window), vbox);
	//!
	GtkStatusIcon *tray_icon = trayCreateTrayIcon(parent->window);
	//Event
	tableEvent	(parent->window);
	menuEvent	(parent->window);
	g_signal_connect(parent->window, "delete_event", mainQuit, NULL); /* dirty */ 
//	g_signal_connect_swapped(G_OBJECT(parent->window), "destroy",G_CALLBACK(mainQuit), G_OBJECT(parent->window));

	//! Register a function that GLib will call every second 
	g_timeout_add(1000, (GSourceFunc) mainTime, (gpointer) parent->window);
	//! set resize
	settingResizeWidget(parent->window,"winUtama");
	gtk_widget_set_app_paintable(parent->window, TRUE);
	gtk_widget_show_all(parent->window);

	localSetDefCur(parent->window);

	mainTime(parent->window);

	soundCreate(&argc,&argv);
	//soundPlay(argv[1],1);
	//! for tes memory leak
	int x = 0 ;
	while(x<100){
		tableTestMemLeak();
		x++;
	}
	trayTest(tray_icon);
	globalSetAppReady(TRUE);
}
