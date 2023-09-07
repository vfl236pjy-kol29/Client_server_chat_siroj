#include <iostream>
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")
#include<iostream>
//#include <unistd.h>
#include<string.h>
//#include<sys/socket.h>
//#include<netinet/in.h>
#pragma warning(disable:4996)
using namespace std;

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта

struct sockaddr_in  clientaddress, serveraddress;
//int length=sizeof();
int sockert_file_descriptor_client, connection_to_server;
char message[MESSAGE_LENGTH];

//SOCKET connection_to_server;

void ClientHandler()
    {
    char msg[256];
    while (true)
         {
        recv(connection_to_server, msg, sizeof(msg), NULL);
        cout << msg << endl;
         }

    }


int main()
{
    setlocale(LC_ALL, "RUS");

    //ИНИЦИАЛИЗАЦИЯ СОКЕТА
    WSADATA wsaData;	// Эта структура используется для хранения данных Windows Sockets, возвращаемых после вызова функции WSAStartup.
    WORD sockVersion = MAKEWORD(2, 2);	// Информация о номере версии библиотеки сетевого программирования Windows
    if (WSAStartup(sockVersion, &wsaData) != 0) // Функция WSAStartup предназначена для инициализации и загрузки сети Windows в программе
    {
        cout << "Ошибка инициализации сокета!" << endl;
        return 0;
    }





    // Создадание сокета клиента
    SOCKET sockert_file_descriptor_client = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor_client ==-1)
    {
        cout << "Сокет клиента не создан" << endl;
        exit(1);
    }

    // Создаю объект отдельной структуры типа sockaddr_in по имени serveraddress(адрес сервера)
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");// второй вариант: serveraddress.sin_addr.s_addr=inet_addr("127.1.2.0")
// Задам номер порта для этого адреса и семейство интернет
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;


    // Попытка соединения с сервером
    int connection_to_server = connect(sockert_file_descriptor_client, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection_to_server !=0) {
        cout << "Connection with the server failed.!" << endl;
        exit(1);
    }
    else
    {
        cout << "Соединение с сервером осуществлено" << endl;

        char msg[256];//необязательно(лучше удалить), т.к. исполняется функция ClientHandler() в потоке CreateThread(строка75)
        recv(sockert_file_descriptor_client, msg, sizeof(msg), NULL);//необязательно(лучше удалить), т.к. исполняется функция ClientHandler() в потоке CreateThread(строка75)
        cout << msg << endl;//необязательно(лучше удалить), т.к. исполняется функция ClientHandler() в потоке CreateThread(строка75)

        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler,NULL, NULL, NULL);

        char msg1[256];// переменная для хранения сообщения
        while (true)
                  {
                      std::cin.getline(msg1, sizeof(msg1));//считывание строки в переменную msg1 с консоли ввода данных
                      send(connection_to_server,msg1, sizeof(msg1), NULL);//посылка считанного сообщения с консоли серверу
                      Sleep(10);

                  }
    }

    return 0;
}