
template <typename T>
Heap<T>::Heap() : m_data(nullptr), m_size(0) {}

template <typename T>
Heap<T>::Heap(T& item) : Heap() {
    m_data = new T[1];
    m_data[0] = item;
    m_size = 1;
}

template <typename T>
Heap<T>::Heap(T&& item) : Heap(item) {};

template <typename T>
Heap<T>::Heap(T* items, int count) : Heap() {
    m_data = new T[count];
    m_size = count;

    for (int i = 0; i < count; i++) {
        m_data[i] = items[i];
    }
    quickSort(m_data, 0, count-1);
}

template <typename T>
Heap<T>::~Heap() {
    if (m_data)
        delete[] m_data;
}

template <typename T>
Heap<T>::Heap(Heap<T>& another) : Heap() {
    m_size = another.m_size;
    m_data = new T[m_size];
    for (int i = 0; i < m_size; i++)
        m_data[i] = another.m_data[i];
}

template <typename T>
Heap<T>& Heap<T>::insert(T& item) {
    if (m_size == 0)  {
        m_data = new T[1];
        m_data[0] = item;
        m_size++;
    } else {
        T* result = new T[++m_size];
        bool flag = false;
        for (int i = 0, j = 0; j < m_size; i++, j++) {
            if (flag || (m_data[i] > item && i < m_size - 1)) {
                result[j] = m_data[i];
            }
            else {
                result[j] = item;
                flag = true;
                i--;
            }
//            std::cout << j << " " << result[j] << " " << i << " " << m_data[i] << std::endl;
        }
        if (m_data)
            delete[] m_data;// if items are equal throw exc
        m_data = result;
    }
    return *this;
}

template <typename T>
Heap<T>& Heap<T>::insert(T&& item) {
    return insert(item);
}

template <typename T>
Heap<T>& Heap<T>::remove(T& item) {
    int i;
    for (i = 0; i < m_size; i++) {
        if (item == m_data[i]) break;
    }
    if (i == m_size)
        return *this;
    T* result = new T[--m_size];

    for (int j = 0; j < i; j++)
        result[j] = m_data[j];
    for (int j = i++; j < m_size; j++, i++)
        result[j] = m_data[i];

    delete[] m_data;
    m_data = result;
    return *this;
}

template <typename T>
Heap<T>& Heap<T>::remove(T&& item) {
    return remove(item);
}

template <typename T>
bool Heap<T>::searchItem(T& item) {
    for (int i = 0; i < m_size; i++)
        if (m_data[i] == item)
            return true;
    return false;
}

template <typename T>
bool Heap<T>::searchItem(T&& item) {
    return searchItem(item);
}

template <typename T>
Heap<T>* Heap<T>::cut(T& item) {
    int i;
    for (i = 0; i < m_size; i++) {
        if (m_data[i] == item)
            break;
    }
    if (i == m_size)
        return nullptr;
    Heap<T>* result = new Heap;
    preOrderTravers(i, [result](T* item){
        result->insert(*item);
    });
    return result;
}

template <typename T>
Heap<T>* Heap<T>::cut(T&& item) {
    return cut(item);
}

template <typename T>
void Heap<T>::print() {
    for (int i = 0; i < m_size; i++)
        std::cout << m_data[i] << " " << std::endl;
}

template <typename T>
int Heap<T>::getSize() {
    return m_size;
}

template <typename T>
bool Heap<T>::searchSubHeap(Heap<T>& another) {
    if (another.m_size > m_size) // checking m_size == 0 isn't needed
        return false;
    if (another.m_size == 0)
        return true;
    int i;
    for (i = 0; i < m_size; i++)
        if (m_data[i] == another.m_data[0])
            break;
    if (i == m_size)
        return false;
    for (int j = i; j - i < another.m_size; j++)
        if (m_data[j] != another.m_data[j - i])
            return false;

    return true;
}

template <typename T>
bool Heap<T>::searchSubHeap(Heap<T>&& another) {
    return searchSubHeap(another);
}

template <typename T>
void Heap<T>::quickSort(T* array, int low, int high) {
    int i = low;
    int j = high;
    T pivot = array[(i + j) / 2];
    T temp;

    while (i <= j)
    {
        while (array[i] > pivot)
            i++;
        while (array[j] < pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}

template <typename T>
int Heap<T>::getHeight(int index) {
    index++;
    if (index <= 0 || index >= m_size) return -1;
    int result = -1;
    while (index) {
        result++;
        index /= 2;
    }
    return result;
}

template <typename T>
int Heap<T>::getRightChild(int index) {
    if (index < 0 || index >= m_size)
        return -1;
    return 2 * index + 2;
}

template <typename T>
int Heap<T>::getLeftChild(int index) {
    if (index < 0 || index >= m_size)
        return -1;
    return 2 * index + 1;
}

template <typename T>
int Heap<T>::getParent(int index) {
    if (index < 0 || index >= m_size)
        return -1;
    return (index - 1) / 2;
}

template <typename T>
Heap<T>& Heap<T>::preOrderTravers(int index, std::function<void(T*)> func) {
    if (index >= 0 && index < m_size) {
        func(m_data + index);
        preOrderTravers(getLeftChild(index), func);
        preOrderTravers(getRightChild(index), func);
    }
    return *this;
}