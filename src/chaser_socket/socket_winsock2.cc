#include "socket_winsock2.h"
#include <winsock2.h>
#include <ws2tcpip.h>
//#include <wspiapi.h>

using namespace chaser_c::chaser_socket;

// --- STATIC MEMBERS ---
int socket_winsock2::connect_sockets = 0;

bool socket_winsock2::init_winsock2() {
    WSAData data;
    int init_result = WSAStartup(MAKEWORD(2, 2), &data);

    if (init_result != 0) return false;
    else return true;
}


void socket_winsock2::uninit_winsock2() {
    WSACleanup();
}

// --- MEMBERS ---
bool socket_winsock2::init_socket(std::string &address, unsigned short port) {
    // Winsock2 で接続されたソケットがない場合は、最初に Winsock2 を初期化する
    if (socket_winsock2::connect_sockets == 0) {
        socket_winsock2::init_winsock2();
    }

    struct addrinfo hints, *addr_res;
    struct sockaddr_in addr;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // アドレス情報を引っ張ってくる
    int func_res = getaddrinfo(address.c_str(), NULL, &hints, &addr_res);
    if (func_res != 0) return false;

    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    inet_pton(addr.sin_family, address.c_str(), &addr.sin_addr);

    // ソケット構築と接続
    this->socket_instance = socket(addr.sin_family, SOCK_STREAM, 0);
    if (connect(this->socket_instance, (struct sockaddr *)&addr, sizeof(addr))) {
        closesocket(this->socket_instance);
        return false;
    }

    socket_winsock2::connect_sockets++;
    return true;
}


bool socket_winsock2::send_buffer(std::string &content) {
    send(this->socket_instance, content.c_str(), content.length(), 0);
}

std::string socket_winsock2::receive_buffer() {
    int recv_chars_len = 100;
    char recv_chars[recv_chars_len];
    recv(this->socket_instance, recv_chars, recv_chars_len, 0);

    return std::string(recv_chars);
}

void socket_winsock2::close_socket() {
    closesocket(this->socket_instance);
    socket_winsock2::connect_sockets--;
    if (socket_winsock2::connect_sockets <= 0) {
        socket_winsock2::uninit_winsock2();
    }
}
