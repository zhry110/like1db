//
// Created by like1 on 7/2/21.
//

#include "tcp_server.h"
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "CoroutineTask.h"

tcp_server::tcp_server(int port) {
    epoll_fd = epoll_create(max_epoll_size);
    if (epoll_fd < 0) {
        logger.warn("can not create epoll");
        std::terminate();
    }
    logger.info("server started");

    listen_at_ipv4(port);
}

void tcp_server::listen_at_ipv4(int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        logger.error("can not create socket");
        std::terminate();
    }
    sockaddr_in addr{};
    memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) < 0) {
        logger.error("can not set reuse addr");
        std::terminate();
    }
    if (setsockopt(fd, SOL_TCP, TCP_NODELAY, (char *) &on, sizeof(on)) < 0) {
        logger.error("can not set no delay");
        std::terminate();
    }
    if (bind(fd, reinterpret_cast<const sockaddr *>(&addr), sizeof(sockaddr_in)) < 0) {
        logger.error("can not bind ipv4");
        std::terminate();
    }
    if (listen(fd, max_listen_size) < 0) {
        logger.error("can not listen at ipv4");
        std::terminate();
    }
    int flags = fcntl(fd, F_GETFL, 0);
    assert(flags != -1);
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        logger.error("can not set socket to no block mode");
        std::terminate();
    }
    listen_fds.push_back(fd);
}

void tcp_server::stop() {
    this->stopped = true;
}

void tcp_server::start() {
    assert(!listen_fds.empty());
    std::for_each(listen_fds.begin(), listen_fds.end(), [&](int fd) -> void {
        epoll_event event{};
        event.data.fd = fd;
        CoroutineTask accept_coro = accept_request(fd);
        event.data.ptr = accept_coro.coro_handle().address();
        event.events = EPOLLIN | EPOLLET;
        if (epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, fd, &event) < 0) {
            logger.error("can not epoll listen fd");
            std::terminate();
        }
    });

    while (!stopped) {
        int event_num = epoll_wait(epoll_fd, events, max_listen_size, 1000);
        if (event_num < 0 && errno != EINTR) {
            logger.error("epoll wait error");
            std::terminate();
        }
        for (int i = 0; i < event_num; i++) {
            auto handle = coroutine_handle<CoroutineTask::promise_type>::from_address(events[i].data.ptr);
            handle.resume();
        }
    }
}

CoroutineTask tcp_server::accept_request(int fd) {
    while (!stopped) {
        sockaddr addr{};
        socklen_t len = sizeof(addr);
        int req_fd = accept(fd, &addr, &len);
        if (req_fd < 0) {
            if (errno == EAGAIN) {
                co_await std::experimental::suspend_always();
            } else {
                logger.error("accept error");
                std::terminate();
            }
        } else {

        }
    }
}
