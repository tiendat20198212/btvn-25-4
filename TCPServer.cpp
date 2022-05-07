#include <stdio.h>
#include <WinSock2.h>
#include <string.h> 
#include <stdlib.h> 
#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

void ToUp(char* p);

int main()
{
    // Khoi tao thu vien
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Tao socket
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi server
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    // Gan cau truc dia chi voi socket
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    // Chuyen sang trang thai cho ket noi
    listen(listener, 5);

    // Cho ket noi moi
    SOCKET client = accept(listener, NULL, NULL);

    FILE* helloClientFile = fopen("C:\\Users\\DELL\\Desktop\\Test\\hello.txt", "r");

    FILE* clientMessage = fopen("C:\\Users\\DELL\\Desktop\\Test\\input.txt", "a");

    int ret;

    char buf[256];

    char buffer[2048];

    // gửi tin nhắn hello cho client từ file
    while (!feof(helloClientFile)) {
        ret = fread(buffer, 1, sizeof(buffer), helloClientFile);

        if (ret > 0)
        {
            send(client, buffer, ret, 0);
        }
    }

   
    while (1)
    {
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
            break;

        // Them ky tu ket thuc xau va in ra man hinh
        buf[ret] = 0;
        printf("Du lieu nhan duoc tu client: %s", buf);
        
        // GHI VÀO FILE
        fwrite(buf, 1, ret, clientMessage);
        fwrite("\n", sizeof(char), 1, clientMessage);
    }

    fclose(helloClientFile);

    fclose(clientMessage);

    // Dong ket noi
    closesocket(client);
    closesocket(listener);
    WSACleanup();
}

