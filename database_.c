#include "database_.h"
#include "global.h"
//! global variabel

sqlite_ *sqlite;
static const gchar *dsn = "SQLite";
static const gchar *default_command = " "
		" select isi.Id as a ,nama_hari.hari as b ,isi.jam as c , isi.bagian as d, isi.X,isi.alarm  as e"
		" from isi , nama_hari "
		" where isi.dal = nama_hari.id  ";
//		" order by isi.id DESC limit 10 , 0";
static gint lastHeaderNumber;
static gboolean sort		;
static const gchar *headerAlias [] = {"isi.id","nama_hari.hari","isi.jam","isi.bagian","isi.X","isi.alarm",""};
static int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names);
static const gchar * databaseGetSortStr(){
	if( sort ){
		return g_strdup_printf ("order by %s DESC  " , headerAlias [ lastHeaderNumber ] );
	}
	else{
		return g_strdup_printf ("order by %s ASC  "  , headerAlias [ lastHeaderNumber ] );
	}
}
sqlite_ *databaseGetObject(){
	return sqlite;
}
//! pertama 
int databaseCreate(){
	g_print("Database Create\n.");
	lastHeaderNumber = 0;
	sort = FALSE;
	sqlite = struct_new(sqlite_); 
	if( sqlite3_open ("dal", & sqlite->db) != 0){
			//! do something
		g_print("Could not open database.");
			return -1;
	}
	return 0;
}
gchar* databaseGetError(){
}
void databaseFreeData(){
	sqlite3_free_table(sqlite->data);
}
void databaseSortChange(const gint  headerNum){
	if(headerNum == lastHeaderNumber){
		if(sort)
			sort = FALSE;
		else
			sort = TRUE;
		return;
	}
	lastHeaderNumber = headerNum ;
	sort = TRUE;
}
//! 
gint databaseExeCommand(const gchar* command_){
	const gchar * sortStr = databaseGetSortStr();
	const gchar *preCommand = g_strdup_printf ("%s %s %s ",default_command,command_  , sortStr ); 	
	int a = databaseExe(preCommand);
	g_free(sortStr)		;	//!	Penting
	g_free(preCommand)	;	//!	Penting
	return a;
}
gint databaseExe(const char* command_){
	int rc = sqlite3_get_table( sqlite->db, command_, &sqlite->data, &sqlite->totalRow, &sqlite->totalCol, &sqlite->errmsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", sqlite->errmsg);
		return 1;
	}
	return 0;
}
gint databasePrepare()	{
	char *command = NULL;
	//! char *tail;
	const char *sql = "update app set val=? where id = ? ";	
	int rc = sqlite3_prepare_v2( sqlite->db,sql , strlen (sql)+1 , &sqlite->stmt, NULL); 
	if(rc == SQLITE_OK) {
		sqlite3_bind_double(sqlite->stmt,1, 250.0);
		sqlite3_bind_int(sqlite->stmt,2, 1);
		g_print("TEST");
	}	
	fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(sqlite->db));
	free(command);
//	free(tail);
	sqlite3_finalize(sqlite->stmt);

}
//! num_field = jumlah column , p__fields = data tiap-tiap baris , p_col_names = nama setiap column
static int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {
	return 0;
}

gint databaseGetTotalRow(){
	return sqlite->totalRow;
}
gint databaseGetTotalCol(){
	return sqlite->totalCol;
}
void databaseQuit(){
	sqlite3_close(sqlite->db);
}
char **databaseGetData(const gint aba ){
	return sqlite->data ;
}
//! belum bisa
void static getColByCol(){
	const gchar * sortStr = databaseGetSortStr();
	const gchar *preCommand = g_strdup_printf ("%s %s ",default_command  , sortStr ); 	
	sqlite->first_row = 1;
//	gint ret = sqlite3_exec(sqlite->db, sqlite->stmt, select_callback, &sqlite->totalRow, &sqlite->errmsg);
	int maxlen = strlen(preCommand);
	int rc = sqlite3_prepare_v2(sqlite->db, preCommand, maxlen, &sqlite->stmt, sqlite->data);
	if( rc!=SQLITE_OK ) {
		printf("Error in select statement %s [%s].\n", sqlite->stmt, sqlite->errmsg);
		//sqlite3_free(zErrMsg);
	}
	g_free(sortStr);
	sqlite->totalCol = sqlite3_column_count( sqlite->stmt);
	int i;
	for (i = 0; i < sqlite->totalCol ; i++){
		sqlite->colName= sqlite3_column_name( sqlite->stmt, i);
	}
	// print all fields, row by row
	int urutan = 0 ;
	do{
		rc = sqlite3_step( sqlite->stmt);
		if (rc == SQLITE_ROW){
			int col;
			for (col = 0; col < sqlite->totalCol; col++){
				sqlite->data[urutan] = sqlite->stmt;
				g_print(sqlite->data[urutan]);
				urutan++;
			}
		}
	}
	while (rc != SQLITE_DONE);

	rc = sqlite3_finalize( sqlite->stmt );	
	return;	
}
gint databaseGetIdHari(const char* hari){
		gint id;
		gchar * sql 	= 	"select id from nama_hari where  hari = ? ";
		int rc = sqlite3_prepare(sqlite->db, sql, strlen(sql), &sqlite->stmt, NULL);
		int ncols = sqlite3_column_count(sqlite->stmt);
		sqlite3_bind_text(sqlite->stmt	,1	, hari , strlen(hari), SQLITE_TRANSIENT);
		rc = sqlite3_step(sqlite->stmt);
		while(rc == SQLITE_ROW) {
			id 	 = sqlite3_column_int(sqlite->stmt, 0);
//			fprintf(stderr, "SQL error boss: %s\n", sqlite3_errmsg(sqlite->db));
			rc = sqlite3_step(sqlite->stmt);
		}
		sqlite3_finalize(sqlite->stmt);		
		return id;
}
//! merubah database , merubah database versi lama 
void databaseRubahFileMusic(){
	GList *list = NULL;
	char buffer [128];
	gint count_row,count_column;
	databaseExeCommand("");
	char ** data = databaseGetData(1);
	for(count_column=0;count_column<databaseGetTotalCol();count_column++){
		data++;
	}
	const int max_rows = databaseGetTotalRow();
	for ( count_row = 0; count_row < max_rows; count_row++ ){
		for ( count_column = 0; count_column < 6; count_column++) {
			if(count_column == 0 ){
				gint fu = globalConStrToInt(*data);
				list = g_list_append (list, GINT_TO_POINTER(fu) );
			}
			else if( count_column == 5 ){
				int target = 0;
				g_snprintf(buffer, sizeof(buffer), "%s", *data);
				gchar **kalender = g_strsplit_set(buffer,"/",-1);		//is equivalent to ``%H:%M:%S'
				if( g_strv_length(kalender) >4){
					target = 5;
				}
				char *a = g_strdup_printf ("%s", kalender[ target ] );
//				globalShowError(NULL,NULL,a);
				list = g_list_append (list, a );
				g_strfreev (kalender);
				//g_free(a);	// jangan lakukan ini
			}
			++data;
		}
	}
	databaseFreeData();
	//! saatnya update
	gchar *sql = "update isi set alarm=? where id = ? ";	
	int xx;
	for(xx=0;xx<g_list_length (list);xx+=2){
		int rc = sqlite3_prepare_v2( sqlite->db,sql , strlen (sql)+1 , &sqlite->stmt, NULL); 
		if(rc == SQLITE_OK) {
//			globalShowError(NULL,NULL,"TEST");
			char *a 	= g_list_nth_data (list,xx+1);
			int   aint 	= g_list_nth_data (list,xx);			
			sqlite3_bind_text(sqlite->stmt	,1	, a , strlen(a), SQLITE_TRANSIENT);
			sqlite3_bind_int(sqlite->stmt	,2	, aint		);
			sqlite3_step(sqlite->stmt);
			g_print("%i\n",aint);
		}
		else{
				fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(sqlite->db));
		}
		sqlite3_finalize(sqlite->stmt);		
	//	free(tail);
	}
	g_list_free (list);
	globalShowError(NULL,NULL,"Alhamdulillah!, berhasil merbuah isi database");
}
/*
char* databaseGetDataFromDb(char* sql , GValueArray *where){
	char *tail, *hasil;
	int rc = sqlite3_prepare(sqlite->db, sql, strlen(sql), &sqlite->stmt, &tail);
	if(rc==SQLITE_OK){	
		int ema;
		for(ema=0;ema<1;ema++){
			GValue*  value  = g_value_array_get_nth (where,ema);
			if(G_VALUE_TYPE(value) == G_TYPE_INT){
				sqlite3_bind_int(sqlite->stmt	, ema+1	, g_value_get_int(value)	);
			}
			else if( G_VALUE_TYPE(value) == G_TYPE_STRING ){
				char * tmp = g_value_get_string(value);
				sqlite3_bind_text(sqlite->stmt	, ema+1	, tmp , strlen(tmp), SQLITE_TRANSIENT 	);
			}
		}
//		gint ncols = sqlite3_column_count(sqlite->stmt);
		sqlite3_step(sqlite->stmt);
		hasil = g_strdup_printf ("%s", sqlite3_column_text(sqlite->stmt, 0) ) ;
	}
	else{
		fprintf(stderr, "sqlite3_prepare() : Error: %s\n", tail);
	}
	sqlite3_finalize(sqlite->stmt);	
	return hasil;
}
*/
GValueArray *databaseGetDatasFromDb(char* sql , GValueArray *where , gboolean *status ){
	status = FALSE;
	GValueArray* hasil = 	g_value_array_new (-1);
	char *tail;
	int rc = sqlite3_prepare(sqlite->db, sql, strlen(sql), &sqlite->stmt, &tail);
	if(rc==SQLITE_OK){	
		status = TRUE;
		int ema;
		if(where != NULL){
			for(ema=0;ema<where->n_values;ema++){
				GValue*  value  = g_value_array_get_nth (where,ema);
				if(G_VALUE_TYPE(value) == G_TYPE_INT){
					sqlite3_bind_int(sqlite->stmt	, ema+1	, g_value_get_int(value)	);
				}
				else if( G_VALUE_TYPE(value) == G_TYPE_STRING ){
					char * tmp = g_value_get_string(value);
					sqlite3_bind_text(sqlite->stmt	, ema+1	, tmp , strlen(tmp), SQLITE_TRANSIENT 	);
				}
			}
		}
		int ncols = sqlite3_column_count(sqlite->stmt);
		rc = sqlite3_step(sqlite->stmt);
		//! Print column information
		int i;
		while(rc == SQLITE_ROW) {
			for(i=0; i < ncols; i++) {
				GValue a = {0};
				g_assert (!G_VALUE_HOLDS_STRING (&a));			
				int type = sqlite3_column_type(sqlite->stmt, i);
				if(type==SQLITE_INTEGER){
						g_value_init (&a, G_TYPE_INT);
						int tmp = sqlite3_column_int(sqlite->stmt, i);
						g_value_set_int (&a, 1);
				}
				else if(type==SQLITE_FLOAT){
					g_value_init (&a, G_TYPE_FLOAT);
				}
				else if(type==SQLITE_TEXT){
					char *tmp = g_strdup_printf ("%s", sqlite3_column_text(sqlite->stmt, i) );
					g_value_init (&a, G_TYPE_STRING);
					g_value_set_string (&a, tmp);
					g_free(tmp);
				}
				hasil =	g_value_array_append(hasil,&a);
			}
			rc = sqlite3_step(sqlite->stmt);
		}
	}
	else{
		fprintf(stderr, "sqlite3_prepare() : Error: %s\n", tail);
	}
	sqlite3_finalize(sqlite->stmt);	
	return hasil;
}
