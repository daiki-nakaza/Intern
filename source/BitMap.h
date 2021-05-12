#include <string>

#define FILE_HEADER_SIZE 14
#define FILE_INFO_SIZE 40

using namespace std;

/************************
* �t�@�C���w�b�_�[�\����
*************************/
typedef struct FileHeader {
	uint8_t data[FILE_HEADER_SIZE];  // ���H�O�f�[�^�i�����o���̂��ߕK�v�j  
	string fileType;                 // �t�@�C���^�C�v  
	int fileSize;                    // �t�@�C���T�C�Y  
} FileHeader;

/*******************
* ���w�b�_�[�\����
********************/
typedef struct InfoHeader {
	uint8_t data[FILE_INFO_SIZE];  // ���H�O�f�[�^�i�����o���̂��ߕK�v�j  
	int infoHeaderSize;              // ���w�b�_�̃T�C�Y  
	int width;                       // �摜�̕�  
	int height;                      // �摜�̍���  
	int clrPerPixel;                 // 1�s�N�Z��������̐F��  
	int dataSize;                    // �摜�f�[�^�̃T�C�Y  
} InfoHeader;

/************
*�J���[�\����
*************/
typedef struct Color {
	int r;
	int g;
	int b;
} Color;





/******
*�N���X
*******/
class BitMap
{
private:
	bool ColorBit = false;//�[�x8�r�b�g�ȉ��Ȃ�true
	float scale_width = 1.0f;
	float scale_height = 1.0f;
	int pixel_width = 1;
	int pixel_height = 1;
public:
	FILE *bmp;//�ǂݍ��݃t�@�C��
	uint8_t *org;            // �r�b�g�}�b�v�f�[�^�i�I���W�i���j  
	uint8_t *img;            // �r�b�g�}�b�v�f�[�^�i���H�p�j  
	size_t size;

	FILE *fp;//�������ݗp�t�@�C��


	FileHeader fHeader;
	InfoHeader iHeader;
	Color color[256];

	int bit2Integer(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
	uint8_t bit4(int Integ, int num);
	int ColorChange(int r,int  g, int b);

	bool readFileOpen(string filename);
	void readFileHeader();
	void readFileInfo();
	void readFilePalette();
	void readFileImage();

	void writeFileClose(string filename2);
	void writeFileHeader();
	void writeFileInfo();
	void writeFilePalette();
	void writeFileImage();


	void BitScale(int width, int height, char scale_or_pixel);
	void widthScale();
	void imageScale();
	
};


