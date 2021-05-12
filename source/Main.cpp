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
		printf("�ύX�������摜�̃p�X����͂���Enter�������Ă��������B\n");
		//scanf_s("%s", filename, 500);

		fgets(buf, sizeof(buf), stdin);						/* �����œ��� */
		sscanf_s(buf, "%s", &filename, sizeof(filename));   /* �o�b�t�@����input_num�Ɋi�[ */

		readCheck = bitmap1.readFileOpen(filename);					//�摜���J��//������true���ς���
		if (readCheck) {
			break;
		}

	}

	while (true) {
		printf("�{���w��̏ꍇ��'S'�F�s�N�Z���w��̏ꍇ��'P'����͂���Enter�������Ă��������B\n");
		fgets(buf, sizeof(buf), stdin);						/* �����œ��� */
		sscanf_s(buf, "%c", &scale_pixel, sizeof(scale_pixel));   /* �o�b�t�@����input_num�Ɋi�[ */
		if (scale_pixel == 's' || scale_pixel == 'S' || scale_pixel == 'p' || scale_pixel == 'P') {//�������Ȃ甲����
			break;
		}
		printf("������x���͂��Ă�������\n");
	}

	if (scale_pixel == 's' || scale_pixel == 'S') {
		printf("�傫���i�{���j�̎w������Ă��������B\n");


		while (true) {
			printf("�摜�̕��i���j�F");
			fgets(buf, sizeof(buf), stdin);						/* �����œ��� */
			sscanf_s(buf, "%d", &width, sizeof(width));   /* �o�b�t�@����input_num�Ɋi�[ */

			/* ��������Ȃ����͍ē��� */
			if (width < 1 || 3000 < width) {
				//printf("%d\n", width);
				printf("������x���͂��Ă�������\n");
				continue;												//1
			}
			//printf("%d\n", width);
			check_width = ((float)width / 100) * bitmap1.iHeader.width;
			if (check_width > 3000) {
				printf("�g���:%dpx\n", check_width);
				printf("3000�s�N�Z�����傫�����邱�Ƃ͂ł��܂���B\n");
				width = 10000;
				continue;												//2
			}
			else if (check_width < 1) {
				printf("�k����:%dpx\n", check_width);
				printf("1�s�N�Z����菬�������邱�Ƃ͂ł��܂���B\n");
				width = 10000;
				continue;
			}

			break;

		}


		while (true) {
			printf("�摜�̍����i���j�F");
			fgets(buf, sizeof(buf), stdin);						/* �����œ��� */
			sscanf_s(buf, "%d", &height, sizeof(height));   /* �o�b�t�@����height�Ɋi�[ */

			/* ��������Ȃ����͍ē��� */
			if (height < 1 || 3000 < height) {
				printf("������x���͂��Ă�������\n");
				continue;												//1
			}

			check_height = ((float)height / 100) * bitmap1.iHeader.height;
			if (check_height > 3000) {
				printf("�g���:%dpx\n", check_height);
				printf("3000�s�N�Z�����傫�����邱�Ƃ͂ł��܂���B\n");
				height = 10000;
				continue;												//2
			}
			else if (check_height < 1) {
				printf("�k����:%dpx\n", check_height);
				printf("1�s�N�Z����菬�������邱�Ƃ͂ł��܂���B\n");
				height = 10000;
				continue;
			}

			break;

		}
	}
	else if (scale_pixel == 'p' || scale_pixel == 'P') {
		printf("�傫���i�s�N�Z���j�̎w������Ă��������B\n");


		while (true) {
			printf("�摜�̕��ipx�j�F");
			fgets(buf, sizeof(buf), stdin);						/* �����œ��� */
			sscanf_s(buf, "%d", &width, sizeof(width));   /* �o�b�t�@����input_num�Ɋi�[ */

			/* ��������Ȃ����͍ē��� */
			if (width < 1 || 3000 < width) {
				//printf("%d\n", width);
				printf("������x���͂��Ă�������\n");
				continue;												//1
			}
			//printf("%d\n", width);
			check_width = width;
			if (check_width > 3000) {
				printf("�g���:%dpx\n", check_width);
				printf("3000�s�N�Z�����傫�����邱�Ƃ͂ł��܂���B\n");
				width = 10000;
				continue;												//2
			}
			else if (check_width < 1) {
				printf("�k����:%dpx\n", check_width);
				printf("1�s�N�Z����菬�������邱�Ƃ͂ł��܂���B\n");
				width = 10000;
				continue;
			}

			break;

		}


		while (true) {
			printf("�摜�̍���(px�j�F");
			fgets(buf, sizeof(buf), stdin);						/* �����œ��� */
			sscanf_s(buf, "%d", &height, sizeof(height));   /* �o�b�t�@����height�Ɋi�[ */

			/* ��������Ȃ����͍ē��� */
			if (height < 1 || 3000 < height) {
				printf("������x���͂��Ă�������\n");
				continue;												//1
			}

			check_height = height;
			if (check_height > 3000) {
				printf("�g���:%dpx\n", check_height);
				printf("3000�s�N�Z�����傫�����邱�Ƃ͂ł��܂���B\n");
				height = 10000;
				continue;												//2
			}
			else if (check_height < 1) {
				printf("�k����:%dpx\n", check_height);
				printf("1�s�N�Z����菬�������邱�Ƃ͂ł��܂���B\n");
				height = 10000;
				continue;
			}

			break;

		}

		
	}
	
	
	

	
	
	
	
	bitmap1.BitScale(width, height, scale_pixel);				//�摜���g��k������

	
	strcpy_s(filename2, 500, filename);
	char *adr = strstr(filename2, ".bmp");			//�n���ꂽ�p�X��.bmp��T���B
	strcpy_s(adr, 50, addname);						//�V�K�摜�ɖ��̕ύX
	std::cout << filename2 << std::endl;

	
	bitmap1.writeFileClose(filename2);				//��������

	

	fclose(bitmap1.bmp);
	fclose(bitmap1.fp);

	printf("����ɏI�����܂����B(�L�[���́{Enter�L�[�ŉ�ʂ���܂�)\n");
	
	while (true) {

		if (getchar() != '\n')break;
	}

	return 0;
}