#include <Windows.h>
#include <stdio.h>
#include<regex>


using namespace std;

class Comand 
{
private:
public:
	int argc;
	//char *argv[];
	char filename[500][500];//‚T‚O‚O‚±‚Ü‚Å
	int fileCount = 0;

	void fileCheck(char argv[]);
	void FileFind(char argv[]);
};