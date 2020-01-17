#include "webserver.h"
#include "socket/src/Socket.h"
#include "Routing.h"
#include <iostream>


#include "starStringEqualsTest.h"

//void Request_Handler(webserver::http_request* r) {
//	Socket s = *(r->s_);
//
//	Routing routing();
//
//
//	r->answer_ = "HTML";
//}

int main_old() {

	//std::cout << (starstringTest()?"Tests Successfull":"Error in testing")<< std::endl;

	webserver(80);
	return 0;
}