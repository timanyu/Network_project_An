CC=gcc -g
VPATH=. \
	 :./database \
	 :./io \
	 :./network \
	 :./queue \
	 :./thread \
	 :./logic/user

file=server.o  \
 	 database.o \
 	 io.o \
	 network.o \
 	 queue.o\
 	 thread.o \
 	 user.o
	  
all:server remove_file

server: $(file)
	gcc -o server $(file) -lpthread -lmysqlclient
$(file):

remove_file:
	rm *.o

clean:
	rm server