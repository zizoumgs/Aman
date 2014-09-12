CC = gcc
CXX = g++

CFLAGS = -Wall                 \
    -DG_DISABLE_DEPRECATED          \
    -DGDK_DISABLE_DEPRECATED     \
    -DGDK_PIXBUF_DISABLE_DEPRECATED \
    -DGTK_DISABLE_DEPRECATED \
    -w
#LDFLAGS=-lrt -lm -static -L./ -llibunique
#LDFLAGS= -static -L./ -llibunique-1.0.a
# cara sepeti dibawah ini untuk mencari bin.sh    
LIBS = `pkg-config gtk+-2.0 --cflags --libs gstreamer-0.10 sqlite3 unique-1.0 libnotify` 
#./single/lib/libunique-1.0.a 
#end

#mencari directory
INCLUDE = -I"." -I"./sqlite" -I"./single/include/unique-1.0"
#end

FILE_LAIN = menu.c modif.c global.c waktu.c sound.c setting.c alarm.c tray.c

SOURCE = child.c database_.c main.c table.c $(FILE_LAIN) 
NAMAAPP = main
$(NAMAAPP): $(SOURCE) 		
					    $(CC) $(LDFLAGS) $(LIBS) $(INCLUDE) $(SOURCE) -o $(NAMAAPP) $(CFLAGS) 
sapu:
							rm -f *.o core $(NAMAAPP)
    																							
