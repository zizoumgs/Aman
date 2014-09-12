#include "local.h"
void localSetDefCur(GtkWidget* widget){
	GdkCursor *cursor =  gdk_cursor_new (GDK_LEFT_PTR);
	gdk_window_set_cursor( gtk_widget_get_root_window(widget) , cursor);
	gdk_cursor_unref(cursor);
}
void localRetDefCur(GtkWidget* widget){
//	GdkCursor *cursor =   gdk_window_get_cursor (gtk_widget_get_root_window(widget));
//	gdk_window_set_cursor( gtk_widget_get_root_window(widget) , cursor);

}
//! combo box hari
GtkWidget* localGetComboHari(const gint minimum){
	gboolean status = FALSE;
	//! isinya combobox
    GtkListStore    *store;
    GtkTreeIter      iter;
    GtkCellRenderer *cell;
	store = gtk_list_store_new ( 1, G_TYPE_STRING );
	gchar *sql = g_strdup_printf("select hari from nama_hari where id > %i",minimum);

	GValueArray* has = databaseGetDatasFromDb(sql, NULL, &status);
	gint i;
	for(i=0;i<has->n_values;i++){
		GValue *ii = g_value_array_get_nth (has	,i );
//		gtk_combo_box_append_text(GTK_COMBO_BOX(bagian), tmp );
		gtk_list_store_append( store, &iter);
		gtk_list_store_set( store, &iter, 0, g_value_get_string(ii) , -1 );
	}
	GtkWidget* bagian   = gtk_combo_box_new();
	gtk_combo_box_set_model(bagian,store);
	gtk_combo_box_set_active(bagian,0);
	cell = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start( GTK_CELL_LAYOUT( bagian ), cell, TRUE );
    gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT( bagian ), cell, "text", 0, NULL );
	//! free
	g_value_array_free (has);
	g_object_unref( G_OBJECT( store ) );
	return bagian;
}

