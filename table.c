#include "table.h"
#include "glib.h"
#include "global.h"
#include "database_.h"
#include "sound.h"
#include "modif.h"
/*File ini berhubungan dengan table*/
typedef struct _table{
	GtkWidget           *view;
	GtkTreeStore  		*store;
	GtkTreeViewColumn   *col;
	gchar *tittle;
}table_;
typedef struct _dataToSend{
	gchar *id;
	gchar *file;
}dataToSend_;
table_ *table;
//! http://en.wikibooks.org/wiki/GTK%2B_By_Example/Tree_View/Events
//! sudo apt-get install libgda-4.0-dev
static GtkTreeModel* tableConDbTre ();
static gboolean tableClickHeader(GtkTreeViewColumn *widget , gpointer user_data);
static void table_popup_menu (GtkWidget *treeview, GdkEventButton *event, gpointer userdata);
static void tableRefresh();
static void tableTesData(GtkWidget*,gpointer);
static void tableUpdateListAlarmNTable(gboolean status);
static gboolean table_onButtonPressed(GtkWidget *treeview, GdkEventButton *event, gpointer userdata){
	dataToSend_ *dataToSend;
	/* single click with the right mouse button? */
    if (event->type == GDK_BUTTON_PRESS  &&  event->button == 3){
		g_print ("Single right click on the tree view.\n");
		if (1){
			GtkTreeSelection *selection;
			selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
			//! Note: gtk_tree_selection_count_selected_rows() does not exist in gtk+-2.0, only in gtk+ >= v2.2
			if (gtk_tree_selection_count_selected_rows(selection)  <= 1){
				GtkTreePath *path;
				//! Get tree path for row that was clicked
				if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(treeview),(gint) event->x, (gint) event->y,&path, NULL, NULL, NULL)){
					gtk_tree_selection_unselect_all(selection);
					gtk_tree_selection_select_path(selection, path);
					gtk_tree_path_free(path);
					
					GtkTreeModel     *model;
					GtkTreeIter       iter;
					if (gtk_tree_selection_get_selected(selection, &model, &iter)){
						dataToSend = struct_new(dataToSend_);
						gtk_tree_model_get (model, &iter, 0, &dataToSend->id, -1);    
						gtk_tree_model_get (model, &iter, 5, &dataToSend->file, -1);    
					}
				}
			}
		}
		table_popup_menu(treeview, event, dataToSend);
		return TRUE; /* we handled this */
	}
	return FALSE; /* we did not handle this */
}
static const char *headerTable []={
	"Id","Hari","Jam","Bagian","Total Bunyi","File"
};
static const  GType *column_Type []={
	G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING
};
//! clear
static GtkTreeModel *tableRemoveAll(GtkWidget *widget, gpointer selection){
	GtkTreeStore *store;
	GtkTreeModel *model;
	GtkTreeIter  iter;
  
	store = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW (table->view)));
	model = gtk_tree_view_get_model (GTK_TREE_VIEW (table->view));
	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) 
      return NULL ;
	gtk_tree_store_clear(store);
	return model;
}
//! membuat header
static GtkTreeViewColumn   * tableCreateHeader(GtkWidget *view){
	GtkCellRenderer     *renderer;
	int x;
	for(x=0;x<count(headerTable);x++){
		//!	Column
		table->col = gtk_tree_view_column_new();
//		GtkWidget *label = gtk_label_new( "TEST");
//		gtk_tree_view_column_set_widget (col,label);

		gtk_tree_view_column_set_title(table->col, headerTable[x]);
		//! pack tree view column into tree view
		gtk_tree_view_append_column(GTK_TREE_VIEW(view), table->col);
		renderer = gtk_cell_renderer_text_new();
		//! pack cell renderer into tree view column
		gtk_tree_view_column_pack_start(table->col, renderer, TRUE);
 
		//! connect 'text' property of the cell renderer to *  model column that contains the first name
		gtk_tree_view_column_add_attribute(table->col, renderer, "text", x);
		//! set 'weight' property of the cell renderer to
		//! bold print (we want all last names in bold)
		if( x ==0 ){
			g_object_set(renderer,
               "weight", PANGO_WEIGHT_BOLD,
               "weight-set", TRUE,
               NULL);
		}
		g_signal_connect(table->col, "clicked", G_CALLBACK(tableClickHeader), NULL);	 
	}
	return table->col;
}
//! get data
static GtkTreeModel *create_and_fill_model (const char* addCommand){
	gint idHari = databaseGetIdHari(toolGetNameHariActif());
	gchar *preCommand = g_strdup_printf ("");
	if( idHari != 0 ){
		preCommand = g_strdup_printf (" and nama_hari.id = %d ",idHari);		
	}
	databaseExeCommand( preCommand);
	GtkTreeModel *model = tableConDbTre ();
	g_free(preCommand);
	return model;
}
//! modif text inside table
void age_cell_data_func (GtkTreeViewColumn *col,GtkCellRenderer *renderer,GtkTreeModel *model,GtkTreeIter *iter,gpointer user_data)
{
	gchar  buf[64];
	gchar*  year_born;
	gtk_tree_model_get(model, iter, 2, &year_born, -1);
	g_snprintf(buf, sizeof(buf), "%s ", year_born);
	g_object_set(renderer, "foreground-set", FALSE, NULL); // print normal
	g_object_set(renderer, "text", buf, NULL);
	g_free(buf);
	g_free(year_born);
}

//! pembuatan 	view 
GtkWidget *tableCreate (void){
    table = struct_new(table_);
	databaseCreate();
	GtkTreeModel        *model;
 
	table->view = gtk_tree_view_new();
	//header
	GtkTreeViewColumn   *col  =  tableCreateHeader(table->view);	
	/* connect a cell data function */
	model = create_and_fill_model("");
	gtk_tree_view_set_model(GTK_TREE_VIEW(table->view), model);
 
	g_object_unref(model); /* destroy model automatically with view */

	
	gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(table->view)),GTK_SELECTION_SINGLE);
	gtk_tree_view_set_headers_clickable (table->view,TRUE);
	gtk_tree_view_set_rules_hint (table->view,TRUE);
	gtk_tree_view_set_grid_lines(table->view, GTK_TREE_VIEW_GRID_LINES_HORIZONTAL );

	g_object_set(	table->view ,"hover-selection" , TRUE,NULL);
	
	g_signal_connect(table->view, "button-press-event", (GCallback) table_onButtonPressed, NULL);

	return table->view;
}
//! click on header
static gboolean tableClickHeader(GtkTreeViewColumn *widget , gpointer user_data){
	table->tittle =  gtk_tree_view_column_get_title(widget);
	//! mencari header yang di click
	int x;
	for(x=0;x<count(headerTable);x++){
		gint id ; 
		id = g_strcmp0(table->tittle , headerTable [x]);
		if(id == 0)
			break;
	}
	databaseSortChange(x);
	tableRefresh("");
//	soundPlay("file:/home/zizou-desktop/Aman/music/Computer_Magic-Microsift-1901299923.wav" , 1);
//	soundPlay("Computer_Magic-Microsift-1901299923.wav" , 1);	
	return FALSE;
}
//! useless
void tableEvent(GtkWidget* parent){
//	databaseGetData("select *from isi");
//	GtkTreeSelection *selection;
// 	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
//	g_signal_connect(selection, "changed", G_CALLBACK(table_on_changed), view);	 	
	//g_signal_connect(GTK_TREE_VIEW(view), "clicked", G_CALLBACK(table_on_changed), NULL);
}
//! get type of column db
static GType *tableGetTypeColDb(int max_columns ){
	int count_column;
	//! melihat type masing2 column
	GType *lst_type = NULL;
	lst_type = g_try_malloc (sizeof (GType) * max_columns);
	memset (lst_type, 0, sizeof (GType) * max_columns);
	for ( count_column = 0; count_column < max_columns; count_column++) {
		//GdaColumn* field = gda_data_model_describe_column (data_model, count_column);
		//lst_type[count_column] = gda_column_get_g_type (field);
	}
	return lst_type;
}
//! convert db data to gtk data
static GtkTreeModel *tableConDbTre (){
	GtkTreeIter iter;
	guint max_columns = count(column_Type);
	table->store = gtk_tree_store_newv (max_columns, column_Type );
	char ** data = databaseGetData();
	int i ;
	for(i=0;i<databaseGetTotalCol();i++){
		data++;
	}
	int count_row  , count_column , urutan;
	if (table->store){
		const int max_rows = databaseGetTotalRow();
		for ( count_row = 1; count_row < max_rows; count_row++ ){
			gtk_tree_store_append(table->store, &iter, NULL);
			for ( count_column = 0; count_column < max_columns; count_column++) {
				if(count_column == 0 ){
					gint fu = globalConStrToInt(*data);
//					gint fu = globalConStrToInt("1");
					gtk_tree_store_set(table->store, &iter,count_column, fu ,-1);
				}
				else{
					gtk_tree_store_set(table->store, &iter,count_column, *data,-1);
				}
				++data;
			}
		}
	}
	GtkTreeModel *model_new = GTK_TREE_MODEL (table->store);
	databaseFreeData();
	return model_new;
}
void tableTestMemLeak(){
//	tableClickHeader(table->col,NULL);
}
//! pop_up menu
void table_popup_menu (GtkWidget *treeview, GdkEventButton *event, gpointer userdata){
	GtkWidget *menu, *ediItem,*delItem,*tesItem;
    menu = gtk_menu_new();
    ediItem = gtk_menu_item_new_with_label("Edit  Item");
    delItem = gtk_menu_item_new_with_label("Hapus Item");
    tesItem = gtk_menu_item_new_with_label("Test  Item");
    
    g_signal_connect(ediItem, "activate",(GCallback) tableEdiData, userdata);
    g_signal_connect(delItem, "activate",(GCallback) tableDelData, userdata);
    g_signal_connect(tesItem, "activate",(GCallback) tableTesData, userdata);
    
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), ediItem);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), delItem);    
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), tesItem);    
    
    gtk_widget_show_all(menu);
    // Note: event can be NULL here when called from view_onPopupMenu; gdk_event_get_time() accepts a NULL argument
    gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL,
                   (event != NULL) ? event->button : 0,
                   gdk_event_get_time((GdkEvent*)event));
}
static void tableRefresh(const gchar *addCommand){
	GtkTreeModel        *model = tableRemoveAll(NULL,NULL);		
	model = create_and_fill_model(addCommand);
	gtk_tree_view_set_model(GTK_TREE_VIEW(table->view), model);
	g_object_unref(model); // destroy model automatically with view 
}
void tableEdiData(GtkWidget* widget,gpointer data){
	gboolean status = FALSE;
	if(data == NULL){
		//! untuk update langsung dari menu
		status = modifEdi(globalGetParent(),NULL);
	}
	else{
		dataToSend_ *send = (dataToSend_*) data;
		status = modifEdi(globalGetParent(),send->id);
		g_free(send);
	}
	tableUpdateListAlarmNTable(status);
}
void tableDelData(GtkWidget* widget,gpointer data){
	gboolean status = FALSE;
	if(data == NULL){
		//! untuk update langsung dari menu
		status = modifDel(globalGetParent(),NULL);
	}
	else{
		dataToSend_* dataTo = (dataToSend_*)data ;
		char* data_id = dataTo->id;
		status = modifDel( globalGetParent() ,data_id);
		g_free(dataTo);
	}
	tableUpdateListAlarmNTable(status);

}
void tableAddData(GtkWidget* widget,gpointer data){
	gboolean status = FALSE;
	if(data == NULL){
		//! untuk update langsung dari menu
		status = modifAdd(globalGetParent(),NULL);
	}
	else{
		dataToSend_* dataTo = (dataToSend_*)data ;
		char* data_id = dataTo->id;
		status = modifAdd( globalGetParent() ,NULL);
		g_free(dataTo);
	}
	tableUpdateListAlarmNTable(status);
}
static void tableUpdateListAlarmNTable(gboolean status){
	if(status){
		tableRefresh("");
		alarmUpdateList();
	}
}
gboolean tableChangeHari(GtkWidget* widget , gpointer p){
	tableRefresh("");	
	return TRUE;
	char *p_newChuckIcon;
	p_newChuckIcon = gtk_combo_box_get_active_text(widget);
	g_print("%s\n",p_newChuckIcon);
	g_free(p_newChuckIcon);
}
static void tableTesData(GtkWidget* widget,gpointer data){
//	databaseRubahFileMusic();
//	return;
	gboolean status= FALSE;
	dataToSend_* dataTo = (dataToSend_*)data ;
	char* data_ = dataTo->file;
	gint  id    = dataTo->id;
	GValueArray* varr = 	g_value_array_new (-1);

	GValue a = {0};
	g_assert (!G_VALUE_HOLDS_STRING (&a));
	
	g_value_init (&a, G_TYPE_INT);
	g_value_set_int (&a, id);	
//	g_print("%i\n", g_value_get_int (&a) );
	
	varr 				=	g_value_array_append(varr,&a);
	GValueArray* hasil 	= databaseGetDatasFromDb("select  alarm from isi where id = ?", varr,&status);
	GValue *tmp 		= g_value_array_get_nth (hasil	,0 );

	soundPlay( g_value_get_string(tmp)  , 1);	
	//clean
	g_value_array_free (varr);
	g_value_array_free (hasil);
}
