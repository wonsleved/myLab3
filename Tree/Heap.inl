
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
    if (searchItem(item))
        throw(Exceptions(ExceptionConsts::ITEM_EXISTS));
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


    return searchSubHeapDev(i, 0, another);;
}

template <typename T>
bool Heap<T>::searchSubHeap(Heap<T>&& another) {
    return searchSubHeap(another);
}

template <typename T>
Heap<T>* Heap<T>::writeToFile(std::string& path) {
    std::ofstream wf(path, std::ios::out | std::ios::binary);
    if(!wf) {
        throw(Exceptions(ExceptionConsts::FILE_ERROR));
        return nullptr;
    }

    wf.write((char *)& m_size, sizeof(int));

    for (int i = 0; i < m_size; i++) {
        wf.write((char *)& m_data[i], sizeof(T));
    }
    wf.close();
    if(!wf.good()) {
        throw(Exceptions(ExceptionConsts::FILE_ERROR));
        return nullptr;
    }
    return this;
}

template <typename T>
Heap<T>* Heap<T>::writeToFile(std::string&& path) {
    return writeToFile(path);
}

template <typename T>
Heap<T>* Heap<T>::insertFromFile(std::string& path) {
    std::ifstream rf(path, std::ios::out | std::ios::binary);
    if(!rf) {
        throw(Exceptions(ExceptionConsts::FILE_ERROR));
        return nullptr;
    }

    int size = 0;
    rf.read((char *) &size, sizeof(int));
    T* tmp = new T;
    for (int i = 0; i < size; i++) {
        rf.read((char *) tmp, sizeof(T));
        insert(*tmp);
    }


    delete tmp;


    rf.close();
    if(!rf.good()) {
        throw(Exceptions(ExceptionConsts::FILE_ERROR));
        return nullptr;
    }
    return this;
}

template <typename T>
Heap<T>* Heap<T>::insertFromFile(std::string&& path) {
    return insertFromFile(path);
}

//
//          PRIVATE
//

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
int Heap<T>::getHeight(int index) const{
    index++;
    if (index <= 0 || index > m_size) return -1;
    int result = 0;
    while (index) {
        result++;
        index /= 2;
    }
    return result;
}

template <typename T>
bool Heap<T>::searchSubHeapDev(int destination, int source, Heap<T>& another) {
    bool result;
    if (source >= another.m_size) {
        return true;
    }
    else if (m_size <= destination) {
        return false;
    }
    else {

        if (m_data[destination] == another.m_data[source]) {
            if (
                    searchSubHeapDev(getLeftChild(destination), getLeftChild(source), another) &&
                    searchSubHeapDev(getRightChild(destination), getRightChild(source), another ) )
            {
                return true;
            }
        }
        result = searchSubHeapDev(getLeftChild(destination), source, another) ||
                 searchSubHeapDev(getRightChild(destination), source, another);
    }
    return result;
}

template <typename T>
int Heap<T>::getRightChild(int index) const{
//    if (index < 0 || index >= m_size)
//        return -1;
    return 2 * index + 2;
}

template <typename T>
int Heap<T>::getLeftChild(int index) const{
//    if (index < 0 || index >= m_size)
//        return -1;
    return 2 * index + 1;
}

template <typename T>
int Heap<T>::getParent(int index) const{
//    if (index < 0 || index >= m_size)
//        return -1;
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


//
//          OUTPUT
//

template <typename T>
Heap<T>& Heap<T>::print() {
    preOrderTravers(0, [](T* item){
        item->cout();
    });
    return *this;
}


template <typename T>
typename Heap<T>::displayRows Heap<T>::getRowDisplay() const {
    // start off by traversing the tree to
    // build a vector of vectors of Node pointers
    vector<T*> traversalStack;
    vector< std::vector<T*> > rows;
    if(!m_size) return displayRows();
    T tmp = 0;
    T* p = m_data;
    const int maxDepth = getHeight(m_size-1);
    rows.resize(maxDepth);
    int depth = 0;
    int index = 0;
    for(;;) {
        index = (p - m_data);
        // Max-depth Nodes are always a leaf or null
        // This special case blocks deeper traversal
        if(depth == maxDepth - 1)  {

            if (index < m_size)
                rows[depth].push_back(p);
            else
                rows[depth].push_back(nullptr);

            p = m_data + getParent(index);
            if(depth == 0) break;
            --depth;
            continue;
        }

        // First visit to node?  Go to left child.
        if(traversalStack.size() == depth) {
            rows[depth].push_back(p);
            traversalStack.push_back(p);
            if(index >= 0 && index < m_size)
                p = m_data + getLeftChild(index);
            ++depth;
            continue;
        }

        // Odd child count? Go to right child.
        if(rows[depth+1].size() % 2) {
            p = traversalStack.back();
            if(index >= 0 && index < m_size)
                p = m_data + getRightChild((index));
            ++depth;
            continue;
        }

        // Time to leave if we get here

        // Exit loop if this is the root
        if(depth == 0) break;

        traversalStack.pop_back();
        p = traversalStack.back();
        --depth;
    }

    // Use rows of Node pointers to populate rows of cell_display structs.
    // All possible slots in the tree get a cell_display struct,
    // so if there is no actual Node at a struct's location,
    // its boolean "present" field is set to false.
    // The struct also contains a string representation of
    // its Node's value, created using a std::stringstream object.
    displayRows rowsDisp;
    std::stringstream ss;
    for(const auto& row : rows) {
        rowsDisp.emplace_back();
        for(T* pn : row) {
            if(pn) {
                ss << *pn;
                rowsDisp.back().push_back(cellDisplay(ss.str()));
                ss = std::stringstream();
            } else {
                rowsDisp.back().push_back(cellDisplay());
            }   }   }
    return rowsDisp;
}

template <typename T>
vector<string> Heap<T>::rowFormatter(const displayRows& rowsDisp) const {
    using s_t = string::size_type;

    // First searchItem the maximum value string length and put it in cellWidth
    s_t cellWidth = 0;
    for(const auto& rowDisp : rowsDisp) {
        for(const auto& cd : rowDisp) {
            if(cd.present && cd.valstr.length() > cellWidth) {
                cellWidth = cd.valstr.length();
            }   }   }

    // make sure the cellWidth is an odd number
    if(cellWidth % 2 == 0) ++cellWidth;

    // formatted_rows will hold the results
    vector<string> formatted_rows;

    // some of these counting variables are related,
    // so its should be possible to eliminate some of them.
    s_t row_count = rowsDisp.size();

    // this row's element count, a power of two
    s_t row_elem_count = 1 << (row_count-1);

    // left_pad holds the number of space charactes at the beginning of the bottom row
    s_t left_pad = 0;

    // Work from the level of maximum depth, up to the root
    // ("formatted_rows" will need to be reversed when done)
    for(s_t r=0; r<row_count; ++r) {
        const auto& cd_row = rowsDisp[row_count - r - 1]; // r reverse-indexes the row
        // "space" will be the number of rows of slashes needed to get
        // from this row to the next.  It is also used to determine other
        // text offsets.
        s_t space = (s_t(1) << r) * (cellWidth + 1) / 2 - 1;
        // "row" holds the line of text currently being assembled
        string row;
        // iterate over each element in this row
        for(s_t c=0; c<row_elem_count; ++c) {
            // add padding, more when this is not the leftmost element
            row += string(c ? left_pad*2+1 : left_pad, ' ');
            if(cd_row[c].present) {
                // This position corresponds to an existing Node
                const string& valstr = cd_row[c].valstr;
                // Try to pad the left and right sides of the value string
                // with the same number of spaces.  If padding requires an
                // odd number of spaces, right-sided children get the longer
                // padding on the right side, while left-sided children
                // get it on the left side.
                s_t long_padding = cellWidth - valstr.length();
                s_t short_padding = long_padding / 2;
                long_padding -= short_padding;
                row += string(c%2 ? short_padding : long_padding, ' ');
                row += valstr;
                row += string(c%2 ? long_padding : short_padding, ' ');
            } else {
                // This position is empty, Nodeless...
                row += string(cellWidth, ' ');
            }
        }
        // A row of spaced-apart value strings is ready, add it to the result vector
        formatted_rows.push_back(row);

        // The root has been added, so this loop is finsished
        if(row_elem_count == 1) break;

        // Add rows of forward- and back- slash characters, spaced apart
        // to "connect" two rows' Node value strings.
        // The "space" variable counts the number of rows needed here.
        s_t left_space  = space + 1;
        s_t right_space = space - 1;
        for(s_t sr=0; sr<space; ++sr) {
            string row;
            for(s_t c=0; c<row_elem_count; ++c) {
                if(c % 2 == 0) {
                    row += string(c ? left_space*2 + 1 : left_space, ' ');
                    row += cd_row[c].present ? '/' : ' ';
                    row += string(right_space + 1, ' ');
                } else {
                    row += string(right_space, ' ');
                    row += cd_row[c].present ? '\\' : ' ';
                }
            }
            formatted_rows.push_back(row);
            ++left_space;
            --right_space;
        }
        left_pad += space + 1;
        row_elem_count /= 2;
    }

    // Reverse the result, placing the root node at the beginning (top)
    std::reverse(formatted_rows.begin(), formatted_rows.end());

    return formatted_rows;
}

template <typename T>
void Heap<T>::trimRowsLeft(vector<string>& rows) {
    if(!rows.size()) return;
    auto min_space = rows.front().length();
    for(const auto& row : rows) {
        auto i = row.find_first_not_of(' ');
        if(i==string::npos) i = row.length();
        if(i == 0) return;
        if(i < min_space) min_space = i;
    }
    for(auto& row : rows) {
        row.erase(0, min_space);
    }   }

template <typename T>
std::ostream& Heap<T>::Dump(std::ostream& out) const {
    const int d = getHeight(m_size-1);

    // If this tree is empty, tell someone
    if(d == 0) {
        out << " <empty tree>\n";
        return out;
    }

    // This tree is not empty, so get a list of node values...
    const auto rowsDisp = getRowDisplay();
    // then format these into a text representation...
    auto formattedRows = rowFormatter(rowsDisp);
    // then trim excess space characters from the left sides of the text...
    trimRowsLeft(formattedRows);
    // then dump the text to cout.
    for(const auto& row : formattedRows) {
        out << ' ' << row << '\n';

    }
    return out;
}

//
//          OPERATOR OVERLOADING
//

template <typename T>
std::ostream& operator<< (std::ostream& out, Heap<T>& tree) {
//    tree.preOrderTravers(&(tree.getRoot()), [&out](T item){
//        out << item << " ";
//    });
    return tree.Dump(out);
}