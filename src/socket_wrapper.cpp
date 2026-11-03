// socket_wrapper.cpp
#include "socket_wrapper.h"
#include <sio_client.h>
#include <cstdio>
#include <exception>

struct sio_client_handle {
    sio::client client;
};

extern "C" {

sio_client_handle* sio_client_create(const char* url) {
    auto* handle = new sio_client_handle();

    handle->client.set_open_listener([]() {
        fprintf(stderr, "[socket] connected\n");
    });
    handle->client.set_fail_listener([]() {
        fprintf(stderr, "[socket] connection failed\n");
    });

    try {
        handle->client.connect(url);
    } catch (const std::exception& e) {
        fprintf(stderr, "[socket] connect error: %s\n", e.what());
    }
    return handle;
}

void sio_client_on_event(sio_client_handle* handle, const char* event_name, bool *flag) {
    if (!handle) return;
    handle->client.socket()->on(event_name, [flag](const sio::event&) {
        if (flag) __atomic_store_n(flag, true, __ATOMIC_SEQ_CST);   // runs on socket.io thread — atomic only
    });
}

void sio_client_destroy(sio_client_handle* handle) {
    if (handle) {
        handle->client.close();
        delete handle;
    }
}

}
