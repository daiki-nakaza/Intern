#include "Comand.h"


void Comand::fileCheck(char argv[]) {
	if (strstr(argv, ".bmp") == NULL) {
		FileFind(argv);
	}
	else {
		strcpy_s(filename[fileCount], 500, argv);
		printf("%s\n", filename[fileCount++]);
		
	}
}


/*コマンドライン引数で渡されたのがファイルだった場合に実行*/
void Comand::FileFind(char argv[]){
	
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;
		char target[510]/*"C:\\Users\\O-PC-000000-040\\Desktop\\Release\\image"*/;
		

		strcpy_s(target, sizeof(target), argv);
		strcat_s(target, sizeof(target), "\\*.bmp");

		hFind = FindFirstFile(target, &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do {
				//printf(TEXT("%d: %s\n"), ++fileCount, FindFileData.cFileName);
				strcpy_s(filename[fileCount], 500,argv);
				strcat_s(filename[fileCount], 500, "\\");
				strcat_s(filename[fileCount], 500, FindFileData.cFileName);
				printf("%s\n", filename[fileCount++]);
			} while (FindNextFile(hFind, &FindFileData));

			FindClose(hFind);
		}
		
	//}
}