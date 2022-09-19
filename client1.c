#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main () {
	int cd;
	struct sockaddr_in addr;
	char fileName[32];
	char fileContent[32];
	int fileNameLen;
	int fileContentLen;

	cd = socket(AF_INET, SOCK_STREAM, 0);
	if (cd < 0) {
		perror("error calling socket");
		return __LINE__;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if ((-1) == connect(cd, (struct sockaddr*)&addr, sizeof(addr))) {
		perror("not connect");
		return __LINE__;
	}

	send(cd, "FirstFile\n", 9, 0);
	send(cd, "Hello, World!\n", 14, 0);
	close(cd);
	return 0;
}
