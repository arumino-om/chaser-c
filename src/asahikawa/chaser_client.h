#pragma once
#include <string>

/**
 * @brief C/C++用 CHaser ライブラリ for 旭川版ルール
 */
namespace chaser_c::asahikawa {
    /**
     * @brief CHaser クライアント
     * @details CHaser サーバーとやり取りを行うクラスです。
     */
    class chaser_client {
    public:
        /**
         * @brief 方向指定を行う列挙体
         */
        enum direction {
            /** 上方向 */ UP,
            /** 下方向 */ DOWN,
            /** 左方向 */ LEFT,
            /** 右方向 */ RIGHT
        };

        /**
         * @brief CHaser クライアントを初期化します。
         * @details CHaser クライアントを初期化する際に、サーバーへの接続も行います。
         * @param address 接続先アドレス
         * @param port 接続先ポート
         * @param name 名前
         */
        chaser_client(std::string &address, unsigned short port, std::string &name);

        ~chaser_client();

        /**
         * @brief GetReady を送信します。
         * @param values 制御情報と周囲情報を受け取る配列のポインター
         * @param values_length values配列の長さ (10が望ましい)
         */
        void get_ready(int *values, int values_length);

        /**
         * @brief Walk を送信します。
         * @param dir 歩く方向
         * @param values 制御情報と周囲情報を受け取る配列のポインター
         * @param values_length values配列の長さ (10が望ましい)
         */
        void walk(direction dir, int *values, int values_length);

        /**
         * @brief Look を送信します。
         * @param dir Lookする方向
         * @param values 制御情報と周囲情報を受け取る配列のポインター
         * @param values_length values配列の長さ (10が望ましい)
         */
        void look(direction dir, int *values, int values_length);

        /**
         * @brief Search を送信します。
         * @param dir Searchする方向
         * @param values 制御情報と周囲情報を受け取る配列のポインター
         * @param values_length values配列の長さ (10が望ましい)
         */
        void search(direction dir, int *values, int values_length);

        /**
         * @brief Put を送信します。
         * @param dir Putする方向
         * @param values 制御情報と周囲情報を受け取る配列のポインター
         * @param values_length values配列の長さ (10が望ましい)
         */
        void put(direction dir, int *values, int values_length);

    private:
        /**
         * @brief サーバーにコマンドを送信します。
         * @param command_id 送信するコマンド
         */
        void send_command(std::string &command_id);
    };

}
