#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "setting.h"
#include "database_.h"
#include "global.h"
typedef struct _setting {
    char *x;
    char *y;
    char *w;
    char *h;
} setting_, *settingPtr;

//! g_slice_alloc
//! global variabel agar mudah
gboolean settingCreate(){
	/*
	settingPtr = &setting;
	char *xmlFileName;
	xmlFileName = "aman.xml";
	// Custom function to parse XML file
	parseDoc (xmlFileName);
	*/ 
}
gboolean settingQuit(GtkWidget* window){
	settingSaveWidget(window,1);
}
void settingSetSize(int w,int h){
	
}
void settingSetPos(int x,int y){
}
void settingGetSize(int* w,int* h){
}
void settingGetPos(int* x,int* y){
}
void settingResizeWidget(GtkWidget* w , const char* key){
	const gchar *exe = "select val from app where id < 5 order by val DESC ";
	databaseExe(exe);
	char **data = databaseGetData();
	gtk_window_set_default_size( w, globalConStrToInt(data[1]) , globalConStrToInt(data[2]));
	gtk_window_move( w, globalConStrToInt(data[3]) , globalConStrToInt(data[4]) );	
	gtk_window_set_resizable(w,TRUE);  
	databaseFreeData();
}
void settingSaveWidget(GtkWidget* widget,const gint id){
	sqlite_ *sqlite = databaseGetObject();
	//! sebetulnya harus dilihat dahulu apakah id sudah ada apa belum
	//char *tail;
	int w,h,x,y;
	gtk_window_get_size		(widget,&w,&h);
	gtk_window_get_position	(widget,&x,&y);
	gint oke [4] = {w,h,x,y};
	gchar *sql = "update app set val=? where id = ? ";	
	int xx;
	for(xx=0;xx<5;xx++){
		int rc = sqlite3_prepare_v2( sqlite->db,sql , strlen (sql)+1 , &sqlite->stmt, NULL); 
		if(rc == SQLITE_OK) {
			sqlite3_bind_double(sqlite->stmt	,1	, oke[xx-1]);
			sqlite3_bind_int(sqlite->stmt		,2	, xx		);
			sqlite3_step(sqlite->stmt);
		}
		else{
				fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(sqlite->db));
		}
		sqlite3_finalize(sqlite->stmt);		
	//	free(tail);
	}
}
/*
 * Parse URL Element Node in XML file
 * <url>
 *    <host hash="hash_val_of_hostname">www.example.com</host>
 *    <sctxid>Integer</sctxid>
 * </url>
 */
void parseURL (xmlDocPtr doc, xmlNodePtr cur) {
	xmlChar *key;
	xmlAttrPtr attr;

	// Get the childern Element Node of "url" node
	cur = cur->xmlChildrenNode;

	while (cur != NULL) {
		// check for "host" childern element node of "url" node
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"setting"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			fprintf(stderr,"host: %s\n", key);
			xmlFree(key);
			// search for "hash" attribute in the "host" node
			attr = xmlHasProp(cur, (const xmlChar*)"width");
			// if attr is not found then set it
			if(attr == NULL){
				attr = xmlNewProp(cur, (const xmlChar*)"hash", (const xmlChar*)"12345678");
				key = xmlGetProp(cur, (const xmlChar*)"hash");
				fprintf(stderr,"hash: %s\n", key);
				xmlFree(key);   
			}
			else{
				/* Attribute is available Just retrieve the value and display it */
				key = xmlGetProp(cur, (const xmlChar*)"hash");
				fprintf(stderr, "hash: %s\n", key);
				xmlFree(key);     
			}
		} // end of IF loop " host"
		// check for "sctxid" childern element node of "url" node
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"sctxid"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			fprintf(stderr,"sctxid: %s\n", key);
			xmlFree(key);
		} // end of If loop "sctxid"
		cur = cur->next;
	} // end of While loop
	return;
} // end of parseURL function()
/*
 * Parsing the XML file and Reading the Element Nodes
 */
void parseDoc(char *xmlFileName) {
	xmlDocPtr doc;  // pointer to parse xml Document
	xmlNodePtr cur; // node pointer. It interacts with individual node

	// Parse XML file
	doc = xmlParseFile(xmlFileName);
	
	// Check to see that the document was successfully parsed.
	if (doc == NULL ) {
		fprintf(stderr,"Error!. Document is not parsed successfully. \n");
		return;
	}
	// Retrieve the document's root element.
	cur = xmlDocGetRootElement(doc);
	// Check to make sure the document actually contains something
	if (cur == NULL) {
		fprintf(stderr,"Document is Empty\n");
		xmlFreeDoc(doc);
		return;
	}

	/* We need to make sure the document is the right type.
	* "root" is the root type of the documents used in user Config XML file
	*/
	if (xmlStrcmp(cur->name, (const xmlChar *) "root")) {
		fprintf(stderr,"Document is of the wrong type, root node != root");
		xmlFreeDoc(doc);
		return;
	}

	/* Get the first child node of cur.
   * At this point, cur points at the document root,
   * which is the element "root"
   */
	cur = cur->xmlChildrenNode;
	// This loop iterates through the elements that are children of "root"
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"url"))){
			parseURL (doc, cur);
		}
		cur = cur->next;
	}
	/* Save XML document to the Disk
   * Otherwise, you changes will not be reflected to the file.
   * Currently it's only in the memory
   */
	xmlSaveFormatFile (xmlFileName, doc, 1);

	/*free the document */
	xmlFreeDoc(doc);

	/*
   * Free the global variables that may
   * have been allocated by the parser.
   */
    xmlCleanupParser();

	return;

} // end of XMLParseDoc function
