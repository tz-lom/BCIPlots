#ifndef CYCLICVECTOR_H
#define CYCLICVECTOR_H

template<typename T>
class CyclicVector
{
public:
    CyclicVector(int length=1);
    ~CyclicVector();

    void append(T value);
    T& operator[](int item);
    T& operator()(int item);

    void resize(int length);
    void clear();

    int size();

    int internalPos() { return pos; }

private:
    T *buffer;
    int pos;
    int length;
};


template<typename T>
CyclicVector<T>::CyclicVector(int length)
{
    this->length = length<1?1:length;
    buffer = new T[this->length];
    clear();
}

template<typename T>
CyclicVector<T>::~CyclicVector()
{
    delete buffer;
}

template<typename T>
int CyclicVector<T>::size()
{
    return length;
}

template<typename T>
void CyclicVector<T>::resize(int length)
{
    if(length==this->length) return;
    this->length = length;
    delete buffer;
    buffer = new T[length];
    clear();
}

template<typename T>
void CyclicVector<T>::clear()
{
    for(int t=0; t<length; ++t)
    {
        buffer[t] = T();
    }
    pos = 0;
}

template<typename T>
void CyclicVector<T>::append(T value)
{
    buffer[pos] = value;
    if(++pos==length) pos=0;
}

template<typename T>
T& CyclicVector<T>::operator[](int item)
{
    return buffer[(pos+item)%length];
}

template<typename T>
T& CyclicVector<T>::operator()(int item)
{
    return buffer[item];
}


#endif // CYCLICVECTOR_H
