//
// Created by like1 on 7/2/21.
//

#ifndef LIKE1DB_LOG_H
#define LIKE1DB_LOG_H

#endif //LIKE1DB_LOG_H

#include <string>
#include <iostream>
#include <thread>

namespace like1db {
    class logger {
    public:
        void warn(const char* text) {
            std::cout << "[warn] " << text << std::endl;
        }

        void error(const char* text) {
            std::cout << "[error] " << text << std::endl;
        }

        void info(const char* text) {
            std::cout << "[Thread-" << std::this_thread::get_id() << "][INFO] " << text << std::endl;
        }

        static logger log() {
            static logger log_;
            return log_;
        }
    };
}

using namespace like1db;
