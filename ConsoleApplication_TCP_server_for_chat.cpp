

#include <iostream>
#include <winsock2.h>
#pragma comment (lib,"ws2_32.lib")
#include<iostream>
//#include<unistd.h>
#include<string.h>
//#include<sys/socket.h>
//#include<netinet/in.h>
//#include "stdafx.h"


using namespace std;

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта

struct sockaddr_in serveraddress, client;
int length= sizeof(serveraddress);
int sockert_file_descriptor, connection, bind_status, connection_status;
char message[MESSAGE_LENGTH];

SOCKET connections[100];
int counter = 0;

void ClientHandler(int index)
{
    char msg[256];//переменная для сообщения от клиента
    while (true)//бесконечный цикл приёма/отправки сообщений
    {
        recv(connections[index], msg, sizeof(msg), NULL);//получение сообщения от клиента
        for (int i = 0; i < counter; i++)
        {
            if (i == index) { continue; }
            send(connections[i], msg, sizeof(msg), NULL);// отправка этого же сообщения от сервера другим клиентам по средствам потока созданного createthread  в аксепте accept очередного соединения в сервере----строки 100-116
        }
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









    setlocale(LC_ALL, "RUS");
    // Создадание сокета сервера
    SOCKET sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == 0) {
        cout << "Сокет сервера не создан" << endl;
        exit(1);
    }

    // Создаю объект отдельной структуры типа sockaddr_in по имени serveraddress(адрес сервера)
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);// второй вариант: serveraddress.sin_addr.s_addr=inet_addr("127.1.2.0")
    // Задам номер порта для этого адреса и семейство интернет
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;

    //Привязка сокета к адресному объекту 
    bind_status = bind(sockert_file_descriptor, (sockaddr*)&serveraddress, sizeof(serveraddress));

    //Проверка успешности привязки сокета сервера к адресному объекту сервера
    if (bind_status == -1) {
        cout << "Сокет сервера не привязался к адресному объекту" << endl;
        exit(1);
    }

    // Поставим сервер на прием данных 
    connection_status = listen(sockert_file_descriptor, 100);
    if (connection_status == -1) {
        cout << "Сокет сервера не может прослушивать новые соединения" << endl;
        exit(1);
    }
    else {
        cout << "Сервер слушает новые соединения " << endl;
    }

    SOCKET connection;
    length = sizeof(client);// количественный размер в байтах адресной структуры клиента
    for(int i=0; i<100;i++)
    { 
               connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);//установление связи и принятие пакетов от клиента
                     if (connection == -1) {
                             cout << "Сервер не может принять данные от клиента" << endl;
                                 exit(1);
                                            }
                     else
                     {
                         cout << "Сервер работоспособен" << endl;
                         char mess[256] = "My first network programm";
                         send(sockert_file_descriptor, mess, sizeof(mess), NULL);
                         connections[i] = connection;
                         counter++;
                         CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);


                     }


    }





    return 0;

}


