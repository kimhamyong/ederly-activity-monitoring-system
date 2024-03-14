#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<conio.h>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32");

#define BUFSIZE 512
#define MAX_ELEMENT 200

typedef struct {
    int key;
}element;

int main(int argc, char* argv[]) {
    int retval;

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return -1;

    //socket()
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("(1) socket 생성 완료\n"); //Creating a Socket

    //bind()
    SOCKADDR_IN serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(9000);

    bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
    printf("(2) bind 완료\n"); //bind complete

    //listen()
    listen(listen_sock, SOMAXCONN);
    printf("(3) 클라이언트 대기 중 \n"); //Waiting for client

    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    int addrlen;
    char buf[BUFSIZE];

    //accept()
    addrlen = sizeof(clientaddr);
    client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
    printf("(4) 연결 요청 수락\n\n"); //Accept connection request

        int q = 0;
    int set_total = 10; //20->86400
    clock_t start_time2 = clock();

    //recv() & send()
    while (1) {
        retval = recv(client_sock, buf, BUFSIZE, 0);
        buf[retval] = '\0';
        printf("(5) 메시지 수신 : %s\n", buf); //Receive message

        if (strcmp(buf, "exit") == 0)
            break;
    }

    printf("(7) 종료\n"); //end
    closesocket(listen_sock);
    WSACleanup();
    return 0;
}