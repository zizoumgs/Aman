#include "waktu.h"
#include "global.h"
#include "alarm.h"
#include "child.h"
typedef struct _waktu{
	gint jam_wis;
	gint mnt_wis;
	gint dtk_wis;	
	gint hari;
	gchar *tanggal;
}waktu_;
waktu_ *waktu;
static	time_t curtime;
static struct tm *loctime;
static gint waktuGetTafawut(gchar* bulan_char , gchar* tanggal_char){
	gint bulan 			=	globalConStrToInt( bulan_char )		;
	gint tanggal	 	= 	globalConStrToInt( tanggal_char )	;
	gint tafawut;
	if ( bulan == 1 )
	{
		if ( (tanggal>=1)&&(tanggal <3) )
		{
			tafawut = 31 ;
		}
		else if ( (tanggal>=3)&&(tanggal <6) )
		{
			tafawut = 30 ;
		}
		else if ( (tanggal>=6)&&(tanggal <9) )
		{
			tafawut = 28 ;
		}
		else if ( (tanggal>=9)&&(tanggal <12) )
		{
			tafawut = 27 ;
		}
		else if ( (tanggal>=12)&&(tanggal <15) )
		{
			tafawut = 26 ;
		}
		else if ( (tanggal>=15)&&(tanggal <18) )
		{
			tafawut = 25 ;
		}
		else if ( (tanggal>=18)&&(tanggal <21) )
		{
			tafawut = 24 ;
		}
		else if ( (tanggal>=21)&&(tanggal <24) )
		{
			tafawut = 23 ;
		}
		else if ( (tanggal>=24)&&(tanggal <27) )
		{
			tafawut = 22 ;
		}
		else
		{
			tafawut = 21 ;
		}
	}

	//bulan dua coi alias februari

	else if ( bulan == 2 )
	{
		if ( (tanggal>=1)&&(tanggal <27) )
		{
			tafawut = 20 ;
		}
		else
		{
			tafawut = 21 ;
		}
	}

	//bulan tiga coi alias maret

	else if (bulan == 3 )
	{
		if ( (tanggal>=1)&&(tanggal <3) )
		{
			tafawut = 21 ;
		}
		else if ( (tanggal>=3)&&(tanggal <9) )
	    {
			tafawut = 22 ;
		}
		else if ( (tanggal>=9)&&(tanggal <12) )
	    {
			tafawut = 23 ;
		}
		else if ( (tanggal>=12)&&(tanggal <18) )
	    {
			tafawut = 24 ;
		}
		else if ( (tanggal>=18)&&(tanggal <21) )
	    {
			tafawut = 25 ;
		}
		else if ( (tanggal>=21)&&(tanggal <24) )
	    {
			tafawut = 26 ;
		}
		else if ( (tanggal>=24)&&(tanggal <27) )
	    {
			tafawut = 27 ;
		}
		else if ( (tanggal>=27)&&(tanggal <30) )
	    {
			tafawut = 28 ;
		}
		else
	    {
			tafawut = 29 ;
		}
	}
	else if (bulan ==4)
	{
		if ( (tanggal >=1) && (tanggal<3))
		{
			tafawut = 30 ;
		}
		else if ( (tanggal >=3) && (tanggal<9))
		{
			tafawut = 31 ;
		}
		else if ( (tanggal >=9) && (tanggal<12))
		{
			tafawut = 32 ;
		}
		else if ( (tanggal >=12) && (tanggal<15))
		{
			tafawut = 33 ;
		}
		else if ( (tanggal >=15) && (tanggal<18))
		{
			tafawut = 34 ;
		}
		else if ( (tanggal >=18) && (tanggal<24))
		{
			tafawut = 35 ;
		}
		else if ( (tanggal >=24) && (tanggal<30))
		{
			tafawut = 36 ;
		}
		else
		{
			tafawut = 37 ;
		}
	}
	else if (bulan == 5 )
	{
		if ( (tanggal >=1) && (tanggal<9))
		{
			tafawut = 37 ;
		}
		else if ( (tanggal >=9) && (tanggal<24))
		{
			tafawut = 38 ;
		}
		else
		{
			tafawut = 37 ;
		}
	}
	else if ( bulan == 6 )
	{
		if ( (tanggal >=1 ) && (tanggal < 3 ) )
		{
			tafawut = 37 ;
		}
		else if ( (tanggal >=3 ) && (tanggal < 9 ) )
		{
			tafawut = 36 ;
		}
		else if ( (tanggal >=9 ) && (tanggal < 12 ) )
		{
			tafawut = 35 ;
		}
		else if ( (tanggal >=12 ) && (tanggal < 18 ))
		{
			tafawut = 34 ;
		}
		else if ( (tanggal >=18 ) && (tanggal < 24 ) )
		{
			tafawut = 33 ;
		}
		else if ( (tanggal >=24 ) && (tanggal < 27 ) )
		{
			tafawut = 32 ;
		}
		else
		{
			tafawut = 31 ;
		}
	}
	else if (bulan == 7 )
	{
		if ((tanggal >=1 ) && (tanggal <3 ))
		{
			tafawut = 31 ;
		}
		else if ((tanggal >=3 ) && (tanggal <12 ))
		{
			tafawut = 29 ;
		}
		else
		{
			tafawut = 28 ;
		}
	}
	else if (bulan ==8 )
	{
		if ((tanggal >=1 ) && (tanggal <9))
		{
			tafawut = 28 ;
		}
		else if ((tanggal >=9 ) && (tanggal <15))
		{
			tafawut = 29 ;
		}
		else if ((tanggal >=15 ) && (tanggal <21))
		{
			tafawut = 30 ;
		}
		else if ((tanggal >=21 ) && (tanggal <24))
		{
			tafawut = 31 ;
		}
		else if ((tanggal >=24 ) && (tanggal <27))
		{
			tafawut = 32 ;
		}
		else if ((tanggal >=27 ) && (tanggal <30))
		{
			tafawut = 33 ;
		}
		else
		{
			tafawut = 34 ;
		}
	}
	else if (bulan == 9 )
	{
		if (( tanggal >=1 ) && (tanggal <3))
		{
		    tafawut =34 ;
		}
		else if (( tanggal >=3 ) && (tanggal <9))
		{
		    tafawut =35 ;
		}
		else if (( tanggal >=9 ) && (tanggal <12))
		{
		    tafawut =36 ;
		}
		else if (( tanggal >=12 ) && (tanggal <15))
		{
		    tafawut =37 ;
		}
		else if (( tanggal >=15 ) && (tanggal <18))
		{
		    tafawut =38 ;
		}
		else if (( tanggal >=18 ) && (tanggal <21))
		{
		    tafawut =39 ;
		}
		else if (( tanggal >=21 ) && (tanggal <24))
		{
		    tafawut =40 ;
		}
		else if (( tanggal >=24 ) && (tanggal <27))
		{
		    tafawut =42 ;
		}
		else if (( tanggal >=27 ) && (tanggal <30))
		{
		    tafawut =43 ;
		}
		else
		{
		    tafawut = 44 ;
		}
	}
	else if ( bulan == 10 )
	{
	    if ( (tanggal >= 1 )&& (tanggal <3))
	    {
	        tafawut =44 ;
	    }
        else if (( tanggal >=3 ) && (tanggal <12))
		{
		    tafawut =45 ;
		}
		else if (( tanggal >=12 ) && (tanggal <15))
		{
		    tafawut =47 ;
		}
		else if (( tanggal >=15 ) && (tanggal <18))
		{
		    tafawut =48 ;
		}
		else if (( tanggal >=18 ) && (tanggal <27))
		{
		    tafawut =49 ;
		}
		else
		{
		    tafawut =50 ;
		}
	}
	else if (bulan == 11 )
	{
	    if ((tanggal >=1) && (tanggal <15))
	    {
	        tafawut = 50 ;
	    }
	    else if ((tanggal >=15)&&(tanggal <21))
	    {
	        tafawut = 49 ;
	    }
	    else if ((tanggal >=21)&&(tanggal <24))
	    {
	        tafawut = 48 ;
	    }
	    else if ((tanggal >=24)&&(tanggal <30))
	    {
	        tafawut = 47 ;
	    }
	    else
	    {
	        tafawut = 45 ;
	    }
	}
	else
	{
	    if ((tanggal >=1)&&(tanggal <3))
	    {
	        tafawut = 45 ;
	    }
        else if ((tanggal >=3)&&(tanggal <6))
	    {
	        tafawut = 44 ;
	    }
	    else if ((tanggal >=6)&&(tanggal <9))
	    {
	        tafawut = 43 ;
	    }
	    else if ((tanggal >=9)&&(tanggal <12))
	    {
	        tafawut = 42 ;
	    }
	    else if ((tanggal >=12)&&(tanggal <15))
	    {
	        tafawut = 41 ;
	    }
	    else if ((tanggal >=15)&&(tanggal <18))
	    {
	        tafawut = 39 ;
	    }
	    else if ((tanggal >=18)&&(tanggal <21))
	    {
	        tafawut = 38 ;
	    }
	    else if ((tanggal >=21)&&(tanggal <24))
	    {
	        tafawut = 37 ;
	    }
	    else if ( (tanggal >=24)&&(tanggal <27) )
	    {
	        tafawut = 35 ;
	    }
	    else if ((tanggal >=27)&&(tanggal <30))
	    {
	        tafawut = 34 ;
	    }
	    else
	    {
	        tafawut = 32 ;
	    }
	}
	return tafawut;
}
static gchar *waktuPutZero( gint value ){
	if(value < 10){
		return g_strdup_printf ("0%d", value);
	}
	else{
		return g_strdup_printf ("%d", value);
	}
}
static void waktuSetHari(const gchar* hari){
	waktu->hari = globalConStrToInt(hari);
}
static void waktuSetWis(gchar **kalender){
	gint tafawut = waktuGetTafawut(kalender[1],kalender[2]);
//	g_print("\n%d,Bulan%s,Tanggal%s",tafawut,kalender[1],kalender[2]);
	waktu->jam_wis = globalConStrToInt( kalender[3] );
	waktu->mnt_wis = globalConStrToInt( kalender[4] );
	waktu->dtk_wis = globalConStrToInt( kalender[5] );	
	

	waktu->mnt_wis += tafawut ;
	if(waktu->mnt_wis >= 60){
		waktu->mnt_wis -= 60;
		waktu->jam_wis++;
		if(waktu->jam_wis == 24)
			waktu->jam_wis -= 24 ;
	}
//	g_free(bufTime);	
}
static void waktuUpdate(){
	char bufTime [128];
	strftime(bufTime, 128, "%F-%k-%M-%S-%u ", loctime);//is equivalent to `%Y-%m-%d'
	gchar **kalender = g_strsplit_set(bufTime,"-",7);		//is equivalent to ``%H:%M:%S'
	waktuSetWis(kalender);
	waktuSetHari(kalender[6]);
	//! settanggal
	g_free(waktu->tanggal);
	waktu->tanggal  = strdup(kalender [2]);
	//! free kalender
	g_strfreev (kalender);
}
char * waktuGetTanggal(){
	return waktu->tanggal;
}
gchar * waktuGetIstiwak(gboolean withDetik){
	char buffer[32];
	if(withDetik){
		g_snprintf(buffer, sizeof(buffer), "%s:%s:%s", waktuPutZero(waktu->jam_wis),waktuPutZero(waktu->mnt_wis),waktuPutZero( waktu->dtk_wis) );
		return g_strdup_printf ("%s WIS", buffer);
	}
	g_snprintf(buffer, sizeof(buffer), "%s:%s", waktuPutZero(waktu->jam_wis),waktuPutZero(waktu->mnt_wis));
	return g_strdup_printf ("%s", buffer);
}
gchar * waktuGetWib(gboolean withDetik){
	if(withDetik){
		return g_strdup_printf ("%s:%s:%s WIB"
									,waktuPutZero(loctime->tm_hour)
									,waktuPutZero(loctime->tm_min)
									,waktuPutZero(loctime->tm_sec) );
	}
	return g_strdup_printf ("%s:%s"
									,waktuPutZero(loctime->tm_hour)
									,waktuPutZero(loctime->tm_min));
}
gchar * waktuGet( gboolean wib ){
	if(wib){
		return waktuGetWib(TRUE);
	}
	else{
		return waktuGetIstiwak(TRUE);
	}
}
void waktuCreate(GtkWidget* widget){
	waktu = struct_new(waktu_);
	curtime = time(NULL);
	loctime = localtime(&curtime);
	waktu->tanggal = strdup("");
	waktuUpdate();
	childCreate(widget);
	alarmCreate(widget);
}
void waktuQuit(){
}
void waktuTimer(GtkWidget* widget){
	curtime = time(NULL);
	loctime = localtime(&curtime);
	waktuUpdate();
	alarmTimer(	 waktu->hari	);
	gtk_widget_queue_draw(widget);
}
gint* waktuGetWis(){
	gint *oke [] = { waktu->jam_wis,waktu->mnt_wis,waktu->dtk_wis};
	return oke;
}
gint waktuGetHari(){
	return waktu->hari;
}
