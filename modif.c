#include "modif.h"
#include "global.h"
#include "database_.h"
#include "local.h"
//! http://blog.borovsak.si/2009/04
typedef struct _modifStruct {
	GtkWidget *hari;
	GtkWidget *jam;
	GtkWidget *mnt;
	GtkWidget *bagian;
	GtkWidget *filePilih;
	GtkWidget *total;
}modifStruct_; 
//g_object_set_data
static gboolean modifChoseFileSig(GtkWidget*,gpointer);
static GtkWidget *modifGetPilihanId(GtkWidget *);
static GtkWidget *modCreateJamMnt(GPtrArray *data,modifStruct_ *modifStruct);
static void modifSetItemToWidget(modifStruct_*,GValueArray*);
static gchar *fuGetNameFile(const gchar*);
// tidak dipakai dipanggil saat add saja
static void *modifGetWidgetLama(GtkWidget *parent);
//! menambah button dialog
static void modifAddButton(GtkWidget* dialog , gint defaultResponse){
	//! button
	gint cancel_button = GPOINTER_TO_INT(gtk_dialog_add_button (GTK_DIALOG (dialog),
                                       GTK_STOCK_CANCEL,
                                       GTK_RESPONSE_CANCEL) );
	gint ok_button = GPOINTER_TO_INT( gtk_dialog_add_button (GTK_DIALOG (dialog),
                                   GTK_STOCK_OK,
                                   GTK_RESPONSE_OK) );
	gtk_dialog_set_alternative_button_order (GTK_DIALOG (dialog),
                                         GTK_RESPONSE_CANCEL,
                                         GTK_RESPONSE_OK,
                                         GTK_RESPONSE_HELP,
                                         -1);
	gtk_dialog_set_default_response((GtkDialog*)dialog,defaultResponse);	
}
//! mengambil widget dialog dengan memakai gaya struct 
static GtkWidget *modifGetDialogWithStruct(GtkWidget* parent , modifStruct_ *modifStruct , const gchar *title	){
	GtkWidget *dialog , *content_area;
	GtkWidget *label [5];
	GtkWidget *total;
	GtkWidget *filePilih;
	GtkWidget *table;
	dialog = gtk_dialog_new();
	gtk_widget_set_parent_window( dialog,(GdkWindow*) parent );
	table = gtk_table_new(5, 2, FALSE);
	//
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	gchar *titleLabel [] = {"Hari","Jam","Bagian","Total","Pilih File"};
	int i;
	for(i=0;i<5;i++){
		label[i] = gtk_label_new( titleLabel[i]);
		gtk_table_attach(GTK_TABLE(table), label[i], 0, 1, i,i+1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	}
	GtkWidget* jamMnt = modCreateJamMnt(NULL, modifStruct);
	modifStruct->bagian   = gtk_combo_box_new_text();
	gtk_combo_box_append_text((GtkComboBox*)modifStruct->bagian,"WIB");
	gtk_combo_box_append_text((GtkComboBox*)modifStruct->bagian,"WIS");

	modifStruct->hari   = localGetComboHari(0);

//	gtk_combo_box_set_active(modifStruct->hari,5);    
//	modifStruct->filePilih	= gtk_file_chooser_button_new_with_dialog(dialog_file_open);
	modifStruct->filePilih  = gtk_button_new_with_label("Pilih File");
	g_signal_connect(G_OBJECT(modifStruct->filePilih), "clicked",G_CALLBACK(modifChoseFileSig), NULL);


//	modifStruct->filePilih 	= 	gtk_file_chooser_button_new ( "Select a file",GTK_FILE_CHOOSER_ACTION_OPEN);
//	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (modifStruct->filePilih),"/etc");
	
	modifStruct->total  	=	gtk_spin_button_new_with_range (1,10,1);
	
	gtk_table_attach(GTK_TABLE(table), modifStruct->hari		, 1, 3, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), jamMnt					, 1, 3, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), modifStruct->bagian		, 1, 3, 2, 3, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), modifStruct->total 		, 1, 3, 3, 4, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), modifStruct->filePilih 	, 1, 3, 4, 5, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_SHRINK, 5, 5);

//	gtk_spin_button_set_value(modifStruct->total,25.0); 
	
	gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 200);

	gtk_container_add (GTK_CONTAINER (content_area), table );
	modifAddButton(dialog,GTK_RESPONSE_CANCEL);
	gtk_window_set_title(GTK_WINDOW(dialog), title);

	gtk_dialog_set_has_separator( (GtkDialog *)dialog,TRUE);
	gtk_window_set_modal( GTK_WINDOW( dialog ), TRUE );
	gtk_window_set_transient_for( GTK_WINDOW( dialog ),GTK_WINDOW( globalGetParent() ) );
	return dialog;
}
//! mengambil widget jam dan menit 
static GtkWidget *modCreateJamMnt(GPtrArray *data,modifStruct_ *modifStruct){
	GtkWidget *table;
	table = gtk_table_new(1, 1, TRUE);
	GtkWidget *jam , *mnt;
	GtkAdjustment *jam_adj,*mnt_adj;
	jam_adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 23, 1.0, 0, 0);
	mnt_adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 59, 1.0, 0, 0);
	
	jam = gtk_spin_button_new (jam_adj, 1.0, 0);
	mnt = gtk_spin_button_new (mnt_adj, 1.0, 0);
	
	gtk_table_set_row_spacings(GTK_TABLE(table), 2);
	gtk_table_set_col_spacings(GTK_TABLE(table), 2);
	gtk_table_attach_defaults(GTK_TABLE(table), jam, 0, 1, 0, 1 ); 	
	gtk_table_attach_defaults(GTK_TABLE(table), mnt, 1, 2, 0, 1 ); 		

	if(modifStruct == NULL){
		//! pointer
		g_ptr_array_add (data, (gpointer) jam );
		g_ptr_array_add (data, (gpointer) mnt );

	}
	else{
		modifStruct->jam = jam;
		modifStruct->mnt = mnt;		
	}
	return table;
}
//! mengambil combo box pilihan id
static GtkWidget *modifGetPilihanId(GtkWidget *bagian){
	gboolean status = FALSE;
	GtkWidget *dialog , *content_area;
	GtkWidget *label1;
	GtkWidget *table;
	dialog = gtk_dialog_new();
	table = gtk_table_new(1, 1, FALSE);
	//
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	
	char *str = "<b>Id</b>";
	label1 = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label1), str);
		
	gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	//! isinya combobox
    GtkListStore    *store;
    GtkTreeIter      iter;
    GtkCellRenderer *cell;
	store = gtk_list_store_new ( 1, G_TYPE_STRING );
	
	GValueArray* has = databaseGetDatasFromDb("select id from isi ", NULL , &status);
	gint i;
	for(i=0;i<has->n_values;i++){
		GValue *ii = g_value_array_get_nth (has	,i );
		gchar *tmp = g_strdup_printf ("%i", g_value_get_int(ii)  );
		gtk_list_store_append( store, &iter);
		gtk_list_store_set( store, &iter, 0, tmp, -1 );
		
		//! free
		g_free(tmp);
	}
 
//	GtkWidget* bagian   = gtk_combo_box_new_with_model( GTK_TREE_MODEL( store ) );
//	bagian   = gtk_combo_box_new_with_model( GTK_TREE_MODEL( store ) );
	gtk_combo_box_set_model ( (GtkComboBox *) bagian,(GtkTreeModel *)store);
	gtk_combo_box_set_active( (GtkComboBox *) bagian,0);
	cell = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start( GTK_CELL_LAYOUT( bagian ), cell, TRUE );
    gtk_cell_layout_set_attributes( GTK_CELL_LAYOUT( bagian ), cell, "text", 0, NULL );
	
	gtk_combo_box_set_row_span_column(bagian,0);
	
	gtk_table_attach(GTK_TABLE(table), bagian		, 1, 2	, 0, 1, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_SHRINK, 5, 5);
	
	gtk_window_set_default_size(GTK_WINDOW(dialog), 250, 100);
	gtk_container_add (GTK_CONTAINER (content_area), table );
	modifAddButton(dialog,GTK_RESPONSE_CANCEL);
	gchar *tmp = g_strdup_printf ("Pilih Id - %s", globalGetAppName()); 
	gtk_window_set_title(GTK_WINDOW(dialog), tmp);

	gtk_dialog_set_has_separator(dialog,TRUE);
//	data = bagian;	
	gtk_dialog_set_has_separator(dialog,TRUE);
	gtk_window_set_modal( GTK_WINDOW( dialog ), TRUE );
	gtk_window_set_transient_for( GTK_WINDOW( dialog ),GTK_WINDOW( globalGetParent() ) );

	//! free
	g_value_array_free (has);
	g_object_unref( G_OBJECT( store ) );

	return dialog;
}
//! memasukkan item ke widget , biasanya dipakai di proses editing
static void modifSetItemToWidget(modifStruct_* modif,GValueArray* hasil){
	//! hari
	GValue *ii = g_value_array_get_nth (hasil	,1 );
	globalSetCurrentIndexCombo(modif->hari , g_value_get_string(ii));
	//!jam dan  menit
	ii = g_value_array_get_nth (hasil	,2 );
	gchar **kalender = g_strsplit_set(g_value_get_string(ii),":",-1);		//is equivalent to ``%H:%M:%S'
	gtk_spin_button_set_value( modif->jam,globalConStrToInt(kalender[0]) );
	gtk_spin_button_set_value( modif->mnt,globalConStrToInt(kalender[1]) );
	g_strfreev (kalender);
	//! bagian
	ii = g_value_array_get_nth (hasil	,3 );
	globalSetCurrentIndexCombo(modif->bagian , g_value_get_string(ii) );
	//! total bunyi
	ii = g_value_array_get_nth (hasil	,4 );
	gtk_spin_button_set_value( modif->total , globalConStrToInt(g_value_get_string(ii))  );
	//! nama file
	ii = g_value_array_get_nth (hasil	,5 );
	gtk_button_set_label(modif->filePilih , g_value_get_string(ii) );
}
//! edit
gboolean modifEdi(GtkWidget* parent , gpointer data){
	gboolean status = FALSE;
	gint id = GPOINTER_TO_INT(data);
	gint result = GTK_RESPONSE_OK;
	if(data == NULL){
		GtkWidget *comboId = gtk_combo_box_new ();
		GtkWidget *dialog = modifGetPilihanId(comboId);
		gtk_widget_show_all(dialog);
		result 	= 	gtk_dialog_run (dialog);	// block
		id 		=	globalConStrToInt(gtk_combo_box_get_active_text(comboId));
		gtk_widget_destroy(dialog);
	}	
	if(result==GTK_RESPONSE_OK){
		modifStruct_ *modif = struct_new(modifStruct_);
		gchar *title = g_strdup_printf ("Edit Data dengan id %d", id);
		GtkWidget *dialog = modifGetDialogWithStruct(parent , modif , title);
		//! mengambil data dari database
		GValueArray* varr = 	g_value_array_new (-1);		
		GValue a = {0};
		g_assert (!G_VALUE_HOLDS_STRING (&a));			
		g_value_init (&a, G_TYPE_INT);
		g_value_set_int (&a, id );
		varr =	g_value_array_append(varr,&a);
		gchar *sql = g_strdup_printf ("%s and isi.id=?", globalGetDefCom() );
		GValueArray *hasil = databaseGetDatasFromDb( sql	 , varr , &status);		
		modifSetItemToWidget(modif,hasil);
		//! show 
		gtk_widget_show_all(dialog);
		result = gtk_dialog_run (dialog);	// block
		if (result==GTK_RESPONSE_OK){
			//! sekarang kita akan masuk pada database
			//! mengambil data
			char *filename;
			char* jamchar = globalPutZeroToWkt(gtk_spin_button_get_value_as_int(modif->jam));
			char* mntchar = globalPutZeroToWkt(gtk_spin_button_get_value_as_int(modif->mnt));		
			gchar *jamMnt	= g_strdup_printf ("%s:%s", jamchar,mntchar);
			gchar * hari 	= gtk_combo_box_get_active_text ( modif->hari);
			gchar * bagian 	= gtk_combo_box_get_active_text ( modif->bagian );
			gint	total   = gtk_spin_button_get_value_as_int (modif->total);
			filename = fuGetNameFile( gtk_button_get_label(modif->filePilih));
			//! update database
			gint idHari = databaseGetIdHari(hari);
			GValueArray* varr = 	g_value_array_new (-1);		
			GValue a = {0};
			g_assert (!G_VALUE_HOLDS_STRING (&a));			
			g_value_init (&a, G_TYPE_INT);
			g_value_set_int (&a, idHari);			//! 1
			varr =	g_value_array_append(varr,&a);
			g_value_set_int (&a, total);			//! 2
			varr =	g_value_array_append(varr,&a);
			g_value_unset (&a);
			g_value_init (&a, G_TYPE_STRING);
			g_value_set_string (&a, jamMnt);		//! 3
			varr =	g_value_array_append(varr,&a);								
			g_value_set_string (&a, bagian);		//! 4
			varr =	g_value_array_append(varr,&a);								
			g_value_set_string (&a, filename);		//! 5
			varr =	g_value_array_append(varr,&a);
			g_value_unset (&a);
			g_value_init (&a, G_TYPE_INT);
			g_value_set_int (&a, id);			//! 6
			varr =	g_value_array_append(varr,&a);
			GValueArray *hasil = databaseGetDatasFromDb("update isi set dal=? , X=?,jam=?,bagian=?,alarm=? where id = ?" , varr,&status);
			//! free
			g_value_array_free (varr);
			g_value_array_free (hasil);
			//! aslinya harus di cek kembali
			status = TRUE;
		}
		else{
		}
		//! free all
		g_value_array_free (varr);
		g_value_array_free (hasil);
		gtk_widget_destroy(dialog);				
	}
	return TRUE;
}
//! delete
gboolean modifDel(GtkWidget* parent , gpointer data){
	gint id = GPOINTER_TO_INT(data);
	gboolean status = FALSE;
	gint result = GTK_RESPONSE_OK;
	if(data == NULL){
		GtkWidget *comboId = gtk_combo_box_new ();
		GtkWidget *dialog = modifGetPilihanId(comboId);
		gtk_widget_show_all(dialog);
		result 	= 	gtk_dialog_run ((GtkDialog*)dialog);	// block
		if (result != GTK_RESPONSE_OK)
			return FALSE;
		id 		=	globalConStrToInt(gtk_combo_box_get_active_text(comboId));
		gtk_widget_destroy(dialog);
		data =id;
	}
	char *tmp = g_strdup_printf ("Sudah yakinkah anda untuk menghapus id = %i", data);
	GtkWidget *w = globalGetSimpleQues(parent,"AMAN Tanya",tmp);	
	gtk_widget_show_all(w);
	result = gtk_dialog_run (w);
	g_free(tmp);
	if (result==GTK_RESPONSE_YES){
		GValueArray* varr = 	g_value_array_new (-1);		
		GValue a = {0};
		g_assert (!G_VALUE_HOLDS_STRING (&a));			
		g_value_init (&a, G_TYPE_INT);
		g_value_set_int (&a, data);
		varr =	g_value_array_append(varr,&a);								

		GValueArray *hasil = databaseGetDatasFromDb("delete from isi where id = ?" , varr , &status);
		status = TRUE;
		//! free
		g_value_array_free (varr);
		g_value_array_free (hasil);
	}
	gtk_widget_destroy(w);
	return status;
}
//! ketika tombol add di tekan maka akan kesini
gboolean modifAdd(gpointer call,GtkWidget* parent){
	gboolean status = FALSE;
	//modifGetWidgetLama(parent);
	modifStruct_ *modif = struct_new(modifStruct_);
	GtkWidget *w = modifGetDialogWithStruct(parent , modif ,"Menambah Data");	
	gtk_widget_show_all(w);
	gint result = gtk_dialog_run ((GtkDialog *) w);	// block
	if (result==GTK_RESPONSE_OK){
		//! mencari total row
		const gchar *exe = "select max(id) from isi ";
		databaseExe(exe);
		char **data = databaseGetData();
		int totalRow = databaseGetTotalRow();
		databaseFreeData();		
		//! mengambil data
		char *filename;
		char* jamchar = globalPutZeroToWkt(gtk_spin_button_get_value_as_int((GtkSpinButton *) modif->jam));
		char* mntchar = globalPutZeroToWkt(gtk_spin_button_get_value_as_int((GtkSpinButton *) modif->mnt));		
		gchar *jamMnt	= g_strdup_printf ("%s:%s", jamchar,mntchar);
		gchar * hari 	= gtk_combo_box_get_active_text ( (GtkComboBox *) modif->hari);
		gchar * bagian 	= gtk_combo_box_get_active_text ( (GtkComboBox *) modif->bagian );
		gint	total   = gtk_spin_button_get_value_as_int ( (GtkSpinButton *) modif->total);
		filename = fuGetNameFile( gtk_button_get_label( (GtkButton *) modif->filePilih));
		//! insert into database
		gint idHari = databaseGetIdHari(hari);
		GValueArray* varr = 	g_value_array_new (-1);		
		GValue a = {0};
		g_assert (!G_VALUE_HOLDS_STRING (&a));			
		g_value_init (&a, G_TYPE_INT);
		g_value_set_int (&a, totalRow+1);		//! 1
		varr =	g_value_array_append(varr,&a);								
		g_value_set_int (&a, idHari);			//! 2
		varr =	g_value_array_append(varr,&a);
		g_value_set_int (&a, total);			//! 3
		varr =	g_value_array_append(varr,&a);
		g_value_unset (&a);
		g_value_init (&a, G_TYPE_STRING);
		g_value_set_string (&a, jamMnt);		//! 4
		varr =	g_value_array_append(varr,&a);								
		g_value_set_string (&a, bagian);		//! 5
		varr =	g_value_array_append(varr,&a);								
		g_value_set_string (&a, filename);		//! 6
		varr =	g_value_array_append(varr,&a);

		GValueArray *hasil = databaseGetDatasFromDb("insert into isi (id,dal,X,jam,bagian,alarm) values (?,?,?,?,?,?)" , varr , &status);
		status = TRUE;
		//! free
		g_value_array_free (varr);
		g_value_array_free (hasil);
		g_free(jamMnt);
		g_free(hari);
		g_free(bagian);
	}
	g_free(modif);
	gtk_widget_destroy(w);
	return status;	
}
///! signal ketika user henddak memilih file
static gboolean modifChoseFileSig(GtkWidget* widget,gpointer data){
//	GtkWidget *toplevel = gtk_widget_get_toplevel (parent);
	GtkFileChooserDialog *dialog;
	dialog = gtk_file_chooser_dialog_new ("Buka file Bung",
				      (GtkWindow *)globalGetParent(),
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
		char *filename;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		gtk_button_set_label((GtkButton*)widget,filename);
		g_free(filename);
	}
	gtk_widget_destroy ( (GtkWidget *)dialog);
}
//! ketika keluar maka menjalankan ini
void modifQuit(){
	//! lakukan segala sesuatu yang harus dibunuh
}
static gchar * fuGetNameFile(const gchar* name){
	GFile *file = g_file_new_for_path(name);
	return g_file_get_basename(file);
}



// tidak dipakai
static GtkWidget *modifGetMyAsk(GPtrArray * z , gint index){
	return g_ptr_array_index (z, index);
}
// mengambil widget dialog add dengan memakai gaya pointer,, tidak dipakai tapi jangan dibuang
static GtkWidget *modifGetDialogAdd(GtkWidget* parent , GPtrArray *data 	){
	/*
	GtkWidget *dialog , *content_area;
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *label5;
	
	GtkWidget *total;
	GtkWidget *filePilih;

	GtkWidget *table;

	dialog = gtk_dialog_new();
	table = gtk_table_new(5, 2, FALSE);

	//
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	
	label1 = gtk_label_new("Hari");
	label2 = gtk_label_new("Jam");
	label3 = gtk_label_new("Bagian");
	label4 = gtk_label_new("Total");
	label5 = gtk_label_new("Pilih file");
	

	gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 2, 3, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label4, 0, 1, 3, 4, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label5, 0, 1, 4, 5, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  
	GtkWidget* jamMnt = modCreateJamMnt(data,NULL);
	
	GtkWidget* bagian   = gtk_combo_box_new_text();
	gtk_combo_box_append_text(bagian,"WIB");
	gtk_combo_box_append_text(bagian,"WIS");

	GtkWidget* hari   = localGetComboHari(0);
	GtkFileChooserDialog *dialog_file_open;
	dialog_file_open = gtk_file_chooser_dialog_new ("Buka file",
				      parent,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
				      
	filePilih	= gtk_file_chooser_button_new_with_dialog(dialog_file_open);

	total  =  gtk_spin_button_new_with_range (1,10,1);
	
	gtk_table_attach(GTK_TABLE(table), hari			, 1, 3, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), jamMnt		, 1, 3, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), bagian		, 1, 3, 2, 3, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), total 		, 1, 3, 3, 4, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), filePilih 	, 1, 3, 4, 5, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_SHRINK, 5, 5);

	
	gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 200);

	gtk_container_add (GTK_CONTAINER (content_area), table );
	modifAddButton(dialog,GTK_RESPONSE_CANCEL);
	gtk_window_set_title(GTK_WINDOW(dialog), "Menambah data ");

	gtk_dialog_set_has_separator(dialog,TRUE);

	if(data){
		g_ptr_array_add (data, (gpointer) hari );
		g_ptr_array_add (data, (gpointer) bagian );
		g_ptr_array_add (data, (gpointer) total );
		g_ptr_array_add (data, (gpointer) dialog_file_open );		
		return dialog;
	}
	return NULL;
	**/
}
// tidak dipakai
static void *modifGetWidgetLama(GtkWidget *parent){
	/*
	//! 0 = jam , 1 = menit ,2=hari, 3 =bagian , 4 = total , 5 = file
	GPtrArray *z = g_ptr_array_new ();
	GtkWidget *w = modifGetDialogAdd(parent , z);
	gtk_widget_show_all(w);
	gint result = gtk_dialog_run (w);	// block
	if (result==GTK_RESPONSE_OK){
		//! mencari total row
		const gchar *exe = "select * from isi ";
		databaseExe(exe);
		char **data = databaseGetData();
		int totalRow = databaseGetTotalRow();
		databaseFreeData();		
		g_print("%i\n", totalRow);				
		//! persiapan menuju pemasukan data
		char *filename;
		char* jamchar = globalPutZeroToWkt(gtk_spin_button_get_value_as_int(modifGetMyAsk(z,0)));
		char* mntchar = globalPutZeroToWkt(gtk_spin_button_get_value_as_int(modifGetMyAsk(z,1)));		
		gchar *jamMnt	= g_strdup_printf ("%s:%s", jamchar,mntchar);
		gchar * hari 	= gtk_combo_box_get_active_text ( modifGetMyAsk(z,2) );
		gchar * bagian 	= gtk_combo_box_get_active_text ( modifGetMyAsk(z,3) );
		gint	total   = gtk_spin_button_get_value_as_int (modifGetMyAsk(z,4));
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER ( modifGetMyAsk(z,5) ));		

		//!	syarat-syarat letakkan disini
			gint idHari = databaseGetIdHari(hari);
			char* tail;
			sqlite_ *sqlite = databaseGetObject();
			char* sql = "insert into isi (id,dal,jam,bagian,X,alarm) values (?,?,?,?,?,?)";
			int rc = sqlite3_prepare(sqlite->db, sql, strlen(sql), &sqlite->stmt, tail);
			if(rc != SQLITE_OK) {
				fprintf(stderr, "sqlite3_prepare() : Error: %s\n", tail);
			}
			else{
				sqlite3_bind_int(sqlite->stmt	,1	, totalRow+1	);
				sqlite3_bind_int(sqlite->stmt	,2	, idHari	);
				sqlite3_bind_text(sqlite->stmt	,3	, jamMnt , strlen(jamMnt), SQLITE_TRANSIENT);
				sqlite3_bind_text(sqlite->stmt	,4	, bagian , strlen(bagian), SQLITE_TRANSIENT);
				sqlite3_bind_int(sqlite->stmt	,5	, total );
				sqlite3_bind_text(sqlite->stmt	,6	, filename , strlen(filename), SQLITE_TRANSIENT);
				sqlite3_step(sqlite->stmt);
			}
		sqlite3_finalize(sqlite->stmt);		
		g_free(filename);
		g_free(jamMnt);
		g_free(hari);
		g_free(bagian);
	}
	g_ptr_array_free (z, TRUE);
	gtk_widget_destroy(w);	
	*/ 
}
