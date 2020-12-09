#include <bits/types/struct_timeval.h>
#include <stdlib.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string.h>

std::string str = " std::string str[5] = { \"je\", \"suis\", \"un\", \"gros\", \"canrd\" };\n\nint main() {\n\nstruct termios oldSettings, newSettings;\n\nint i = 0;\nstd::string text = "";\n\ntcgetattr(fileno( stdin), &oldSettings);\n";

int main() {

	struct termios oldSettings, newSettings;

	int i = 0;
	std::string text = "";

	tcgetattr(fileno( stdin), &oldSettings);
	newSettings = oldSettings;
	newSettings.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(fileno( stdin), TCSANOW, &newSettings);

	fd_set set;
	struct timeval tv;

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	FD_ZERO(&set);
	FD_SET(fileno( stdin ), &set);

	int res = select(fileno( stdin) + 1, &set, NULL, NULL, &tv);

	system("clear");

	while (res > 0) {
		char c;
		system("clear");
		text += str[i];
		std::cout << text << std::endl;
		i++;
		if(i >= str.length())
			i = 0;
		read(fileno(stdin), &c, 1);
	}

	tcsetattr(fileno( stdin), TCSANOW, &oldSettings);
	return 0;
}
