//
//      NODE STRUCT FROM BINARY TREE
//
template <typename T>
BinaryTree<T>::M_Node::M_Node() : parent(nullptr), leftChild(nullptr), rightChild(nullptr) {};
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
BinaryTree<T>::BinaryTree(const T& item) : BinaryTree() {
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
BinaryTree<T>& BinaryTree<T>::preOrderTravers(const M_Node* nodeRoot, std::function<void(T)> func) {
    if (nodeRoot) {
        func(nodeRoot->data);
        preOrderTravers(nodeRoot->leftChild, func);
        preOrderTravers(nodeRoot->rightChild, func);
    }
    return *this;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::insert(T& item) {
    if (!m_root) {
        m_root = new BinaryTree::M_Node(nullptr, item);
    } else {
        M_Node* tmp = m_root;
        while(tmp) {
            if (item > tmp->data) {
                if (tmp->rightChild) {
                    tmp = tmp->rightChild;
                    continue;
                } else {
                    tmp->rightChild = new BinaryTree::M_Node(tmp, item);
                    return *this;
                }
            } else if (item < tmp->data) {
                if (tmp->leftChild) {
                    tmp = tmp->leftChild;
                    continue;
                } else {
                    tmp->leftChild = new BinaryTree::M_Node(tmp, item);
                    return *this;
                }
            } else {
                throw(Exceptions(ExceptionConsts::ITEM_EXISTS));
            }
        }
    }


    return *this;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::insert(T&& item) {
    T tmp = item;
    insert(tmp);
    return *this;
}

template <typename T>
BinaryTree<T>* BinaryTree<T>::remove(int item) { // If element wasn't found
    M_Node* node = getNode(item);
    if (!node)
        return nullptr;
    removeNode(node);
    return this;
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
const typename BinaryTree<T>::M_Node& BinaryTree<T>::getRoot() {
    return *m_root;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::removeNode(M_Node* target) {
    if (target->leftChild && target->rightChild) {
        M_Node* localMax = getLocalMax(target->leftChild);

        target->data = localMax->data;
        removeNode(localMax);
        return *this;
    } else if (target->leftChild) {
        if (target == target->parent->leftChild) {
            std::cout << "ok" << std::endl;
            target->parent->leftChild = target->leftChild;
        } else {
            target->parent->rightChild = target->leftChild;
        }
    } else if (target->rightChild) {
        if (target == target->parent->leftChild) {
            target->parent->leftChild = target->rightChild;
        } else {
            target->parent->rightChild = target->rightChild;
        }
    } else {
        if (target == target->parent->leftChild) {
            target->parent->leftChild = nullptr;
        } else {
            target->parent->rightChild = nullptr;
        }
    }
    target->rightChild = target->leftChild = nullptr;
    delete target;
    return *this;
}

template <typename T>
typename BinaryTree<T>::M_Node* BinaryTree<T>::getLocalMax(M_Node* root) {
    M_Node* tmp = root;
    while(tmp->rightChild)
        tmp = tmp->rightChild;
    return tmp;
}

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

    // First find the maximum value string length and put it in cellWidth
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