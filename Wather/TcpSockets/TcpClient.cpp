#define TSP_SOKETS_DLL
#include "Header.h"

TcpClient::TcpClient()
{  
    //2. создание клиентского сокета
   _clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_clientSocket == INVALID_SOCKET) {
        throw SocketException("socket failed with error: ");       
    }
}

TcpClient::TcpClient(SOCKET socket)
{
	_clientSocket = socket;
}

TcpClient::TcpClient(TcpClient&& tcpClient)
{
    _clientSocket = tcpClient._clientSocket;
    tcpClient._clientSocket = INVALID_SOCKET;
}

void TcpClient::operator=(TcpClient&& tcpClient)
{
    if (this == &tcpClient)
        return;

    if (_clientSocket != INVALID_SOCKET)
        closesocket(_clientSocket);

    _clientSocket = tcpClient._clientSocket;
    tcpClient._clientSocket = INVALID_SOCKET;
}

TcpClient::~TcpClient()
{
    if(_clientSocket != INVALID_SOCKET)
        closesocket(_clientSocket);   
}

void TcpClient::connect(string ipAddress, unsigned short port)
{
    //инициализация структуры, для указания ip адреса и порта сервера с которым мы хотим соединиться
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ipAddress.c_str(), &addr.sin_addr);
    addr.sin_port = htons(port);

    //3. Соединяемся с сервером
    int iResult = ::connect(_clientSocket, (SOCKADDR*)&addr, sizeof(addr));
    if (iResult == SOCKET_ERROR)
    {
        throw SocketException("Unable to connect to server!");
    }
}

string TcpClient::receive()
{      
    const size_t BUFFERSIZE = 1024;
    char resBuf[BUFFERSIZE];
    int respLength = 0;
    string answer;

    do {
        respLength = recv(_clientSocket, resBuf, BUFFERSIZE, 0);
        if (respLength > 0) {
            answer += string(resBuf).substr(0, respLength);
        }
        else {
            cout << "recv failed: " << WSAGetLastError() << endl;
            closesocket(_clientSocket);
            WSACleanup();
            throw SocketException("Unable to connect to server!");
        }

    } while (respLength == BUFFERSIZE);

    return answer;
}

void TcpClient::send(string data)
{
    if (::send(_clientSocket, data.c_str(), data.length() + 1, 0) == SOCKET_ERROR) 
    {
        throw SocketException("send failed: ");       
    }
}

void TcpClient::shutdown()
{
    int iResult = ::shutdown(_clientSocket, SD_BOTH);
    if (iResult == SOCKET_ERROR) {
        throw SocketException("shutdown failed: ");        
    }   
}

const SOCKET* TcpClient::GetSocket() const
{
    return &_clientSocket;
}

void TcpClient::SetSocket(const SOCKET& soket)
{
    _clientSocket = soket;
}
