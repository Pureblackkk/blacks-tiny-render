#include<pngimage.h>
#include <stdio.h>
#include<iostream>

// TODO: delete data
PNGImage::~PNGImage(){
    for(int i = 0; i < height; i++) {
        free(row_pointers[i]);
    }
    free(row_pointers);
}

PNGImage::PNGImage(){}

bool PNGImage::read_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png) return false;

    png_infop info = png_create_info_struct(png);
    if(!info) return false;

    if(setjmp(png_jmpbuf(png))) return false;

    // Read png
    png_init_io(png, fp);
    png_read_info(png, info);

    // Set png info
    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    // Read any color_type into 8bit depth, RGBA format
    if (bit_depth == 16)
        png_set_strip_16(png);
    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);
    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);
    if(
        color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE
    )
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
        
    if(
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA
    )
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);
    if (row_pointers) abort();

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
    }
    png_read_image(png, row_pointers);

    png_destroy_read_struct(&png, &info, NULL);
    return true;
}

// TODO: no need to implement for now
bool PNGImage::write_file(const char *filename, bool rle) {
    FILE *fp = fopen(filename, "wb");
    if(!fp) return false;
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) return false;
    png_infop info = png_create_info_struct(png);
    if (!info) return false;
    if (setjmp(png_jmpbuf(png))) return false;

    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);
    if (!row_pointers) return false;
    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    // Close file
    fclose(fp);
    return true;
}

// TODO: no need to implement for now
bool PNGImage::flip_horizontally() {
    throw std::runtime_error("method not implement");
    return false;
}

// TODO: no need to implement for now
bool PNGImage::flip_vertically() {
    throw std::runtime_error("method not implement");
    return false;
}

// TODO: no need to implement for now
bool PNGImage::scale(int w, int h) {
    throw std::runtime_error("method not implement");
    return false;
}

Color PNGImage::get(int x, int y) {
    png_bytep targetRow = row_pointers[y];
    png_bytep targetPixel = &(targetRow[x * 4]);

    uint8_t red = targetPixel[0];
    uint8_t green = targetPixel[1];
    uint8_t blue = targetPixel[2];
    uint8_t alpha = targetPixel[3];

    return Color(red, green, blue, alpha);
}

bool PNGImage::set(int x, int y, Color c) {
    png_bytep targetRow = row_pointers[y];
    png_bytep targetPixel = &(targetRow[x * 4]);

    targetPixel[0] = c.r;
    targetPixel[1] = c.g;
    targetPixel[2] = c.b;
    targetPixel[3] = c.a;

    return true;
}

// TODO: no need to implement for now
PNGImage & PNGImage::operator=(Image &img) {
    throw std::runtime_error("method not implement");
}

int PNGImage::get_width() {
    return width;
}

int PNGImage::get_height() {
    return height;
}

int PNGImage::get_bytespp() {
    return sizeof(png_bytep);
}

// TODO: no need to implement for now
unsigned char* PNGImage::buffer() {
    throw std::runtime_error("method not implement");
}

// TODO: no need to implement for now
void PNGImage::clear() {
    throw std::runtime_error("method not implement");
}