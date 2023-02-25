#include "tcp.h"
void process_conn_server(int s)
{
    ssize_t size = 0;
    char buffer[1024];
    for (;;){
        size = read(s, buffer, 1024);// 从套接字读取数据放到缓冲区buffer中
        if (size == 0){
            return ;// 没有数据
        }
        // 构建响应字符，为接收到客户端字节的数量
        sprintf(buffer, "%d bytes altogether\n", size);
        // 发给客户端
        write(s, buffer, strlen(buffer)+1);
    }
}
void process_conn_client(int s){
    ssize_t size = 0;
    char buffer[1024];
    for(;;)
    {
        // 0表示标准输入，1表示标准输出
        // 从标准输入中读取数据放到缓冲区的buffer中
        size = read(0, buffer, 1024);
        if (size > 0){// 读到数据
            write(s, buffer, size);// 发给服务器
            size = read(s, buffer, 1024);// 从服务器读取数据
            write(1, buffer, size);
        }
    }
}