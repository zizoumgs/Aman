#include "global.h"
static void globalInsertToArray(GArray* arr , gchar* text){
	g_array_append_val (arr,  text);	
}
gchar *globalConIntToStr(gint value){
	//		g_print( "\n%s",globalConIntToStr(100) );
	char buffer[10];
	g_snprintf(buffer, sizeof(buffer), "%d", value);
	return buffer;
}
gint globalConStrToInt(gchar *text){
//	return g_printf("%s",text);
	return atoi(text);
}
gfloat globalConStrToFlo(gchar *text){
//	return g_printf("%s",text);
	return atof(text);
}
void globalShowError(GtkWidget *widget, gpointer window,const gchar *pesan){
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            pesan);
	gtk_window_set_title(GTK_WINDOW(dialog), "Error");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}
GtkWidget* globalGetParent(){
	return parent->window;
}
gchar *globalPutZeroToWkt( gint value ){
	if(value < 10){
		return g_strdup_printf ("0%d", value);
	}
	else{
		return g_strdup_printf ("%d", value);
	}
}
GtkWidget *globalGetSimpleQues(GtkWidget *parent,char* tittle,char* text){
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            text);
	gtk_window_set_title(GTK_WINDOW(dialog),tittle);
	return dialog;
//	gtk_dialog_run(GTK_DIALOG(dialog));
//	gtk_widget_destroy(dialog);
}
gchar* globalGetAppName(){return " - Aman"; }
gchar *globalGetVersion(){ return "0.3";}
gchar *globalGetAppNameNVersion(){
	return g_strdup_printf ("%s (%s)", globalGetAppName(),globalGetVersion());
}
void globalSetCurrentIndexCombo(GtkWidget* combo, gchar* textFind){
	GtkTreeIter iter;
	gboolean valid;
	gint row_count = 0;
	GtkTreeModel * list_store = gtk_combo_box_get_model (combo);
	valid = gtk_tree_model_get_iter_first (list_store, &iter);
	while (valid){
		gchar *str_data;
		gint   int_data;
		gtk_tree_model_get (list_store, &iter,0,&str_data,-1);
		if( g_strcasecmp( str_data , textFind) == 0 ){
			g_free (str_data);
			break;
		}
		g_free (str_data);
		row_count ++;
		valid = gtk_tree_model_iter_next (list_store, &iter);
    }
    gtk_combo_box_set_active (combo, row_count);	
}
gchar* globalGetDefCom(){
	return
		" select isi.Id as a ,nama_hari.hari as b ,isi.jam as c , isi.bagian as d, isi.X,isi.alarm  as e"
		" from isi , nama_hari "
		" where isi.dal = nama_hari.id  ";
}
GdkPixbuf *globalCreateIcon(const gchar * filename)
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   if(!pixbuf) {
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
   }
   return pixbuf;
}
void globalShowAbout(GtkWidget *widget, gpointer data){
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("home.png", NULL);
	GtkWidget *dialog = gtk_about_dialog_new();
	gtk_window_set_modal( GTK_WINDOW( dialog ), TRUE );
	gtk_window_set_transient_for( GTK_WINDOW( dialog ),GTK_WINDOW( globalGetParent() ) );
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), globalGetAppName());
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), globalGetVersion()); 
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(C) F.U - 13-02-15 ");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"Aman adalah alarm sekolah sederhana yang ternyata tidak sederhana.");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),"http://www.manggisan.com");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
	gtk_dialog_run(GTK_DIALOG (dialog));
	gtk_widget_destroy(dialog);
//	g_object_unref(pixbuf);
}
gchar *globalGetCurDir(){
	return g_get_current_dir ();
}
void globalSetGtkrc(const gchar* file){
	gtk_rc_add_default_file (file);	
}
void globalAddGValue( GValue *val , GType type,gchar* text , gboolean changeType){
	if(changeType)
		g_value_unset (val);
		
	g_value_init (val, type);
	g_value_set_string (val, text);
	/*
	GValue a = {0};
	g_assert (!G_VALUE_HOLDS_STRING (&a));			
	g_value_init (&a, type);
	g_value_set_string (&a, val);	
	return &a;
	*/ 
}
gboolean globalIsAppReady(){
	return parent->appReady;
}
void globalSetAppReady(gboolean status){
	parent->appReady = status;
}
void globalCreate(){
	globalSetAppReady(FALSE);
}
