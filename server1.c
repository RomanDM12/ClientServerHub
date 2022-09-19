#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main () {
	FILE* fp;
	int sd, cd;
	struct sockaddr_in addr;
	char fileName[32];
	char fileContent[32];
	int fileNameLen;
	int fileContentLen;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		perror("error calling socket");
		return __LINE__;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(sd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return __LINE__;
	}

	if (listen(sd, 5)) {
		perror("listen");
		return __LINE__;
	}

	if (0 > (cd = accept(sd, NULL, NULL))) {
		perror("accept");
		return __LINE__;
	}

	fileNameLen = recv(cd, fileName, 32, 0);
	fileContentLen = recv(cd, fileContent, 32, 0);

	fp = fopen(fileName, "w");
	if (fp == NULL) {
		perror("cant create file");
		return -1;
	}

	if (fileContentLen > 0) {
		fwrite(fileContent, sizeof(char), fileContentLen, fp);
	}
	fclose(fp);
	close(cd);
	close(sd);
	return 0;
}
