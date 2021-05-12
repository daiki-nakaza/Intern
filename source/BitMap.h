#include <string>

#define FILE_HEADER_SIZE 14
#define FILE_INFO_SIZE 40

using namespace std;

/************************
* ファイルヘッダー構造体
*************************/
typedef struct FileHeader {
	uint8_t data[FILE_HEADER_SIZE];  // 加工前データ（書き出しのため必要）  
	string fileType;                 // ファイルタイプ  
	int fileSize;                    // ファイルサイズ  
} FileHeader;

/*******************
* 情報ヘッダー構造体
********************/
typedef struct InfoHeader {
	uint8_t data[FILE_INFO_SIZE];  // 加工前データ（書き出しのため必要）  
	int infoHeaderSize;              // 情報ヘッダのサイズ  
	int width;                       // 画像の幅  
	int height;                      // 画像の高さ  
	int clrPerPixel;                 // 1ピクセル当たりの色数  
	int dataSize;                    // 画像データのサイズ  
} InfoHeader;

/************
*カラー構造体
*************/
typedef struct Color {
	int r;
	int g;
	int b;
} Color;





/******
*クラス
*******/
class BitMap
{
private:
	bool ColorBit = false;//深度8ビット以下ならtrue
	float scale_width = 1.0f;
	float scale_height = 1.0f;
	int pixel_width = 1;
	int pixel_height = 1;
public:
	FILE *bmp;//読み込みファイル
	uint8_t *org;            // ビットマップデータ（オリジナル）  
	uint8_t *img;            // ビットマップデータ（加工用）  
	size_t size;

	FILE *fp;//書き込み用ファイル


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


