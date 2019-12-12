#include "webserver.h"
#include "socket/src/Socket.h"



void Request_Handler(webserver::http_request* r) {
	Socket s = *(r->s_);






	r->answer_ = "HTML";
}

int main() {
	webserver(8080, Request_Handler);
}
