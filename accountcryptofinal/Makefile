account : monitor.o Search.o Modify.o Analysis.o login.o chatting.o
		gcc -g -o account monitor.o Search.o Modify.o Analysis.o login.o chatting.o -pthread -lssl -lcrypto

monitor.o : type.h monitor.c
		gcc -c monitor.c

Search.o : type.h Search.c
		gcc -c Search.c

Modify.o : type.h Modify.c
		gcc -c Modify.c

Analysis.o : type.h Analysis.c
		gcc -c Analysis.c

login.o : type.h login.c
		gcc -c login.c -pthread

chatting.o : type.h chatting.c
		gcc -c chatting.c -pthread -lssl -lcrypto
