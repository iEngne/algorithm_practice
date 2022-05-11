/**
 * @file socket_client.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("121.196.186.105");  //具体的IP地址
    serv_addr.sin_port = htons(6806);  //端口
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   
    //读取服务器传回的数据
    char buffer[40] = "hello.stranger";
    //read(sock, buffer, sizeof(buffer)-1);
    write(sock, buffer, sizeof(buffer));
    printf("client: %s\n", buffer);
   
    //关闭套接字
    close(sock);

    return 0;
}