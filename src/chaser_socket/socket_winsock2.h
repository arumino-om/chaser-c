#pragma once
#include <winsock2.h>
#include "socket_interface.h"

namespace chaser_c::chaser_socket {
    /**
     * @brief socket_interface の Winsock2 用実装
     * @details Windows Sockets 2 を用いたソケット通信の実装です。MSVCでコンパイルされるときは、これが使用されます。
     * @note Windows以外のOSではサポートされていません。
     */
    class socket_winsock2 : public socket_interface {
    public:
        /**
         * @brief ソケットを初期化します。
         * @details 通信用ソケットを初期化します。\n
         *  一つのクラスインスタンスにつき一つだけ初期化できます。
         *  使用後は、必ず close_socket() を呼び出してください。
         * @param address 接続先アドレス
         * @param port 接続先ポート
         * @return 接続できた場合は true, できなかった場合は false
         */
        bool init_socket(std::string &address, unsigned short port);

        /**
         * @brief バッファーを送信します。
         * @details この関数は、使用前に init_socket() でソケットを初期化する必要があります。
         * @param content 送信内容
         * @return 送信できた場合は true，送信できなかった場合は false
         */
        bool send_buffer(std::string &content);

        /**
         * @brief サーバーからバッファーを受信し、文字列として返します。
         * @details この関数は、使用前に init_socket() でソケットを初期化する必要があります。
         * @return 正しく受信できた場合は文字列、そうでない場合は nullptr
         */
        std::string receive_buffer();

        /**
         * @brief ソケットを閉じます。
         * @details 最後のソケットだった場合、 uninit_winsock2() も呼び出されます。
         */
        void close_socket();

    private:
        /**
         * @brief クラスインスタンス内で共有されるソケット
         */
        SOCKET socket_instance;

        /**
         * @brief Winsock2 を初期化します。
         * @details この関数は、ライブラリ内で一度もWinsock2が使用されていない場合に呼び出されます。
         * @return 初期化に成功したかどうか
         */
        static bool init_winsock2();

        /**
         * @brief Winsock2 の使用を終了します。
         * @details この関数は、ライブラリ内で最後のソケットが閉じられたときに呼び出されます。
         */
        static void uninit_winsock2();

        /**
         * @brief Winsock2 を使用して接続されているソケット数
         */
        static int connect_sockets;
    };

}
