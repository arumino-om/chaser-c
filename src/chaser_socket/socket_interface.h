#pragma once
#include <string>

/**
 * @brief CHaserC で用いるソケット通信のインターフェース、およびその実装
 */
namespace chaser_c::chaser_socket {
    /**
     * @brief ソケット通信を抽象化したインターフェース
     * @details CHaserC では、このインターフェースを通じてソケット通信の実装を切り替えます。\n
     *  新規にソケット通信の実装を行う場合は、このインターフェースを継承してください。
     */
    class socket_interface {
    public:
        /**
         * @brief ソケットを初期化します。
         * @note 開発者向け: この関数でソケットを初期化した後、クラスインスタンス内にそのソケットを保持することを想定しています。
         * @param address 接続先アドレス
         * @param port 接続先ポート
         * @return 接続できた場合は true, できなかった場合は false
         */
        virtual bool init_socket(std::string &address, unsigned short port) = 0;

        /**
         * @brief バッファーを送信します。
         * @param content 送信内容
         * @return 送信できた場合は true，送信できなかった場合は false
         */
        virtual bool send_buffer(std::string &content) = 0;

        /**
         * @brief バッファーを受信し、文字列として返します。
         * @return 正しく受信できた場合は文字列、そうでない場合は nullptr
         */
        virtual std::string receive_buffer() = 0;

        /**
         * @brief ソケットを閉じます。
         */
        virtual void close_socket() = 0;
    };
}
