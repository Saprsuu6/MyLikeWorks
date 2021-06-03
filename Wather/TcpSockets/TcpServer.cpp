#define TSP_SOKETS_DLL
#include "Header.h"

TcpServer::TcpServer()
{
    //2. создание серверного сокета
    _listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (_listenSocket == INVALID_SOCKET) {
        throw SocketException("socket failed with error: ");          
    }
}


TcpServer::~TcpServer()
{
    if (_listenSocket != INVALID_SOCKET)
    {
        closesocket(_listenSocket);
    }
}

void TcpServer::GetAddresInfo()
{
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(hostname, "http", &hints, &result);
    if (iResult != 0) {
        cout << "getaddrinfo failed with error: " << iResult << endl;
        WSACleanup();
        throw SocketException("getting adress failed with error ");
    }
}

void TcpServer::ConnectionWithWatherServer()
{
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (connectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            throw SocketException("connection with wather server failed with error ");
        }

        iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(connectSocket);
            connectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
}

string TcpServer::MakingMassage(const string& town)
{
    string uri = "/data/2.5/weather?q=";
    uri += town + "&appid=" + "75f6e64d49db78658d09cb5ab201e483&mode=json&units=metric";

    string massage = "GET " + uri + " HTTP/1.1\n";
    massage += "Host: " + string(hostname) + "\n";
    massage += "Accept: */*\n";
    massage += "Accept-Encoding: gzip, deflate, br\n";
    massage += "Connection: close\n";
    massage += "\n";

    return massage;
}

void TcpServer::FindWather(const string& massage)
{
    if (send(connectSocket, massage.c_str(), massage.length(), 0) == SOCKET_ERROR) {
        cout << "send failed: " << WSAGetLastError() << endl;
        closesocket(connectSocket);
        WSACleanup();
        throw SocketException("find wather failed with error ");
    }
    cout << "send data" << endl;
}

string TcpServer::GetAnswer()
{
    const size_t BUFFERSIZE = 1024;
    char resBuf[BUFFERSIZE];
    int respLength;
    string answer;

    do {
        respLength = recv(connectSocket, resBuf, BUFFERSIZE, 0);
        if (respLength > 0) {
            answer += string(resBuf).substr(0, respLength);
        }
        else {
            cout << "recv failed: " << WSAGetLastError() << endl;
            closesocket(connectSocket);
            WSACleanup();
            throw SocketException("getting answer failed with error ");
        }

    } while (respLength == BUFFERSIZE);

    return answer;
}

void TcpServer::bind(string ipAddress, unsigned short port)
{
    //инициализация структуры, для указания ip адреса и порта который мы будем слушать
    sockaddr_in addr;
    addr.sin_family = AF_INET;//IPv4
    inet_pton(AF_INET, ipAddress.c_str(), &addr.sin_addr);
    addr.sin_port = htons(port);

    //3. Привязываем к ip адресу и порту
    //::bind - функция из глобальной области видимости
    if (::bind(_listenSocket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) 
    {
        throw SocketException("bind failed with error ");  
    }
}

void TcpServer::listen()
{
    //4. Первести сокет в состояние прослушки
    if (::listen(_listenSocket, SOMAXCONN) == SOCKET_ERROR) 
    {
        throw SocketException( "Listen failed with error: ");       
    }
}

TcpClient* TcpServer::accept()
{
    SOCKET clientSocket = ::accept(_listenSocket, NULL, NULL);
    
    if (clientSocket == INVALID_SOCKET) {

        throw SocketException("accept failed: ");
    }

    return new TcpClient(clientSocket);
}
