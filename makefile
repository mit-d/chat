
all: msg
msg: main.o msgclient.o msgd.o
	$(CC) $^ -o $@ 
main.o: main.c
	$(CC) $< -c -o $@
msgclient.o: msgclient.c
	$(CC) $< -c -o $@
# server.o: server.c
# 	$(CC) $< -c -o $@
msgd.o: msgd.c
	$(CC) $< -c -o $@

.PHONY: clean
clean: 
	$(RM) $(targets) *.o
