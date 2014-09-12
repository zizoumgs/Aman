#ifndef DATABASE_H
#define DATABASE_H
#include <gtk/gtk.h>
#include "sqlite3.h"
typedef struct _sqlite{
	char **data;
	sqlite3 * db;
	sqlite3_stmt * stmt;
	gchar * errmsg;
	int first_row;
	int totalRow;
	int totalCol;
	char* colName;
}sqlite_;

int databaseCreate();
gchar* databaseGetError();
//! untuk default command
gint databaseExeCommand(const gchar*);
//! yang ini terserah
gint databaseExe(const gchar*);
gint databaseGetTotalRow();
gint databaseGetTotalCol();
gint databasePrepare();
char **databaseGetData();
void databaseQuit();
void databaseFreeData();
void databaseFreePrepareData();
void databaseSortChange(const gint headerNum);
sqlite_ *databaseGetObject();
gint databaseGetIdHari(const char*);
void databaseRubahFileMusic();
//char * databaseGetDataFromDb(char *sql, GValueArray* where);
GValueArray *databaseGetDatasFromDb(char*, GValueArray*,gboolean*);
//! ini masih belum ada
GValueArray *databaseGetDatasFromDb_boss(char*, GType*,char*,gboolean*);
#endif


