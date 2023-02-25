#include "tcp.h"
int main(int agrc, char *argv[])
{
    int s;// socket描述符
    struct sockaddr_in server_addr;//服务器地址结构
    int err;// 返回值
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        printf("socket error!\n");
        return -1;
    }
    // 设置服务器地址
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    // 将用户输入的字符串类型的ip地址转换为整型，运行"# ./client hostname"，输入的hostname为字符串类型
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    // 连接服务器
    connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
    process_conn_client(s);
    close(s);
    return 0;
}
