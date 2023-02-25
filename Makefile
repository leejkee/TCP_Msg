all:preprocess client server
preprocess:
	gcc -c tcp_process.c
	gcc -c tcpserver.c
	gcc -c tcpclient.c
client:tcp_process.o tcpclient.o
	gcc -o client tcp_process.o tcpclient.o
server:tcp_process.o tcpserver.o
	gcc -o server tcp_process.o tcpserver.o
clean:
	rm -f client server *.o