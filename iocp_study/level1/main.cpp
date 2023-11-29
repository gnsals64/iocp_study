#include "IOCompletionPort.h"

const UINT16 SERVER_PORT = 11021;
const UINT16 MAX_CLIENT = 100;

int main() {
	IOCompletionPort ioCompletionPort;

	ioCompletionPort.InitSocket();
	ioCompletionPort.BindandListen(SERVER_PORT);
	ioCompletionPort.

}