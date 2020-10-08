
all: msg
msg: main.o client.o receive_message.o
	$(CC) $^ -o $@ 
main.o: main.c
	$(CC) $< -c -o $@
client.o: client.c
	$(CC) $< -c -o $@
# server.o: server.c
# 	$(CC) $< -c -o $@
receive_message.o: receive_message.c
	$(CC) $< -c -o $@

.PHONY: clean
clean: 
	$(RM) $(targets) *.o
