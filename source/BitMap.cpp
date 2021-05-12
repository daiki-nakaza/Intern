#include "BitMap.h"

using namespace std;


/*****************************
* 4�r�b�g����Int�����l�ɕϊ�
*****************************/
int BitMap::bit2Integer(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4) {
	return b1 +
		b2 * 256 +
		b3 * 256 * 256 +
		b4 * 256 * 256 * 256;
	//413078
}

/*****************************
* Int�����l��4�r�b�g���ɕϊ�
*****************************/
uint8_t BitMap::bit4(int integ, int num) {
	uint8_t b1, b2,  b3,  b4;
	b4 = integ / (256 * 256 * 256);
	integ = integ % (256 * 256 * 256);

	b3 = integ / (256 * 256);
	integ = integ % (256 * 256);

	b2 = integ / 256;
	integ = integ % 256;

	b1 = integ;

	switch (num)
	{
	case 1:
		return b1;
	case 2:
		return b2;
	case 3:
		return b3;
	case 4:
		return b4;
	}

	return 0;
}

/************************
*�O���[�X�P�[���ɕύX����
************************/
int BitMap::ColorChange(int r,int g,int b) {
	//Gray = r*0.3 + g*0.59 + b*0.11
	int Gray = r * 30 + g * 59 + b * 11;
	Gray = Gray / 100;
	/*int Gray = (r + g + b) / 3;*/

	return Gray;
}

/************
*�ǂݍ��ݕ���
************/
bool BitMap::readFileOpen(string filename) {

	if (bmp != NULL) {
		fclose(bmp);
	}

	errno_t error;
	//�t�@�C�����J��
	error = fopen_s(&bmp, filename.c_str()/*"image/test.bmp"*/, "rb");

	if (error != 0) {
		printf("�t�@�C�����J���܂���ł����B������x���͂����Ă��������B\n");
		
		return false;
	}
	if (bmp == NULL) {
		printf("�t�@�C���I�[�v���Ɏ��s���܂����B������x���͂����Ă��������B\n");
		
		return false;
	}

	readFileHeader();
	readFileInfo();
	//�[�x��8�r�b�g�ȉ��Ȃ�F���Ɏw�肷��
	if (ColorBit) {
		readFilePalette();
	}
	readFileImage();

	return true;
}

/*�t�@�C���w�b�_�[�ǂݍ���*/
void BitMap::readFileHeader() {
	uint8_t data[FILE_HEADER_SIZE];
	size = fread(data, sizeof(uint8_t), FILE_HEADER_SIZE, bmp);

	memcpy(fHeader.data, data, sizeof(data));

	//BM���\��
	fHeader.fileType = "";
	fHeader.fileType += data[0];
	fHeader.fileType += data[1];
	fHeader.fileSize = bit2Integer(data[2], data[3], data[4], data[5]);

}

/*���w�b�_�ǂݍ���*/
void BitMap::readFileInfo() {
	uint8_t data[FILE_INFO_SIZE];
	size = fread(data, sizeof(uint8_t), FILE_INFO_SIZE, bmp);

	memcpy(iHeader.data, data, sizeof(data));
	iHeader.infoHeaderSize = bit2Integer(data[0], data[1], data[2], data[3]);
	iHeader.width = bit2Integer(data[4], data[5], data[6], data[7]);
	iHeader.height = bit2Integer(data[8], data[9], data[10], data[11]);
	iHeader.clrPerPixel = bit2Integer(data[14], data[15], 0, 0);
	iHeader.dataSize = bit2Integer(data[20], data[21], data[22], data[23]);
	if (iHeader.clrPerPixel <= 8) {
		ColorBit = true;
	}
}

/*�p���b�g�f�[�^����Γǂݍ���*/
void BitMap::readFilePalette() {
	uint8_t data[1024];

	//bitPix�ɂ̓r�b�g��������̂ŁA�F����useColor�ɂ����
	int bitPix = iHeader.clrPerPixel;
	int useColor = 1;
	for (int j = 0; j < bitPix; j++) {
		useColor *= 2;
	}

	size = fread(data, sizeof(uint8_t), useColor *4, bmp);
	for (int n = 0; n < useColor; n++) {
		color[n].b = data[n * 4 + 0];
		color[n].g = data[n * 4 + 1];
		color[n].r = data[n * 4 + 2];
	}
}

/*�摜�f�[�^�ǂݍ���*/
void BitMap::readFileImage() {
	//8�r�b�g�ȉ��̏ꍇ
	if (ColorBit) {
		int sz = iHeader.dataSize;
		org = new uint8_t[sz];
		img = new uint8_t[sz];
		size = fread(org, sizeof(uint8_t), sz, bmp);
		memcpy(img, org, sz);
		if (size != sz) {
			printf("�摜�f�[�^�ǂݍ��݂̃T�C�Y���������Ă��܂��B�P\n");

			return;
		}

	}
	else {
		int sz = iHeader.dataSize;
		org = new uint8_t[sz];
		img = new uint8_t[sz];
		size = fread(org, sizeof(uint8_t), sz, bmp);
		memcpy(img, org, sz);
		if (size != sz) {
			printf("�摜�f�[�^�ǂݍ��݂̃T�C�Y���������Ă��܂��B�Q\n");
			return;
		}
	}
}



/************
*�������ݕ���
************/
void BitMap::writeFileClose(string filename2) {
	if (ColorBit) {

		errno_t error;
		error = fopen_s(&fp, filename2.c_str()/*"image/test.bmp"*/, "wb");

		if (error != 0) {
			printf("�V�K�t�@�C�����J���܂���ł����B�P(�L�[���́{Enter�L�[�ŉ�ʂ���܂�)\n");
			while (true) {

				if (getchar() != '\n')break;
			}
			exit(1);
			return;
		}
		if (fp == NULL) {
			printf("�V�K�t�@�C�����J���܂���ł����B�P(�L�[���́{Enter�L�[�ŉ�ʂ���܂�)\n");
			while (true) {

				if (getchar() != '\n')break;
			}
			exit(1);
			return;
		}
		writeFileHeader();
		writeFileInfo();
		writeFilePalette();
		writeFileImage();
		

	}
	else {
		errno_t error;
		error = fopen_s(&fp, filename2.c_str()/*"image/test.bmp"*/, "wb");

		if (error != 0) {
			printf("�V�K�t�@�C�����J���܂���ł����B�Q(�L�[���́{Enter�L�[�ŉ�ʂ���܂�)\n");
			while (true) {

				if (getchar() != '\n')break;
			}
			exit(1);
			return;
		}
		if (fp == NULL) {
			printf("�V�K�t�@�C�����J���܂���ł����B�Q(�L�[���́{Enter�L�[�ŉ�ʂ���܂�)\n");
			while (true) {

				if (getchar() != '\n')break;
			}
			exit(1);
			return;
		}

		writeFileHeader();
		writeFileInfo();
		writeFileImage();
	}
}

/*�t�@�C���w�b�_�[��������*/
void BitMap::writeFileHeader() {
	//���̂܂܏�������ł��܂�
	fwrite(fHeader.data, sizeof(uint8_t), FILE_HEADER_SIZE, fp);
}

/*���w�b�_�[��������*/
void BitMap::writeFileInfo() {
	//���̂܂܏�������ł��܂��B
	fwrite(iHeader.data, sizeof(uint8_t), FILE_INFO_SIZE, fp);
}

/*�p���b�g�f�[�^�̏�������*/
void BitMap::writeFilePalette() {
	uint8_t data[1024];//�Ō�t�@�C���ɏ������ނ悤�ɕύX�_�Ȃǂ��܂Ƃ߂�B�p���b�g�f�[�^�͍ő�ł�1024�F�����Ȃ��̂ő����B

	//bitPix�ɂ̓r�b�g��������̂ŁA�F����useColor�ɂ����
	int bitPix = iHeader.clrPerPixel;
	int useColor = 1;
	for (int j = 0; j < bitPix; j++) {
		useColor *= 2;                    //�Q�̃r�b�g������Ă���B
	}


	//�O���[�X�P�[�����f
	for (int n = 0; n < useColor; n++) {
		int r = color[n].r, g = color[n].g, b = color[n].b;
		int Gray = ColorChange(r, g, b);

		data[n * 4 + 0] = Gray/*color[n].b*/;
		data[n * 4 + 1] = Gray/*color[n].g*/;
		data[n * 4 + 2] = Gray/*color[n].r*/;
		data[n * 4 + 3] = 0;
	}

	fwrite(data, sizeof(uint8_t), useColor *4, fp);
	
}

/*�摜�f�[�^�̏�������*/
void BitMap::writeFileImage() {
	//�[�x���W�ȉ��̎�
	if (ColorBit) {
		int sz = iHeader.dataSize;
		size = fwrite(img, sizeof(uint8_t), sz, fp);
		if (size != sz) {
			printf("�摜�f�[�^�������݂̃T�C�Y���������Ă��܂��B�P\n");
			return;
		}
	}
	else {
		int sz = iHeader.dataSize;

		//�O���[�X�P�[�����f
		for (int n = 0; n < sz/3; n++) {
			int r = img[n * 3 + 2], g = img[n * 3 + 1], b = img[n * 3];
			int Gray = ColorChange(r, g, b);

			img[n * 3 + 0] = Gray/*org[n * 3 + 0]*/;
			img[n * 3 + 1] = Gray/*org[n * 3 + 1]*/;
			img[n * 3 + 2] = Gray/*org[n * 3 + 2]*/;
		}
		size = fwrite(img, sizeof(uint8_t), sz, fp);
		if (size != sz) {
			printf("�摜�f�[�^�������݂̃T�C�Y���������Ă��܂��B�Q\n");
			return;
		}
	}
}



/********
*�ύX����
********/
void BitMap::BitScale(int width, int height, char scale_or_pixel) {

	if (scale_or_pixel == 's' || scale_or_pixel == 'S') {
		scale_width = ((float)width / 100);
		scale_height = ((float)height / 100);
		pixel_width = iHeader.width*scale_width;
		pixel_height = iHeader.height*scale_height;
	}
	else if(scale_or_pixel == 'p' || scale_or_pixel == 'P'){
		pixel_width = width;
		pixel_height = height;
		scale_width = (float)pixel_width / (float)iHeader.width;
		scale_height = (float)pixel_height / (float)iHeader.height;
		
	}
	printf("\n���@�F%dpx�F%.0f��\n", pixel_width, scale_width*100);
	printf("�����F%dpx�F%.0f��\n", pixel_height, scale_height*100);
	//printf("%f\n%f\n%d\n%d\n", scale_width, scale_height, pixel_width, pixel_height);

	widthScale();
	imageScale();
}


/*�摜�̕����L����*//*�������ǉ�*/
void BitMap::widthScale() {
	//8bit�ȉ�
	if (ColorBit) {
		int new_width = pixel_width;
		int new_height = pixel_height;


		uint8_t data[FILE_INFO_SIZE];
		
		memcpy(data, iHeader.data, FILE_INFO_SIZE);

		//width��ύX����
		data[4] = bit4(new_width, 1);
		data[5] = bit4(new_width, 2);
		data[6] = bit4(new_width, 3);
		data[7] = bit4(new_width, 4);

		//height��ύX����
		data[8] = bit4(new_height, 1);
		data[9] = bit4(new_height, 2);
		data[10] = bit4(new_height, 3);
		data[11] = bit4(new_height, 4);

		int image_width = new_width;
		//799�Ȃ�1���{���邽��
		if (new_width % 4 != 0) {
			image_width += (4 - new_width % 4);
		}
		//�t�@�C���T�C�Y�ύX
		fHeader.fileSize += ((image_width * new_height) - iHeader.dataSize);

		//imagesize��ύX����
		size = iHeader.dataSize;
		iHeader.dataSize = image_width * new_height;
		data[20] = bit4(iHeader.dataSize, 1);
		data[21] = bit4(iHeader.dataSize, 2);
		data[22] = bit4(iHeader.dataSize, 3);
		data[23] = bit4(iHeader.dataSize, 4);


		memcpy(iHeader.data, data, FILE_INFO_SIZE);

		uint8_t data2[FILE_HEADER_SIZE];
		memcpy(data2, fHeader.data, FILE_HEADER_SIZE);
		data2[2] = bit4(fHeader.fileSize, 1);
		data2[3] = bit4(fHeader.fileSize, 2);
		data2[4] = bit4(fHeader.fileSize, 3);
		data2[5] = bit4(fHeader.fileSize, 4);
		memcpy(fHeader.data, data2, FILE_HEADER_SIZE);
	}
	else {
		int new_width = pixel_width;
		int new_height = pixel_height;


		uint8_t data[FILE_INFO_SIZE];

		memcpy(data, iHeader.data, FILE_INFO_SIZE);

		//width��ύX����
		data[4] = bit4(new_width, 1);
		data[5] = bit4(new_width, 2);
		data[6] = bit4(new_width, 3);
		data[7] = bit4(new_width, 4);

		//height��ύX����
		data[8] = bit4(new_height, 1);
		data[9] = bit4(new_height, 2);
		data[10] = bit4(new_height, 3);
		data[11] = bit4(new_height, 4);

		int image_width = new_width;

		int new_blank = 0;
		int old_blank = 0;
		//
		if ((new_width*3) % 4 != 0) {
			new_blank += (4 - (new_width*3) % 4);
		}
		if ((iHeader.width * 3) % 4 != 0) {
			old_blank += (4 - (iHeader.width * 3) % 4);
		}

		//�t�@�C���T�C�Y�ύX
		fHeader.fileSize += ((image_width * new_height * 3 + new_blank * new_height) - iHeader.dataSize);

		//imagesize��ύX����
		size = iHeader.dataSize;
		iHeader.dataSize = image_width * new_height * 3 + new_blank * new_height;
		data[20] = bit4(iHeader.dataSize, 1);
		data[21] = bit4(iHeader.dataSize, 2);
		data[22] = bit4(iHeader.dataSize, 3);
		data[23] = bit4(iHeader.dataSize, 4);


		memcpy(iHeader.data, data, FILE_INFO_SIZE);

		uint8_t data2[FILE_HEADER_SIZE];
		memcpy(data2, fHeader.data, FILE_HEADER_SIZE);
		data2[2] = bit4(fHeader.fileSize, 1);
		data2[3] = bit4(fHeader.fileSize, 2);
		data2[4] = bit4(fHeader.fileSize, 3);
		data2[5] = bit4(fHeader.fileSize, 4);
		memcpy(fHeader.data, data2, FILE_HEADER_SIZE);
	}
}

/*�摜�����Ȃ���*/
void BitMap::imageScale() {
	if (ColorBit) {
		if (img != NULL) {
			delete img;
		}
		int new_width = pixel_width;
		int new_height = pixel_height;


		int sz = iHeader.dataSize;
		img = new uint8_t[sz];

		int image_width = new_width;
		int old_image_width = iHeader.width;
		//799�Ȃ�1���{���邽��
		if (new_width % 4 != 0) {
			image_width += (4 - new_width % 4);
		}
		if (iHeader.width % 4 != 0) {
			old_image_width += (4 - iHeader.width % 4);
		}
		uint8_t F = 255;
		int sz2 = 0;
	
		for (int n = 0; n < new_height; n++) {
			for (int j = 0; j < image_width; j++) {
				
				
				img[(n*image_width) + j] = org[((int)(n/ scale_height)*old_image_width) + (int)(j / scale_width)];
				sz2++;
			}
		}

		if (sz2 != sz) {
			printf("�g���̃T�C�Y�������Ă܂���B");
		}
		iHeader.width = new_width;
		iHeader.height = new_height;

	}
	else {
		if (img != NULL) {
			delete img;
		}
		int new_width = pixel_width;
		int new_height = pixel_height;

		int sz = iHeader.dataSize;
		img = new uint8_t[sz];

		int image_width = new_width;
		int old_image_width = iHeader.width;
		int old_blank = 0, new_blank = 0;//���ꂪ�p�f�B���O

		//3�{�������Ƃ̃p�f�B���O
		if ((new_width * 3) % 4 != 0) {
			new_blank += (4 - (new_width*3) % 4);
		}
		if ((iHeader.width*3) % 4 != 0) {
			old_blank += (4 - (iHeader.width*3) % 4);
		}
		
		uint8_t F = 255;
		int sz2 = 0;
		

		for (int n = 0; n < new_height; n++) {
			for (int j = 0; j < image_width ; j++) {
				
				img[(int)(n*image_width * 3) + new_blank * n + j * 3 + 0] = org[((int)(n / scale_height)*old_image_width * 3) + old_blank * n + (int)(j / scale_width) * 3 + 0];
				sz2++;
				img[(int)(n*image_width * 3) + new_blank * n + j * 3 + 1] = org[((int)(n / scale_height)*old_image_width * 3) + old_blank * n + (int)(j / scale_width) * 3 + 1];
				sz2++;
				img[(int)(n*image_width * 3) + new_blank * n + j * 3 + 2] = org[((int)(n / scale_height)*old_image_width * 3) + old_blank * n + (int)(j / scale_width) * 3 + 2];
				sz2++;
			}
			sz2 += new_blank;
		}
		/*printf("%d", old_image_width);
		printf("%d", image_width);*/
		if (sz2 != sz) {
			printf("�g���̃T�C�Y�������Ă܂���B");
		}
		iHeader.width = new_width;
	}
}


