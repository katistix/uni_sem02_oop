//
// Created by paultal on 02.04.2026.
//

#ifndef LAB07_CUSTOMVECTOR_H
#define LAB07_CUSTOMVECTOR_H


#define SCALE_FACTOR 2

template <typename  T> class CustomVector
{
private:
    T* data;

    int size;
    int capacity;

    void resize()
    {
        this->capacity *= SCALE_FACTOR;

        T* new_data = new T[this->capacity];

        for (int i = 0; i < this->size; i++)
        {
            new_data[i] = this->data[i];
        }
        delete[] this->data;

        this->data = new_data;
    }
public:
    CustomVector()
    {
        this->size = 0;
        this->capacity = 1;
        this->data = new T[this->capacity];
    }

    void add(T new_element)
    {
        if (this->size == this->capacity) resize();

        this->data[size] = new_element;
        size++;
    }

    void remove_index(const int index)
    {
        for (int i = index; i < this->size - 1; i++)
        {
            this->data[i] = this->data[i + 1];
        }
        --this->size;
    }

    [[nodiscard]] int get_size() const
    {
        return this->size;
    }

    T& get_by_index(int index) const
    {
        return this->data[index];
    }

};


#endif //LAB07_CUSTOMVECTOR_H
