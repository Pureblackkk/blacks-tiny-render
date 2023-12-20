#ifndef BUFFER_H
#define BUFFER_H

template<typename T>
class Buffer {
    public:
        Buffer(int width, int height);
        Buffer(int width, int height, const T initValue);
        void set(int x, int y, const T value);
        T* get();
        T get(int x, int y) const;
        int size() const;
        int typeBytes() const;
        void clean();
        void clean(T val);
        int width() const;
        int height() const;

    private:
        T *buffer;
        int bWidth;
        int bHeight;
        int bSize;
        int bTypeBytes;
};

template<typename T>
Buffer<T>::Buffer(int width, int height) {
    bWidth = width;
    bHeight = height;
    bSize = width * height;
    bTypeBytes = sizeof(T);
    buffer = new T[width * height];
}

template<typename T>
Buffer<T>::Buffer(int width, int height, const T initValue) {
    bWidth = width;
    bHeight = height;
    bSize = width * height;
    bTypeBytes = sizeof(T);
    buffer = new T[width * height];

    // Initial value
    for (int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            Buffer<T>::set(i, j, initValue);
        }
    }
}

template<typename T>
void Buffer<T>::set(int x, int y, const T value) {
    buffer[x + y * bWidth] = value;
}

template<typename T>
T* Buffer<T>::get() {
    return buffer;
}

template<typename T>
T Buffer<T>::get(int x, int y) const {
    return buffer[x + y * bWidth];
}

template<typename T>
int Buffer<T>::size() const {
    return bSize;
}

template<typename T>
int Buffer<T>::typeBytes() const {
    return bTypeBytes;
}

template<typename T>
void Buffer<T>::clean() {
    for(int i = 0; i < bSize; i++) {
        buffer[i] = T();
    }
}

template<typename T>
void Buffer<T>::clean(T val) {
    for(int i = 0; i < bSize; i++) {
        buffer[i] = T(val);
    }
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