#include "alarm.h"
#include "waktu.h"
#include "database_.h"
#include "global.h"
#include "sound.h"
/***
 * Jam sudah di uji pada 3 kemungkinan 1. pada saat jam akhir sama dengan jam start , jam akhir< jam start , jam akhir>jam start
 ***/
#define NGAJI_JAM_START 22
#define NGAJI_JAM_AKHIR 23
#define NGAJI_MNT_START 15
#define NGAJI_MNT_AKHIR 6
//#include "global.h"
static gboolean oldIdHari;
static GList *wib;
static GList *wis;
static void alarmSetIdHari(gint idHari){	oldIdHari = idHari ;	}
static gint jarakDuaBunyi;
static void alarmDecideMengaji();
static gboolean  mengajikah;	//! harus true jika sedang mengaji
static void alarmMulaiMengaji();
static void alarmResetJarak(){
	jarakDuaBunyi = 0;
}
void alarmCreate(GtkWidget* widget){
	alarmSetIdHari(-1);
	wib 	= 	NULL;
	wis		=	NULL;
	mengajikah = FALSE;
	alarmResetJarak();
}
void alarmQuit(){
}

void alarmTimer(gint currentIdHari){
	if(oldIdHari != currentIdHari){
		alarmSetIdHari ( currentIdHari );
		alarmUpdateList();
	}
	int i;
	gchar * current = waktuGetWib(FALSE);
	for(i=0;i<g_list_length (wib);i+=3){
		char *a = g_list_nth_data (wib,i);
		char* b  = g_list_nth_data (wib,i+1);
		char* c  = g_list_nth_data (wib,i+2);
		if(  g_strcmp0(  a, current)==0 ){
			CustomData *cd = soundGetGStream();
			if(cd->totalLoop == 0){
				soundPlay(c,globalConStrToInt(b));
			}
			g_print ("durasi %i\n",cd->duration );
		}
	}
	current = (gpointer)waktuGetWis(FALSE);
	for(i=0;i<g_list_length (wis);i+=2){
		char *a = g_list_nth_data (wis,i);
		char* b  = g_list_nth_data (wis,i+1);
		char* c  = g_list_nth_data (wis,i+2);
		if(  g_strcmp0(  a, current)==0 ){
			if( jarakDuaBunyi == 0 ){
				//soundPlay(c,globalConStrToInt(b));
			}
			jarakDuaBunyi++;
		}
	}
	if (jarakDuaBunyi == 60)
		alarmResetJarak();
	//! untuk mengaji boss
	alarmDecideMengaji();
}
//! ngaji use istiwak`s time
static void alarmDecideMengaji(){
	int  * wis = waktuGetWis();
	if(wis[0] >= NGAJI_JAM_START && wis [0] < NGAJI_JAM_AKHIR ){
		if( wis [0] == NGAJI_JAM_START ){
			if(wis[1] > NGAJI_MNT_START ){
				if( ! mengajikah ){
					alarmMulaiMengaji();
				}
			}
		}
		else{
			if( ! mengajikah ){
				alarmMulaiMengaji();
			}
		}
	}
	else if( wis[0] >= NGAJI_JAM_AKHIR){
		if( wis[0] == NGAJI_JAM_AKHIR){
			//! lihat menit
			if( wis [1] >= NGAJI_MNT_AKHIR){
				soundStop(NULL , soundGetGStream());			
				mengajikah = FALSE;
			}
			else{
				if( ! mengajikah ){
					alarmMulaiMengaji();
				}
			}
		}
		else{
			soundStop(NULL , soundGetGStream());			
			mengajikah = FALSE;
		}
	}
	if( mengajikah ){
		if( soundGetStatus() == SOUNDSIAP){
			alarmMulaiMengaji();
		}
	}
//	soundPlay("1.ogg",2);
//	g_print(" Mengaji = %i \n" , mengajikah);
}
static void alarmMulaiMengaji(){
	return;
	gchar text [255];
	sprintf(text,"%s.0gg",waktuGetTanggal());
	mengajikah = TRUE;
	soundPlay("1.mp3",1);
}
//! 
static void alarmUpdateListWib(){
	///home/zizou/3/build/music/Alarm.mp3
	int i;
	char * bagian = "WIB";
	sqlite_ *sqlite = databaseGetObject();
	gchar *sql = " select Jam,X,Alarm from isi where dal = ? and Bagian=?";	
	int rc = sqlite3_prepare_v2( sqlite->db,sql , strlen (sql)+1 , &sqlite->stmt, NULL); 
	if(rc == SQLITE_OK) {
		sqlite3_bind_double(sqlite->stmt	,1	, waktuGetHari()	  								);
		sqlite3_bind_text  (sqlite->stmt	,2	, bagian		, strlen(bagian), SQLITE_TRANSIENT	);
		rc = sqlite3_step(sqlite->stmt);
//		int ncols = sqlite3_column_count(sqlite->stmt);
		while(rc == SQLITE_ROW) {
			char *a = g_strdup_printf ("%s", sqlite3_column_text(sqlite->stmt, 0));
			wib =  g_list_append(wib	,  a )	;
			char *b = g_strdup_printf ("%s", sqlite3_column_text(sqlite->stmt, 1));
			wib =  g_list_append(wib	,  b )	;
			char *c = g_strdup_printf ("%s", sqlite3_column_text(sqlite->stmt, 2));
			wib =  g_list_append(wib	,  c )	;
			rc = sqlite3_step(sqlite->stmt);
		}
	}
	else{
			fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(sqlite->db));
	}
	sqlite3_finalize(sqlite->stmt);
}
//! 
void alarmUpdateListWis(){
	int i;
	char * bagian = "WIS";
	sqlite_ *sqlite = databaseGetObject();
	gchar *sql = " select Jam,X,Alarm from isi where dal = ? and Bagian=?";	
	int rc = sqlite3_prepare_v2( sqlite->db,sql , strlen (sql)+1 , &sqlite->stmt, NULL); 
	if(rc == SQLITE_OK) {
		sqlite3_bind_double(sqlite->stmt	,1	, waktuGetHari()	  								);
		sqlite3_bind_text  (sqlite->stmt	,2	, bagian		, strlen(bagian), SQLITE_TRANSIENT	);
		rc = sqlite3_step(sqlite->stmt);
		int ncols = sqlite3_column_count(sqlite->stmt);
		while(rc == SQLITE_ROW) {
			//! anda tidak bissa melakukan hal ini
			//! char *a = sqlite3_column_text(sqlite->stmt, i);
			char *a = g_strdup_printf ("%s", sqlite3_column_text(sqlite->stmt, 0));
			wis =  g_list_append(wis	,  a )	;
			char *b = g_strdup_printf ("%s", sqlite3_column_text(sqlite->stmt, 1));
			wis =  g_list_append(wis	,  b )	;				
			char *c = g_strdup_printf ("%s", sqlite3_column_text(sqlite->stmt, 2));
			wis =  g_list_append(wis	,  c )	;
			rc = sqlite3_step(sqlite->stmt);
		}
	}
	else{
			fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(sqlite->db));
	}
	sqlite3_finalize(sqlite->stmt);
}
//! tempat meng-update hari
void alarmUpdateList(){
	if(g_list_length (wib)>0){
		g_list_foreach(wib, (GFunc) g_free, NULL);
		g_list_free(wib);
		wib = NULL;
	}
	if(g_list_length (wis)>0){
		g_list_foreach(wis, (GFunc) g_free, NULL);
		g_list_free(wis);
		wis = NULL;
	}
	alarmUpdateListWib();
	alarmUpdateListWis();	
	alarmResetJarak();
}
