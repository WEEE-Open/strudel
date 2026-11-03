// socket_wrapper.h
#ifndef SOCKET_WRAPPER_H
#define SOCKET_WRAPPER_H

#include <stdatomic.h>

#ifdef __cplusplus
extern "C" {
#endif

// Opaque type: C code can hold a pointer to it but not look inside
typedef struct sio_client_handle sio_client_handle;
  
sio_client_handle* sio_client_create(const char* url);
void sio_client_on_event(sio_client_handle* handle, const char* event_name, atomic_bool *flag);
void sio_client_destroy(sio_client_handle* handle);

#ifdef __cplusplus
}
#endif

#endif // SOCKET_WRAPPER_H
