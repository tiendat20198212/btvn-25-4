#include <stdio.h>
#include <WinSock2.h>
#include <string.h> 
#include <stdlib.h> 
#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

#define INFO_BUFFER_SIZE 32767

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8000);

    system("pause");

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Ket noi khong thanh cong - %d\n", ret);
        return 1;
    }

    int action = 1;

   

    char buffer[2048];

    while (true) {
      
        int retHello = recv(client, buffer, sizeof(buffer), 0);
        if (retHello < 0) {
            break;
        }
        buffer[retHello] = 0;
        printf("%s\n", buffer);
        break;
    }

    

        printf("Nhap noi dung tin nhan gui den server\n");     
        char buf[256];
        while (1)
        {
            printf("Nhap xau ky tu: ");
            fgets(buf, sizeof(buf), stdin);

            // dừng chương trình khi ấn exit
            if (strncmp(buf, "exit", 4) == 0)
                break;

            send(client, buf, strlen(buf), 0);
        }

        closesocket(client);

        WSACleanup();
    }
