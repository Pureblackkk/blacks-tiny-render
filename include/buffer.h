#ifndef BUFFER_H
#define BUFFER_H

template<typename T>
class Buffer {
    public:
        Buffer(int width, int height);
        void set(int x, int y, T value);
        T get(int x, int y) const;
        int size() const;
        void clean();
        int width() const;
        int height() const;

    private:
        T *buffer;
        int bWidth;
        int bHeight;
        int bSize;
};

template<typename T>
Buffer<T>::Buffer(int width, int height) {
    bWidth = width;
    bHeight = height;
    bSize = width * height;
    buffer = new int[width * height];
}

template<typename T>
void Buffer<T>::set(int x, int y, T value) {
    buffer[x + y * bWidth] = value;
}

template<typename T>
T Buffer<T>::get(int x, int y) const {
    return buffer[x + y * bWidth]
}

template<typename T>
int Buffer<T>::size() const {
    return bSize;
}

template<typename T>
int Buffer<T>::width() const {
    return bWidth;
}

template<typename T>
int Buffer<T>::height() const {
    return bHeight;
}
#endif