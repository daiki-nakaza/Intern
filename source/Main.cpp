#include <cstdio>  
#include <iostream>  
#include <cstring>  
#include <stdio.h> 
#include<string.h>

#include "BitMap.h"
#include "Comand.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	
	char filename[500][500];/* = "D:/work/Project1/Project1/image/cat2.bmp"*/
	char filename2[500];//書き出しようのファイルネーム
	char addname[50] = "(1).bmp";//
	char buf[500];//入力受け取り

	int width = 10000, height = 10000;
	int check_width = 0, check_height = 0;//
	int max_width = 0, max_height = 0;//複数枚の写真のピクセルが3000を超えないかどうか調べるため。

	int readCheck = 0;//何枚読み込めたかしらべる
	char scale_pixel = 'n';//'s'or'p'

	BitMap bitmap1;
	Comand command1;//コマンドライン引数に関すること

	for (int i = 1; i < argc; i++) {
		command1.fileCheck(argv[i]);//いくつかのｂｍｐを読み込みできるようにする。
	}
	for (int i = 0; i < command1.fileCount; i++) {//コマンドライン引数で読み取ったファイルを開けるかどうか調べる。

		if (bitmap1.readFileOpen(command1.filename[i])) {
			strcpy_s(filename[readCheck], 500, command1.filename[i]);//filenameをコピーする
			readCheck++;											 //数をチェック
			if (max_width < bitmap1.iHeader.width) {
				max_width = bitmap1.iHeader.width;
			}
			if (max_height < bitmap1.iHeader.height) {
				max_height = bitmap1.iHeader.height;
			}
			
			fclose(bitmap1.bmp);
			
		}//画像を開く//成功でtrueに変える
	}
	
	printf(TEXT("Total File Count: %d\n"), readCheck);//開けた画像の個数
	
	while (readCheck == 0)//引数で与えられなかったもしくは読み込みできなかった時に入る
	{
		printf("変更したい画像のパスを入力してEnterを押してください。\n");

		fgets(buf, sizeof(buf), stdin);						/* ここで入力 */
		sscanf_s(buf, "%s", &filename[readCheck], sizeof(filename[readCheck]));   /* バッファからfilenameに格納 */
		

		command1.fileCheck(filename[readCheck]);//いくつかのｂｍｐを読み込みできるようにする。
		for (int i = 0; i < command1.fileCount; i++) {//ファイルを開けるかどうか調べる。

			if (bitmap1.readFileOpen(command1.filename[i])) {
				strcpy_s(filename[readCheck], 500, command1.filename[i]);//filenameをコピーする
				readCheck++;											 //数をチェック
				if (max_width < bitmap1.iHeader.width) {
					max_width = bitmap1.iHeader.width;
				}
				if (max_height < bitmap1.iHeader.height) {
					max_height = bitmap1.iHeader.height;
				}

				fclose(bitmap1.bmp);

			}//画像を開く//成功でtrueに変える
		}

		if (readCheck != 0) {
			break;
		}
		else {
			printf("エラー画像が見つかりませんでした。\n");
		}
		
	}

	printf("%d個の画像の読み込みに成功しました。\n", readCheck);
	
	

	

	while (true) {
		printf("倍率指定の場合は'S'：ピクセル指定の場合は'P'を入力してEnterを押してください。\n");
		fgets(buf, sizeof(buf), stdin);						/* ここで入力 */
		sscanf_s(buf, "%c", &scale_pixel, sizeof(scale_pixel));   /* バッファからscale_pixelに格納 */
		if (scale_pixel == 's' || scale_pixel == 'S' || scale_pixel == 'p' || scale_pixel == 'P') {//正しいなら抜ける
			break;
		}
		printf("もう一度入力してください\n");
	}

	if (scale_pixel == 's' || scale_pixel == 'S') {
		printf("大きさ（倍率）の指定をしてください。\n");


		while (true) {
			printf("画像の幅（％）：");
			fgets(buf, sizeof(buf), stdin);						/* ここで入力 */
			sscanf_s(buf, "%d", &width, sizeof(width));   /* バッファからinput_numに格納 */

			/* 数字じゃない時は再入力 */
			if (width < 1 || 3000 < width) {
				//printf("%d\n", width);
				printf("もう一度入力してください\n");
				continue;												//1
			}
			//printf("%d\n", width);
			check_width = ((float)width / 100) * max_width;
			if (check_width > 3000) {
				printf("拡大後:%dpx\n", check_width);
				printf("3000ピクセルより大きくすることはできません。\n");
				width = 10000;
				continue;												//2
			}
			else if (check_width < 1) {
				printf("縮小後:%dpx\n", check_width);
				printf("1ピクセルより小さくすることはできません。\n");
				width = 10000;
				continue;
			}

			break;

		}


		while (true) {
			printf("画像の高さ（％）：");
			fgets(buf, sizeof(buf), stdin);						/* ここで入力 */
			sscanf_s(buf, "%d", &height, sizeof(height));   /* バッファからheightに格納 */

			/* 数字じゃない時は再入力 */
			if (height < 1 || 3000 < height) {
				printf("もう一度入力してください\n");
				continue;												//1
			}

			check_height = ((float)height / 100) * max_height;
			if (check_height > 3000) {
				printf("拡大後:%dpx\n", check_height);
				printf("3000ピクセルより大きくすることはできません。\n");
				height = 10000;
				continue;												//2
			}
			else if (check_height < 1) {
				printf("縮小後:%dpx\n", check_height);
				printf("1ピクセルより小さくすることはできません。\n");
				height = 10000;
				continue;
			}

			break;

		}
	}
	else if (scale_pixel == 'p' || scale_pixel == 'P') {
		printf("大きさ（ピクセル）の指定をしてください。\n");


		while (true) {
			printf("画像の幅（px）：");
			fgets(buf, sizeof(buf), stdin);						/* ここで入力 */
			sscanf_s(buf, "%d", &width, sizeof(width));   /* バッファからinput_numに格納 */

			/* 数字じゃない時は再入力 */
			if (width < 1 || 3000 < width) {
				//printf("%d\n", width);
				printf("もう一度入力してください\n");
				continue;												//1
			}
			//printf("%d\n", width);
			check_width = width;
			if (check_width > 3000) {
				printf("拡大後:%dpx\n", check_width);
				printf("3000ピクセルより大きくすることはできません。\n");
				width = 10000;
				continue;												//2
			}
			else if (check_width < 1) {
				printf("縮小後:%dpx\n", check_width);
				printf("1ピクセルより小さくすることはできません。\n");
				width = 10000;
				continue;
			}

			break;

		}


		while (true) {
			printf("画像の高さ(px）：");
			fgets(buf, sizeof(buf), stdin);						/* ここで入力 */
			sscanf_s(buf, "%d", &height, sizeof(height));   /* バッファからheightに格納 */

			/* 数字じゃない時は再入力 */
			if (height < 1 || 3000 < height) {
				printf("もう一度入力してください\n");
				continue;												//1
			}

			check_height = height;
			if (check_height > 3000) {
				printf("拡大後:%dpx\n", check_height);
				printf("3000ピクセルより大きくすることはできません。\n");
				height = 10000;
				continue;												//2
			}
			else if (check_height < 1) {
				printf("縮小後:%dpx\n", check_height);
				printf("1ピクセルより小さくすることはできません。\n");
				height = 10000;
				continue;
			}

			break;

		}

		
	}
	
	
	
	//1枚ずつ書き換えする
	for (int i = 0; i < readCheck; i++) {
		bitmap1.readFileOpen(filename[i]);//画像を読み込む

		bitmap1.BitScale(width, height, scale_pixel);				//画像を拡大縮小する


		strcpy_s(filename2, 500, filename[i]);
		if ((strstr(filename2, ").bmp")) != NULL) {
			char *adr = strstr(filename2, ").bmp");
			adr--;//アドレスを1つ後ろにずらす。9).bmp
			while (true) {
				printf("%s\n", adr);
				if (adr[0] == '9') {//9なら
					adr--; //アドレスを1つ後ろにずらす。19).bmp
				}
				else if(isdigit(adr[0])){

					while (adr[0] != ')') {
						if (adr[0] == '9') {
							adr[0] = '0';
						}
						else {
							adr[0]++;
						}
						adr++;
					}
					
					break;
				}
				else if (adr[0] == '(') {
					char str[50];//一時的に保留
					adr++;
					strcpy_s(str, 50,adr);//9).bmpを一時避難
					adr[0] = '0'; adr++; //
					strcpy_s(adr, 50, str);//
				}
				else {
					char *adr = strstr(filename2, ".bmp");			//渡されたパスの.bmpを探す。
					strcpy_s(adr, 50, addname);						//新規画像に名称変更
					break;
				}
			}
			
			//adr--;//アドレスを-
			//adr[0]++;//数字を１加算
		}
		else {
			char *adr = strstr(filename2, ".bmp");			//渡されたパスの.bmpを探す。
			strcpy_s(adr, 50, addname);						//新規画像に名称変更
		}
		//char *adr = strstr(filename2, ".bmp");			//渡されたパスの.bmpを探す。
		//strcpy_s(adr, 50, addname);						//新規画像に名称変更
		std::cout << filename2 << std::endl;


		bitmap1.writeFileClose(filename2);				//書き込み



		fclose(bitmap1.bmp);
		fclose(bitmap1.fp);

	}
	
	
	

	
	

	printf("正常に終了しました。(キー入力＋Enterキーで画面を閉じます)\n");
	
	while (true) {

		if (getchar() != '\n')break;
	}

	return 0;
}