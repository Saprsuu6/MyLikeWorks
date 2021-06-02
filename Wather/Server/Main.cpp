#pragma comment(lib, "../x64/Debug/TcpSockets.lib")
#include "../TcpSockets/Header.h"

#include <Windows.h>
#include <list>
#include <algorithm>

list<TcpClient*> clients;
CRITICAL_SECTION csClients;

char hostname[255] = "api.openweathermap.org";
addrinfo* result = NULL;
addrinfo hints;
SOCKET connectSocket = INVALID_SOCKET;
addrinfo* ptr = NULL;

DWORD WINAPI ThreadProc(LPVOID lpParameter);

int main()
{
    InitializeCriticalSection(&csClients);
    try {
        
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        int iResult = getaddrinfo(hostname, "http", &hints, &result);
        if (iResult != 0) {
            cout << "getaddrinfo failed with error: " << iResult << endl;
            WSACleanup();
            return 3;
        }

        for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
            connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            if (connectSocket == INVALID_SOCKET) {
                printf("socket failed with error: %ld\n", WSAGetLastError());
                WSACleanup();
                return 1;
            }

            iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(connectSocket);
                connectSocket = INVALID_SOCKET;
                continue;
            }
            break;
        }

        TcpServer server;
        server.bind("127.0.0.1", 1111);

        cout << "server bind 127.0.0.1 : 1111" << endl;

        server.listen();
        cout << "server listening..." << endl;

        while (true)
        {
            //принимаем запрос на соединение
            TcpClient* client = server.accept();

            EnterCriticalSection(&csClients);
            clients.push_back(client);
            LeaveCriticalSection(&csClients);

            cout << "client accepted" << endl;

            HANDLE hThread = CreateThread(NULL, 0, ThreadProc, client, 0, NULL);
            CloseHandle(hThread);
        }

        DeleteCriticalSection(&csClients);
    }
    catch (SocketException& ex)
    {
        cout << ex.what() << endl;

        DeleteCriticalSection(&csClients);
    }

}

DWORD __stdcall ThreadProc(LPVOID lpParameter)
{
    TcpClient* client = (TcpClient*)lpParameter;
    string town;
    string uri;
    string massage;
    string answer;

    while (true)
    {
        try {
            //принимаем сообщение от клиента
            string request = client->receive();
            cout << "Reqest: " << request << endl;

            if (strstr(request.c_str(), "<TOWN>") != NULL) {
                request.replace(request.find("<TOWN>"), 6, "");
                town = request;
            }

            else if (request == "<FIND>") {
                uri = "/data/2.5/weather?q=";
                uri += town + "&appid=" + "75f6e64d49db78658d09cb5ab201e483&mode=json&units=metric";

                massage = "GET " + uri + " HTTP/1.1\n";
                massage += "Host: " + string(hostname) + "\n";
                massage += "Accept: */*\n";
                massage += "Accept-Encoding: gzip, deflate, br\n";
                massage += "Connection: close\n";
                massage += "\n";

                town.clear();

                if (send(connectSocket, massage.c_str(), massage.length(), 0) == SOCKET_ERROR) {
                    cout << "send failed: " << WSAGetLastError() << endl;
                    closesocket(connectSocket);
                    WSACleanup();
                    return 5;
                }
                cout << "send data" << endl;

                const size_t BUFFERSIZE = 1024;
                char resBuf[BUFFERSIZE];
                int respLength;

                do {
                    respLength = recv(connectSocket, resBuf, BUFFERSIZE, 0);
                    if (respLength > 0) {
                        answer += string(resBuf).substr(0, respLength);
                    }
                    else {
                        cout << "recv failed: " << WSAGetLastError() << endl;
                        closesocket(connectSocket);
                        WSACleanup();
                        return 6;
                    }

                } while (respLength == BUFFERSIZE);

                answer += "<JSON>";

                client->send(answer);
            }
        }
        catch (SocketException& ex)
        {
            if (ex.getCode() == 10054 || ex.getCode() == 50000)
            {
                cout << "client closed" << endl;

                auto it = find(clients.begin(), clients.end(), client);
                delete* it;

                EnterCriticalSection(&csClients);
                clients.erase(it);
                LeaveCriticalSection(&csClients);

                return 0;
            }
        }
    }
    return 0;
}
