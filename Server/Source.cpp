#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <string>
#include <sstream>  
#include <winsock2.h>
#include <algorithm>
#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <cmath>
#include <fstream>
#include <map>
#pragma comment(lib, "ws2_32.lib")
struct ClientMessage {
    SOCKET clientSocket;
    std::vector<std::string> clientsWhoRead;
    std::string message;
};
const int PORT = 12345;
const int PORT1 = 54321;
std::map<std::string,std::vector<ClientMessage>> mapMessages;
std::vector<ClientMessage> clientMessages;
struct ThreadParams {
    SOCKET clientSocket;
};
std::string TrimStringToNewline(char* managedString) {
    // Конвертуємо в std::string
    std::string standardString = managedString;

    // Знаходимо позначку нового рядка
    size_t newlinePos = standardString.find('\n');
    //size_t newlinePos = standardString.find('\0');
    // Обрізаємо стрічку до позначки нового рядка (якщо вона є)
    std::string trimmedString = (newlinePos != std::string::npos) ? standardString.substr(0, newlinePos) : standardString;

    return trimmedString;
}
std::vector<std::string> SplitString(std::string managedString, const std::string& delimiter) {
    std::vector<std::string> words;

    // Конвертація в std::string для обробки
    std::string standardString = managedString;

    size_t pos = 0;
    while ((pos = standardString.find(delimiter)) != std::string::npos) {
        words.push_back(standardString.substr(0, pos));
        standardString.erase(0, pos + delimiter.length());
    }

    // Додаємо останнє слово
    words.push_back(standardString);

    return words;
}
bool ContainsString(std::vector<std::string>& vector, std::string searchString) {
    auto it = std::find(vector.begin(), vector.end(), searchString);

    return it != vector.end();
}


 
DWORD WINAPI answMessage(LPVOID n) {
    ThreadParams* params = reinterpret_cast<ThreadParams*>(n);

    SOCKET clientSocket = params->clientSocket;
    char buffer[100];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

    std::string message = TrimStringToNewline(buffer);
    std::vector<std::string> mess = SplitString(message, " ");
    if (bytesReceived > 0) {        
        ClientMessage clientMessage;
        clientMessage.clientSocket = clientSocket;
        if (mess[0] == "_send") {           
            ClientMessage clientMessage;
            clientMessage.clientSocket = clientSocket;
            clientMessage.message = mess[3];
            int a = atoi(mess[1].c_str());
            int b = atoi(mess[2].c_str());
            std::string key = "";
            if (a == 0 || b == 0) {
                std::string q = "";
                for (int i = 3; i < mess.size(); i++) {
                    q += mess[i] + " ";
                }
                clientMessage.message = q;
                clientMessages.push_back(clientMessage);
            }
            else {
                if (a > b) {
                    key += mess[2] + " " + mess[1];
                }
                else {
                    key += mess[1] + " " + mess[2];
                }
                if (mapMessages.find(key) != mapMessages.end()) {

                    auto it = mapMessages.find(key);
                    std::vector<ClientMessage> message1 = it->second;
                    std::string q = "";
                    for (int i = 3; i < mess.size(); i++) {
                        q += mess[i] + " ";

                    }
                    clientMessage.message = q;
                    message1.push_back(clientMessage);
                    mapMessages[key] = message1;
                }
                else {
                    std::vector<ClientMessage> vec;

                    std::string q = "";
                    for (int i = 3; i < mess.size(); i++) {
                        q += mess[i] + " ";
                    }
                    clientMessage.message = q;
                    vec.push_back(clientMessage);
                    mapMessages[key] = vec;
                }
            }
            
        }
    }

    
    std::string request = message; 

    if (mess[0] == "get_messages") {
        ClientMessage cm;
            int a = atoi(mess[1].c_str());
            int b = atoi(mess[2].c_str());
            std::string key = "";
            if (a == 0 || b == 0) {
                std::ostringstream combinedMessages;
                for (auto& client : clientMessages) {
                    //std::cout << client.message << std::endl;
                    if (!ContainsString(client.clientsWhoRead, mess[1])) {

                        combinedMessages << client.message << "\n";

                        client.clientsWhoRead.push_back(mess[1]);
                    }

                }
                std::string allMessages = combinedMessages.str();
                send(clientSocket, allMessages.c_str(), allMessages.size(), 0);
            }
            else {
                if (a > b) {
                    key += std::to_string(b) + " " + std::to_string(a);
                }
                else {
                    key += std::to_string(a) + " " + std::to_string(b);
                }
                std::ostringstream combinedMessages;
                if (mapMessages.size() != 0) {
                    std::vector<ClientMessage>& qwe = mapMessages[key];

                    for (auto& client : qwe) {
                        if (!ContainsString(client.clientsWhoRead, mess[1])) {

                            combinedMessages << client.message << "\n"; 

                            client.clientsWhoRead.push_back(mess[1]);
                        }

                    }
                }
                std::string allMessages = combinedMessages.str();
                send(clientSocket, allMessages.c_str(), allMessages.size(), 0);
            }
            
    }
    closesocket(clientSocket);
    return 0;
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket. Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket. Error code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error while listening for incoming connections. Error code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is waiting for incoming connections..." << std::endl;

    std::vector<ClientMessage> clientMessages;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Failed to accept connection. Error code: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }
        ThreadParams* params = new ThreadParams;
        params->clientSocket = clientSocket;

        CreateThread(nullptr, 0, answMessage, params, 0, nullptr);
        
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}