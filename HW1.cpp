/*
Степанян Григорий
Visual Studio 2019

1.Добавить в контейнерный класс, который был написан в этом уроке, методы:
    -для добавления нового элемента в произвольное место
    -для добавления нового элемента на последнее место
    -для удаления последнего элемента массива (аналог функции pop_back() в векторах)
    -для сортировки массива.

*/
#include <iostream> 
#include <cstdlib>
#include <cassert>
#include <algorithm>

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }
    void erase()
    {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
    }
    int getLength() { return m_length; }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void resize(int newLength)
    {
        if (newLength == m_length)
            return;

        if (newLength <= 0)
        {
            erase();
            return;
        }

        int* data = new int[newLength];
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);
        int* data = new int[m_length + 1];

        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        data[index] = value;

        for (int after = index; after < m_length; ++after)
            data[after + 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) { insertBefore(value, m_length); }

    void pop_back()
    {
        int* data = new int[m_length - 1];
        for (int i = 0; i < m_length - 1; ++i)
            data[i] = m_data[i];
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void sortArray()
    {
        int start = 0;
        int end = m_length;
        int* data = new int[end];
        for (int j = start; j < end; ++j)
        {
            data[j] = m_data[j];
        }
        std::sort(data, data + 8);

        delete[] m_data;
        m_data = data;
    }
};

int main()
{
    ArrayInt array(10);

    for (int i = 0; i < 10; i++)
        array[i] = i + 1;

    array.resize(7);

    array.insertBefore(15, 4);

    array.pop_back();

    array.push_back(35);


    for (int j = 0; j < array.getLength(); j++)
        std::cout << array[j] << " ";
    std::cout << std::endl;
    array.sortArray();

    for (int j = 0; j < array.getLength(); j++)
        std::cout << array[j] << " ";
    std::cout << std::endl;
    return 0;
}