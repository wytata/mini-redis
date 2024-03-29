#include "stdio.h"
#include "sys/socket.h"

int main(int argc, char *argv[])
{
	int sock = socket(AF_INET, 0, SOCK_STREAM);
}
