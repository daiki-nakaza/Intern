#include <cstdio>  
#include <iostream>  
#include <cstring>  
#include <stdio.h> 
#include<string.h>

#include "BitMap.h"

using namespace std;

int main(int argc, char* argv[]) {

	char filename[500]/* = "D:/work/Project1/Project1/image/cat2.bmp"*/;
	char filename2[500];
	char addname[50] = "(1).bmp";
	char buf[500];

	int width = 10000, height = 10000;
	int check_width = 0, check_height = 0;//

	bool readCheck = false;
	char scale_pixel = 'n';

	BitMap bitmap1;
	while (true)
	{
		printf("変更したい画像のパスを入力してEnterを押してください。\n");
		//scanf_s("%s", filename, 500);

		fgets(buf, sizeof(buf), stdin);						/* ここで入力 */
		sscanf_s(buf, "%s", &filename, sizeof(filename));   /* バッファからinput_numに格納 */

		readCheck = bitmap1.readFileOpen(filename);					//画像を開く//成功でtrueが変える
		if (readCheck) {
			break;
		}

	}

	while (true) {
		printf("倍率指定の場合は'S'：ピクセル指定の場合は'P'を入力してEnterを押してください。\n");
		fgets(buf, sizeof(buf), stdin);						/* ここで入力 */
		sscanf_s(buf, "%c", &scale_pixel, sizeof(scale_pixel));   /* バッファからinput_numに格納 */
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
			check_width = ((float)width / 100) * bitmap1.iHeader.width;
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

			check_height = ((float)height / 100) * bitmap1.iHeader.height;
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
	
	
	

	
	
	
	
	bitmap1.BitScale(width, height, scale_pixel);				//画像を拡大縮小する

	
	strcpy_s(filename2, 500, filename);
	char *adr = strstr(filename2, ".bmp");			//渡されたパスの.bmpを探す。
	strcpy_s(adr, 50, addname);						//新規画像に名称変更
	std::cout << filename2 << std::endl;

	
	bitmap1.writeFileClose(filename2);				//書き込み

	

	fclose(bitmap1.bmp);
	fclose(bitmap1.fp);

	printf("正常に終了しました。(キー入力＋Enterキーで画面を閉じます)\n");
	
	while (true) {

		if (getchar() != '\n')break;
	}

	return 0;
}