// Server              Client()
// socket()           socket()
// bind()
// listen()
// accept()<--三次握手--connect()
// read()    <-----   write()
// write()   ----->   read()
// close()   ----->    close()

#include "tcp.h"
#define BACKLOG 2
int main(int agrc, char *argv[])
{
    int s_server, s_client;// 服务器和客户端的socket描述符
    // 服务器和客户端的地址结构
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int err;// 返回值
    pid_t pid;// 分叉的进行ID
    /*建立套接字*/
    s_server = socket(AF_INET, SOCK_STREAM, 0);// ipv4  stream  
    if (s_server < 0){
        printf("socket error\n");
        return -1;
    }
    // 设置服务器地址和
    bzero(&server_addr, sizeof(server_addr));// set to zero
    server_addr.sin_family = AF_INET; // ipv4和前面socket一样
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);// 本机地址
    server_addr.sin_port = htons(PORT); // 端口
    // 绑定地址到套接字描述符
    err = bind(s_server, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (err < 0){
        printf("bind error!\n");
        return -1;
    }
    // 设置侦听队列，BACKLOG=2，可以同时处理两个客户端的连接请求
    err = listen(s_server, BACKLOG);
    if (err < 0){
        printf("listen error!\n");
        return -1;
    }
    // 处理过程
    for(;;){
        int addrlen = sizeof(struct sockaddr);
        s_client = accept(s_server, (struct sockaddr*)&client_addr, &addrlen);
        // 接受客户端连接
        if (s_client < 0){ // 出错重新开始循环
            continue;
        }
        // 建立一个新的进程来处理来到的连接
        pid = fork();     // 分叉进程
        if (pid == 0){    // 子进程中
            close(s_server); // 子进程中关闭服务器的侦听去处理连接
            process_conn_server(s_client);
        }
        else {
            close(s_client);// 在父进程中关闭客户端的连接
        }
    }
    return 0;
}