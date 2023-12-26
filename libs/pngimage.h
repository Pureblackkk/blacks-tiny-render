#ifndef PNGIMAGE_H
#define PNGIMAGE_H

#include<image.h>
#include<png.h>

class PNGImage: public Image {
    protected: 
        int width;
        int height;
        png_bytep *row_pointers = NULL;

    public:
        PNGImage();
        ~PNGImage();
        bool read_file(const char *filename);
        bool write_file(const char *filename, bool rle=true);
        bool flip_horizontally();
	    bool flip_vertically();
        bool scale(int w, int h);
        Color get(int x, int y);
        bool set(int x, int y, Color c);
        PNGImage & operator=(Image &img);
        int get_width();
        int get_height();
        int get_bytespp();
        unsigned char *buffer();
        void clear();
};

#endif