#pragma comment (lib, "Ws2_32.lib")
#include <Winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void CreateFile(const char* name, ofstream& create_file)
{
    char value;
    create_file.open(name, ios::binary | ios::out);
    if (create_file.is_open())
    {
        for (int i = 0; i < 250; i++)
        {
            value = rand() % 127+90;
            create_file.write((char*)&value, sizeof(char));
        }
    }
    else
    {
        cout << "Not write file\n";
    }
}

int main()
{
    ofstream create_file;
    srand(time(0));
    string name = "Text.txt";
    CreateFile(name.c_str(), create_file);
    create_file.close();
    //1. инициализаци€ "Ws2_32.dll" дл€ текущего процесса
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);

    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {

        cout << "WSAStartup failed with error: " << err << endl;
        return 1;
    }

    //2. создание клиентского сокета
    SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET) {
        cout << "socket failed with error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 2;
    }

    //инициализаци€ структуры, дл€ указани€ ip адреса и порта сервера с которым мы хотим соединитьс€
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    addr.sin_port = htons(27015);

    //3. —оедин€емс€ с сервером
    int iResult = connect(connectSocket, (SOCKADDR*)&addr, sizeof(addr));
    if (iResult == SOCKET_ERROR) {
        cout << "Unable to connect to server!\n";
        closesocket(connectSocket);
        WSACleanup();
        return 3;
    }
 //отправка сообщени€
    char answer[3];
    send(connectSocket, "WinSockets.rar", strlen("WinSockets.rar") + 1, 0);
    while (recv(connectSocket, answer, 3, 0) == 0)
    {
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }
    ifstream read_file;
    read_file.open("WinSockets.rar", ios::in | ios::binary);
    if (read_file.is_open())
    {
        read_file.seekg(ifstream::end);
        int size = read_file.tellg();
        read_file.seekg(ifstream::beg);
        char sendData[1024];
        while(!read_file.eof())
        {
            if (size < 1024)
            {
                read_file.read((char*)&sendData, size);

                if (send(connectSocket, sendData, size, 0) == SOCKET_ERROR) {
                    cout << "send failed: " << WSAGetLastError() << endl;
                    closesocket(connectSocket);
                    WSACleanup();
                    return 4;
                }
                if (recv(connectSocket, answer, 3, 0) >= 0) {
                    continue;
                }
                else
                {
                    cout << "Dont get answer";
                    return 1;
                }
            }
            else if (size >= 1024)
            {
                read_file.read((char*)&sendData, 1024);

                if (send(connectSocket, sendData, 1024, 0) == SOCKET_ERROR) {
                    cout << "send failed: " << WSAGetLastError() << endl;
                    closesocket(connectSocket);
                    WSACleanup();
                    return 4;
                }
                if (recv(connectSocket, answer, 3, 0) >= 0) {
                    continue;
                }
                else
                {
                    cout << "Dont get answer";
                    return 1;
                }
            }
        }
    }
    else
    {
        cout << "File not open";
    }
    read_file.close();
    send(connectSocket, "END", 4, 0);
    cout << "send data" << endl;

    char sendAccept[100] = "accept responce";
    //отправка сообщени€
    if (send(connectSocket, sendAccept, strlen(sendAccept)+1, 0) == SOCKET_ERROR) {
        cout << "send failed: " << WSAGetLastError() << endl;
        closesocket(connectSocket);
        WSACleanup();
        return 4;
    }

    //отключает отправку и получение сообщений сокетом
    iResult = shutdown(connectSocket, SD_BOTH);
    if (iResult == SOCKET_ERROR) {
        cout << "shutdown failed: " << WSAGetLastError() << endl;
        closesocket(connectSocket);
        WSACleanup();
        return 8;
    }

    system("PAUSE");

    closesocket(connectSocket);
    WSACleanup();

    return 0;
}
