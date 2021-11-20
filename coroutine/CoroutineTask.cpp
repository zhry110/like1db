//
// Created by like1 on 2021/2/8.
//

#include "CoroutineTask.h"


CoroutineTask::CoroutineTask(const coroutine_handle<promise_type> &handle) : handle(handle) {

}

coroutine_handle<CoroutineTask::promise_type> CoroutineTask::coro_handle() {
    return handle;
}


CoroutineTask CoroutineTask::promise_type::get_return_object() {
    return CoroutineTask(coroutine_handle<promise_type>::
                         from_promise(*this));
}

suspend_never CoroutineTask::promise_type::initial_suspend() const {
    return {};
}

void CoroutineTask::promise_type::unhandled_exception() const {
    std::terminate();
}

void CoroutineTask::promise_type::return_void() const {

}

suspend_never CoroutineTask::promise_type::final_suspend() const noexcept {
    return {};
}
