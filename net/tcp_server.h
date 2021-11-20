//
// Created by like1 on 7/2/21.
//

#ifndef LIKE1DB_TCP_SERVER_H
#define LIKE1DB_TCP_SERVER_H

#ifdef HAVE_EPOLL
#include <sys/epoll.h>
#endif
#ifdef HAVE_KQUEUE
#include <sys/event.h>
#endif
#include <vector>
#include <atomic>
#include <cassert>
#include <CoroutineTask.h>

#include "common/log.h"

class tcp_server {
    using fd_set = std::vector<int>;
public:
    static constexpr int max_epoll_size = 4096;
private:
    logger logger = logger::log();

    int epoll_fd = {0};
#ifdef HAVE_EPOLL
    epoll_event events[max_epoll_size]{};
#endif
    fd_set listen_fds{};

    std::atomic_bool stopped{false};

    void listen_at_ipv4(int port);

public:
    static constexpr int max_listen_size = 4096;
    static constexpr int max_accept_size = 1024;

    explicit tcp_server(int port);

    void stop();

    void start();

    CoroutineTask accept_request(int fd);

    std::experimental::suspend_always coro_accept(int fd);
};


#endif //LIKE1DB_TCP_SERVER_H
