#ifndef COLOR_H
#define COLOR_H

struct Color {
    union {
		struct {
			unsigned char b, g, r, a;
		};
		unsigned char raw[4];
		unsigned int val;
	};
	int bytespp;

	Color() : val(0), bytespp(1) {
	}

	Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : b(B), g(G), r(R), a(A), bytespp(4) {
	}

	Color(int v, int bpp) : val(v), bytespp(bpp) {
	}

	Color(const Color &c) : val(c.val), bytespp(c.bytespp) {
	}

	Color(const unsigned char *p, int bpp) : val(0), bytespp(bpp) {
		for (int i=0; i<bpp; i++) {
			raw[i] = p[i];
		}
	}

	Color & operator =(const Color &c) {
		if (this != &c) {
			bytespp = c.bytespp;
			val = c.val;
		}
		return *this;
	}
};

class Image {
	protected:
		unsigned char* data;
		int width;
		int height;
		int bytespp;
    public:
        virtual ~Image() {};
        virtual bool read_file(const char *filename) = 0;
        virtual bool write_file(const char *filename, bool rle=true) = 0;
        virtual bool flip_horizontally() = 0;
        virtual bool flip_vertically() = 0;
        virtual bool scale(int w, int h) = 0;
        virtual Color get(int x, int h) = 0;
        virtual bool set(int x, int y, Color c) = 0;
        virtual Image & operator=(Image &img) = 0;
        virtual int get_width() = 0;
        virtual int get_height() = 0;
        virtual int get_bytespp() = 0;
        virtual unsigned char *buffer() = 0;
        virtual void clear() = 0;
};

#endif