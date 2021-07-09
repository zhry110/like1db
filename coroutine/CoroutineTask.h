//
// Created by like1 on 2021/2/8.
//

#ifndef COROUTINE_DEMO_COROUTINETASK_H
#define COROUTINE_DEMO_COROUTINETASK_H

#include <experimental/coroutine>

using std::experimental::coroutine_handle;
using std::experimental::suspend_never;

class CoroutineTask {
public:
    class promise_type;

private:
    coroutine_handle<promise_type> handle;
public:
    explicit CoroutineTask(const coroutine_handle<promise_type> &handle);

    class promise_type {
    public:
        CoroutineTask get_return_object();

        [[nodiscard]] suspend_never initial_suspend() const;

        [[nodiscard]] suspend_never final_suspend() const noexcept;

        void return_void() const;

        void unhandled_exception() const;
    };

    coroutine_handle<promise_type> coro_handle();
};


#endif //COROUTINE_DEMO_COROUTINETASK_H