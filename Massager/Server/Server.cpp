#pragma comment(lib, "../x64/Debug/TcpSockets")
#include "../TcpSockets/Sockets.h"

#include <Windows.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<TcpClient*, string>> clients;
CRITICAL_SECTION csClients;

DWORD WINAPI ThreadProc(LPVOID lpParameter);

int main()
{
    InitializeCriticalSection(&csClients);
    try {
        TcpServer server;
        server.bind("127.0.0.1", 1111);

        server.listen();
        cout << "server listening..." << endl;

        while (true) {
            //принимаем запрос на соединение
            TcpClient* client = server.accept();
            
            EnterCriticalSection(&csClients);
            clients.push_back(make_pair(client, "New employer"));
            LeaveCriticalSection(&csClients);
            cout << "client accepted" << endl;
            
            HANDLE hThread = CreateThread(NULL, 0, ThreadProc, client, 0, NULL);
            CloseHandle(hThread);
        }

        DeleteCriticalSection(&csClients);
    }
    catch (SocketException& ex) {
        cout << ex.what() << endl;
        DeleteCriticalSection(&csClients);
    }

}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    TcpClient* client = (TcpClient*)lpParameter;
    pair<TcpClient*, string> pair;
    size_t size = 0;

    while (true) {
        try {
            //принимаем сообщение от клиента
            string request = client->receive();

            // изменение имени
            if (strstr(request.c_str(), "<CHNG>") != NULL) {
                for (auto& item : clients) {
                    item.first->send(request);
                }

                size = clients.size();
                request.replace(request.find("<CHNG>"), 6, "");
                for (size_t i = 0; i < size; i++) {
                    if (clients[i].first == client) {
                        clients[i].second = request;
                    }
                }
            }

            else if (strstr(request.c_str(), "<LIST>") != NULL) {
                request.replace(request.find("<LIST>"), 6, "");
                int index = atoi(request.c_str());

                size = clients.size();
                for (size_t i = 0; i < size; i++) {
                    if (i == index) {
                        pair = clients[i];
                    }
                }
            }

            else if (strstr(request.c_str(), "<TEXT>") != NULL) {
                const SOCKET* soket = client->GetSocket();
                size = clients.size();
                string temp;

                for (size_t i = 0; i < size; i++) {
                    if (soket == clients[i].first->GetSocket()) {
                        temp = clients[i].second + ": ";
                    }
                }

                request.insert(0, temp.c_str());
                pair.first->send(request);
            }
        }
        catch (SocketException& ex) {
           /* if (ex.getCode() == 10054 || ex.getCode() == 50000) {
                cout << "client closed" << endl;

                auto it = find(clients.begin(), clients.end(), );
                
                EnterCriticalSection(&csClients);
                clients.erase(it);
                LeaveCriticalSection(&csClients);

                return 0;
            }*/
        }
    }
    return 0;
}
