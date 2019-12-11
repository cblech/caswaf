#include "webserver.h"
#include "socket/src/Socket.h"



void Request_Handler(webserver::http_request* r) {
  Socket s = *(r->s_);

  r->answer_  = "<!DOCTYPE html>\n <html><head><title>Test</title></head><body>";
  r->answer_ += "<h1>Test</h1><p>This is a Test</p>";
  r->answer_ += "</body></html>";

}

int main() {
  webserver(8080, Request_Handler);
}
