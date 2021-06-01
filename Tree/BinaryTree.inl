//
//      NODE STRUCT FROM BINARY TREE
//

template <typename T>
BinaryTree<T>::M_Node::M_Node() : parent(nullptr), leftChild(nullptr), rightChild(nullptr), data(1) {};
template <typename T>
BinaryTree<T>::M_Node::M_Node(M_Node* parent, const T& data) : data(data), parent(parent), leftChild(nullptr), rightChild(nullptr) {};
template <typename T>
BinaryTree<T>::M_Node::~M_Node() {delete leftChild; delete rightChild;};
template <typename T>
int BinaryTree<T>::M_Node::maxDepth() const {
    const int left_depth = leftChild ? leftChild->maxDepth() : 0;
    const int right_depth = rightChild ? rightChild->maxDepth() : 0;
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}


//
//      BINARY TREE
//


template <typename T>
BinaryTree<T>::BinaryTree() : m_root(nullptr) {};

template <typename T>
BinaryTree<T>::BinaryTree(T item) : BinaryTree() {
    insert(item);
}

template <typename T>
BinaryTree<T>::BinaryTree(T* items, int count) : BinaryTree() {
    for (int i = 0; i < count; i++)
        insert(items[i]);
}

template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T>& another) {
    preOrderTravers(another.m_root, [this](T item) {
        this->insert(item);
    });
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    delete m_root;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::insert(T& item) {
    if (!m_root) {
        m_root = new BinaryTree::M_Node(nullptr, item);
    } else {
        insert(m_root, nullptr, item);
    }
    // is Balanced
    return *this;
}

template <typename T>
typename BinaryTree<T>::M_Node* BinaryTree<T>::insert(M_Node* node, M_Node* parent, T& item) {
    if (!node)
        return new M_Node(parent, item);

    if (item < node->data)
        node->leftChild = insert(node->leftChild, node, item);
    else if (item > node->data)
        node->rightChild = insert(node->rightChild, node, item);
    else
        throw(Exceptions(ExceptionConsts::ITEM_EXISTS));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && item < node->rightChild->data) {
        node->rightChild = rightRotate(node->rightChild);
        return leftRotate(node);
    }

    // Right Right Case
    if (balance < -1 && item > node->leftChild->data) {
        node->leftChild = leftRotate(node->leftChild);
        return rightRotate(node);
    }

    // Left Right Case
    if (balance > 1 && item > node->rightChild->data)
    {
//        node->rightChild = leftRotate(node->rightChild);
        return leftRotate(node);
    }

    // Right Left Case
    if (balance < -1 && item < node->leftChild->data)
    {
//        node->leftChild = rightRotate(node->leftChild);
        return rightRotate(node);
    }

    return node;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::insert(T&& item) {
    T tmp = item;
    insert(tmp);
    return *this;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::remove(T& item) { // If element wasn't found
//    M_Node* node = getNode(item);
//    if (!node)
//        return nullptr;
    removeNode(m_root, item);
    return this;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::remove(T&& item) { // If element wasn't found
    return remove(item);
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::map(T (*function)(const T& item)) {
    BinaryTree<T>* result = new BinaryTree;
    preOrderTravers(m_root, [result, function](T item){
        result->insert(function(item));
    });
    return result;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::filter(bool (*function)(const T& item)) {
    BinaryTree<T>* result = new BinaryTree;
    preOrderTravers(m_root, [result, function](T item){
        if (function(item))
            result->insert(item);
    });
    return result;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::cut(T& item) {
    M_Node* node = getNode(item);
    if (node == nullptr)
        return nullptr;
    BinaryTree<T>* result = new BinaryTree<T>;
    preOrderTravers(node, [&result](T item){
        result->insert(item);
    });

    return result;
}

template <typename T>
typename BinaryTree<T>::M_Node* BinaryTree<T>::getNode(T& item) {
    M_Node* root = m_root;
    while(root) {
        if (root->data > item) {
            root = root->leftChild;
            continue;
        } else if (root->data < item) {
            root = root->rightChild;
            continue;
        } else {
            return root;
        }
    }
    return nullptr;
}

template <typename T>
bool BinaryTree<T>::searchItem(T& item) {
    if (getNode(item))
        return true;
    else
        return false;
}

template <typename T>
bool BinaryTree<T>::searchItem(T&& item) {
    return searchItem(item);
}

template <typename T>
bool BinaryTree<T>::searchTree(BinaryTree<T>& source) {
    return searchTreeDev(this->m_root, source.m_root);
}

template <typename T>
bool BinaryTree<T>::searchTreeDev(M_Node* destinationRoot, M_Node* sourceRoot) {
    bool result;
    if (sourceRoot == nullptr) {
        return true;
    }
    else if ((destinationRoot == nullptr)) {
        return false;
    }
    else {
        if (destinationRoot->data == sourceRoot->data) {
            if (
                    searchTreeDev(destinationRoot->leftChild, sourceRoot->leftChild) &&
                    searchTreeDev(destinationRoot->rightChild, sourceRoot->rightChild))
            {
                return true;
            }
        }
        result = searchTreeDev(destinationRoot->leftChild, sourceRoot) ||
                 searchTreeDev(destinationRoot->rightChild, sourceRoot);
    }
    return result;
}


template <typename T>
T BinaryTree<T>::reduce(T (*function)(const T& previousValue, const T& currentValue)) {
    T result;
    bool flag = false;

    preOrderTravers(m_root, [&result, &flag, function](T item){
        if(flag) {
            result = function(result, item);
        } else {
            result = item;
            flag = true;
        }
    });

    return result;
}

template <typename T>
const typename BinaryTree<T>::M_Node& BinaryTree<T>::getRoot() {
    return *m_root;
}

template <typename T>
typename BinaryTree<T>::M_Node* BinaryTree<T>::minValueNode(M_Node* node) {
    M_Node* current = node;
    while (current->leftChild != nullptr)
        current = current->leftChild;

    return current;
}

template <typename T>
int BinaryTree<T>::getMaxDepth() const {
    return m_root ? m_root->maxDepth() : 0;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::writeToFile(std::string& path) {
    std::ofstream wf(path, std::ios::out | std::ios::binary);
    if(!wf) {
        std::cout << "Cannot open file!" << std::endl; // throw exc
        return nullptr;
    }
    preOrderTravers(m_root, [&wf](T item){
        std::cout << item << std::endl; // trow exc
        wf.write((char *)& item, sizeof(T));
    });
    wf.close();
    if(!wf.good()) {
        std::cout << "Error occurred at writing time!" << std::endl; // trow exc
        return nullptr;
    }
    return this;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::writeToFile(std::string&& path) {
    return writeToFile(path);
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::insertFromFile(std::string& path) {
    std::ifstream rf(path, std::ios::out | std::ios::binary);
    if(!rf) {
        std::cout << "Cannot open file!" << std::endl;
        return nullptr;
    }

    rf.seekg(0, rf.end); // or rf.end
    int length = rf.tellg();
    rf.seekg(0, rf.beg);

    T* tmp = new T;


    while (length > 0) {
        rf.read((char *) tmp, sizeof(T));
        std::cout << *tmp << std::endl;
        insert(*tmp);
        length -= sizeof(T);
    }
    delete tmp;


    rf.close();
    if(!rf.good()) {
        std::cout << "Error occurred at reading time!" << std::endl;
        return nullptr;
    }
    return this;
}



template <typename T>
BinaryTree<T>* BinaryTree<T>::insertFromFile(std::string&& path) {
    return insertFromFile(path);
}


//
//          PRIVATE
//

template <typename T>
typename BinaryTree<T>::M_Node* BinaryTree<T>::removeNode(M_Node* target, T& item) {
    if (target == nullptr)
        return target;

    if ( item < target->data )
        target->leftChild = removeNode(target->leftChild, item);
    else if( item > target->data )
        target->rightChild = removeNode(target->rightChild, item);
    else
    {
        if( (target->leftChild == nullptr) ||
            (target->rightChild == nullptr) )
        {
            M_Node *temp = target->leftChild ?
                         target->leftChild :
                         target->rightChild;

            if (temp == nullptr)
            {
                temp = target;
                target = nullptr;
            }
            else {
                *target = *temp;
                target->leftChild = target->rightChild = nullptr;
                delete target;
            }
        }
        else
        {
            M_Node* temp = minValueNode(target->rightChild);
            target->data = temp->data;
            target->rightChild = removeNode(target->rightChild,
                                     temp->data);
        }
    }
    if (target == nullptr)
        return target;
    int balance = getBalance(target);

    // Left Left Case
    if (balance > 1 && item < target->rightChild->data) {
        target->rightChild = rightRotate(target->rightChild);
        return leftRotate(target);
    }

    // Right Right Case
    if (balance < -1 && item > target->leftChild->data) {
        target->leftChild = leftRotate(target->leftChild);
        return rightRotate(target);
    }

    // Left Right Case
    if (balance > 1 && item > target->rightChild->data)
    {
        return leftRotate(target);
    }

    // Right Left Case
    if (balance < -1 && item < target->leftChild->data)
    {
        return rightRotate(target);
    }

    return target;
}

template <typename T>
typename BinaryTree<T>::M_Node* BinaryTree<T>::getLocalMax(M_Node* root) {
    M_Node* tmp = root;
    while(tmp->rightChild)
        tmp = tmp->rightChild;
    return tmp;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::preOrderTravers(const M_Node* nodeRoot, std::function<void(T)> func) {
    if (nodeRoot) {
        func(nodeRoot->data);
        preOrderTravers(nodeRoot->leftChild, func);
        preOrderTravers(nodeRoot->rightChild, func);
    }
    return *this;
}

template <typename T>
typename BinaryTree<T>::M_Node* BinaryTree<T>::leftRotate(M_Node* x) {
    if (x->parent == nullptr)
        m_root = x->rightChild;
    x->rightChild->parent = x->parent;
    x->parent = x->rightChild;
    x->rightChild = x->rightChild->leftChild;
    x->parent->leftChild = x;
    return x->parent;
}

template <typename T>
typename BinaryTree<T>::M_Node* BinaryTree<T>::rightRotate(M_Node* y) {
    if (y->parent == nullptr)
        m_root = y->leftChild;
    y->leftChild->parent = y->parent;
    y->parent = y->leftChild;
    y->leftChild = y->leftChild->rightChild;
    y->parent->rightChild = y;

    return y->parent;
}

template <typename T>
int BinaryTree<T>::getBalance(M_Node* node) {
    if (node == nullptr)
        return 0;
    if (!node->rightChild && !node->leftChild)
        return 0;
    if (!node->rightChild)
        return - node->leftChild->maxDepth();
    if (!node->leftChild)
        return node->rightChild->maxDepth();
    return node->rightChild->maxDepth() - node->leftChild->maxDepth();
}

//
//          OPERATOR OVERLOADING
//

template <typename T>
std::ostream& operator<< (std::ostream& out, BinaryTree<T>& tree) {
//    tree.preOrderTravers(&(tree.getRoot()), [&out](T item){
//        out << item << " ";
//    });
    return tree.Dump(out);
}



//
//          OUTPUT
//


template <typename T>
typename BinaryTree<T>::displayRows BinaryTree<T>::getRowDisplay() const {
    // start off by traversing the tree to
    // build a vector of vectors of Node pointers
    vector<M_Node*> traversalStack;
    vector< std::vector<M_Node*> > rows;
    if(!m_root) return displayRows();

    M_Node* p = m_root;
    const int maxDepth = m_root->maxDepth();
    rows.resize(maxDepth);
    int depth = 0;
    for(;;) {
        // Max-depth Nodes are always a leaf or null
        // This special case blocks deeper traversal
        if(depth == maxDepth - 1) {
            rows[depth].push_back(p);
            if(depth == 0) break;
            --depth;
            continue;
        }

        // First visit to node?  Go to left child.
        if(traversalStack.size() == depth) {
            rows[depth].push_back(p);
            traversalStack.push_back(p);
            if(p) p = p->leftChild;
            ++depth;
            continue;
        }

        // Odd child count? Go to right child.
        if(rows[depth+1].size() % 2) {
            p = traversalStack.back();
            if(p) p = p->rightChild;
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
        for(M_Node* pn : row) {
            if(pn) {
                ss << pn->data;
                rowsDisp.back().push_back(cellDisplay(ss.str()));
                ss = std::stringstream();
            } else {
                rowsDisp.back().push_back(cellDisplay());
            }   }   }
    return rowsDisp;
}

template <typename T>
vector<string> BinaryTree<T>::rowFormatter(const displayRows& rowsDisp) const {
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
void BinaryTree<T>::trimRowsLeft(vector<string>& rows) {
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
std::ostream& BinaryTree<T>::Dump(std::ostream& out) const {
    const int d = getMaxDepth();

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