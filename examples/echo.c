#include "net_skeleton.h"

static void ev_handler(struct ns_connection *conn, enum ns_event ev, void *p) {
  struct iobuf *io = &conn->recv_iobuf;
  (void) p;

  switch (ev) {
    case NS_RECV:
      ns_send(conn, io->buf, io->len);  // Echo message back
      iobuf_remove(io, io->len);        // Discard message from recv buffer
      break;
    default:
      break;
  }
}

int main(void) {
  struct ns_server server;
  const char *port = "1234";

  ns_server_init(&server, NULL, ev_handler);
  ns_bind(&server, port);

  printf("Starting echo server on port %s\n", port);
  for (;;) {
    ns_server_poll(&server, 1000);
  }
  ns_server_free(&server);

  return 0;
}
