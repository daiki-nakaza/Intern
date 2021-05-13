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
	char filename2[500];//�����o���悤�̃t�@�C���l�[��
	char addname[50] = "(1).bmp";//
	char buf[500];//���͎󂯎��

	int width = 10000, height = 10000;
	int check_width = 0, check_height = 0;//
	int max_width = 0, max_height = 0;//�������̎ʐ^�̃s�N�Z����3000�𒴂��Ȃ����ǂ������ׂ邽�߁B

	int readCheck = 0;//�����ǂݍ��߂�������ׂ�
	char scale_pixel = 'n';//'s'or'p'

	BitMap bitmap1;
	Comand command1;//�R�}���h���C�������Ɋւ��邱��

	for (int i = 1; i < argc; i++) {
		command1.fileCheck(argv[i]);//�������̂�������ǂݍ��݂ł���悤�ɂ���B
	}
	for (int i = 0; i < command1.fileCount; i++) {//�R�}���h���C�������œǂݎ�����t�@�C�����J���邩�ǂ������ׂ�B

		if (bitmap1.readFileOpen(command1.filename[i])) {
			strcpy_s(filename[readCheck], 500, command1.filename[i]);//filename���R�s�[����
			readCheck++;											 //�����`�F�b�N
			if (max_width < bitmap1.iHeader.width) {
				max_width = bitmap1.iHeader.width;
			}
			if (max_height < bitmap1.iHeader.height) {
				max_height = bitmap1.iHeader.height;
			}
			
			fclose(bitmap1.bmp);
			
		}//�摜���J��//������true�ɕς���
	}
	
	printf(TEXT("Total File Count: %d\n"), readCheck);//�J�����摜�̌�
	
	while (readCheck == 0)//�����ŗ^�����Ȃ������������͓ǂݍ��݂ł��Ȃ��������ɓ���
	{
		printf("�ύX�������摜�̃p�X����͂���Enter�������Ă��������B\n");

		fgets(buf, sizeof(buf), stdin);						/* �����œ��� */
		sscanf_s(buf, "%s", &filename[readCheck], sizeof(filename[readCheck]));   /* �o�b�t�@����filename�Ɋi�[ */
		

		command1.fileCheck(filename[readCheck]);//�������̂�������ǂݍ��݂ł���悤�ɂ���B
		for (int i = 0; i < command1.fileCount; i++) {//�t�@�C�����J���邩�ǂ������ׂ�B

			if (bitmap1.readFileOpen(command1.filename[i])) {
				strcpy_s(filename[readCheck], 500, command1.filename[i]);//filename���R�s�[����
				readCheck++;											 //�����`�F�b�N
				if (max_width < bitmap1.iHeader.width) {
					max_width = bitmap1.iHeader.width;
				}
				if (max_height < bitmap1.iHeader.height) {
					max_height = bitmap1.iHeader.height;
				}

				fclose(bitmap1.bmp);

			}//�摜���J��//������true�ɕς���
		}

		if (readCheck != 0) {
			break;
		}
		else {
			printf("�G���[�摜��������܂���ł����B\n");
		}
		
	}

	printf("%d�̉摜�̓ǂݍ��݂ɐ������܂����B\n", readCheck);
	
	

	

	while (true) {
		printf("�{���w��̏ꍇ��'S'�F�s�N�Z���w��̏ꍇ��'P'����͂���Enter�������Ă��������B\n");
		fgets(buf, sizeof(buf), stdin);						/* �����œ��� */
		sscanf_s(buf, "%c", &scale_pixel, sizeof(scale_pixel));   /* �o�b�t�@����scale_pixel�Ɋi�[ */
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
			check_width = ((float)width / 100) * max_width;
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

			check_height = ((float)height / 100) * max_height;
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
	
	
	
	//1����������������
	for (int i = 0; i < readCheck; i++) {
		bitmap1.readFileOpen(filename[i]);//�摜��ǂݍ���

		bitmap1.BitScale(width, height, scale_pixel);				//�摜���g��k������


		strcpy_s(filename2, 500, filename[i]);
		if ((strstr(filename2, ").bmp")) != NULL) {
			char *adr = strstr(filename2, ").bmp");
			adr--;//�A�h���X��1���ɂ��炷�B9).bmp
			while (true) {
				printf("%s\n", adr);
				if (adr[0] == '9') {//9�Ȃ�
					adr--; //�A�h���X��1���ɂ��炷�B19).bmp
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
					char str[50];//�ꎞ�I�ɕۗ�
					adr++;
					strcpy_s(str, 50,adr);//9).bmp���ꎞ���
					adr[0] = '0'; adr++; //
					strcpy_s(adr, 50, str);//
				}
				else {
					char *adr = strstr(filename2, ".bmp");			//�n���ꂽ�p�X��.bmp��T���B
					strcpy_s(adr, 50, addname);						//�V�K�摜�ɖ��̕ύX
					break;
				}
			}
			
			//adr--;//�A�h���X��-
			//adr[0]++;//�������P���Z
		}
		else {
			char *adr = strstr(filename2, ".bmp");			//�n���ꂽ�p�X��.bmp��T���B
			strcpy_s(adr, 50, addname);						//�V�K�摜�ɖ��̕ύX
		}
		//char *adr = strstr(filename2, ".bmp");			//�n���ꂽ�p�X��.bmp��T���B
		//strcpy_s(adr, 50, addname);						//�V�K�摜�ɖ��̕ύX
		std::cout << filename2 << std::endl;


		bitmap1.writeFileClose(filename2);				//��������



		fclose(bitmap1.bmp);
		fclose(bitmap1.fp);

	}
	
	
	

	
	

	printf("����ɏI�����܂����B(�L�[���́{Enter�L�[�ŉ�ʂ���܂�)\n");
	
	while (true) {

		if (getchar() != '\n')break;
	}

	return 0;
}