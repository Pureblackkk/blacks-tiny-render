#ifndef TGAIMAGE_H
#define TGAIMAGE_H

#include<image.h>
#include<fstream>

#pragma pack(push,1)
struct TGA_Header {
	char idlength;
	char colormaptype;
	char datatypecode;
	short colormaporigin;
	short colormaplength;
	char colormapdepth;
	short x_origin;
	short y_origin;
	short width;
	short height;
	char  bitsperpixel;
	char  imagedescriptor;
};
#pragma pack(pop)

class TGAImage : public Image {
protected:
	unsigned char* data;
	int width;
	int height;
	int bytespp;

	bool load_rle_data(std::ifstream &in);
	bool unload_rle_data(std::ofstream &out);
public:
	enum Format {
		GRAYSCALE=1, RGB=3, RGBA=4
	};

	TGAImage();
	TGAImage(int w, int h, int bpp);
	TGAImage(const TGAImage &img);
	bool read_file(const char *filename);
	bool write_file(const char *filename, bool rle=true);
	bool flip_horizontally();
	bool flip_vertically();
	bool scale(int w, int h);
	Color get(int x, int y);
	bool set(int x, int y, Color c);
	~TGAImage();
	TGAImage & operator=(Image &img);
	int get_width();
	int get_height();
	int get_bytespp();
	unsigned char *buffer();
	void clear();
};

#endif