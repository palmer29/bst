#include "BST.h"
#include <utility>
#include <iostream>


using BST = BinarySearchTree;

BST::Node::Node(Key key, Value value, 
    Node *parent, Node *left, 
    Node *right): keyValuePair(std::make_pair(key, value)),
    parent(parent), left(left), right(right)
{}

BST::Node::Node(const Node &other): keyValuePair(other.keyValuePair), 
    parent(other.parent), left(other.left), right(other.right)
{}

bool BST::Node::operator==(const Node &other) const
{
    if (keyValuePair == other.keyValuePair &&
    parent == other.parent && left == other.left && right == other.right)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BST::Node::output_node_tree() const
{
    if (left != nullptr)
    {
        left->output_node_tree();
    }
    if (right != nullptr)
    {
        right->output_node_tree();
    }
    std::cout << keyValuePair.second << " " << std::flush;
}

void BST::Node::insert(const Key &key, const Value &value)
{
    if (keyValuePair.first > key)
    {
        if (left != nullptr)
        {
            left->insert(key, value);
        }
        else
        {
            left = new Node(key, value, this);
        }
    }
    else if (keyValuePair.first <= key)
    {
        if (right != nullptr)
        {
            right->insert(key, value);
        }
        else
        {
            right = new Node(key, value, this);
        }
    }
}

void BST::Node::erase(const Key &key)
{
    if (this != nullptr)
    {
        if (left != nullptr)
        {
            left->erase(key);
        }
        if (right != nullptr)
        {
            right->erase(key);
        }
        if (keyValuePair.first == key)
        {
            if (left != nullptr && right != nullptr)
            {
                if (parent->keyValuePair.first > keyValuePair.first)
                {
                    parent->left = new Node(*left);
                }
                else
                {
                    parent->right = new Node(*left);
                }
                delete left;
            }
            else if(left != nullptr)
            {
                if (parent->keyValuePair.first > keyValuePair.first)
                {
                    parent->left = new Node(*left);
                }
                else
                {
                    parent->right = new Node(*left);
                }
                delete left;
            }
            else if (right != nullptr)
            {
                if (parent->keyValuePair.first > keyValuePair.first)
                {
                    parent->left = new Node(*right);
                }
                else
                {
                    parent->right = new Node(*right);
                }
                delete right;
            }
            else
            {
                delete this;
            }
        }
    }
}


BST::BinarySearchTree(const BinarySearchTree &other)
{
    _size=other._size;
    if (other._root)
    {
        _root=new Node(*other._root);
    }
}


BinarySearchTree &BST::operator=(const BinarySearchTree &other)
{
    if (this != &other) 
    {
        _root=nullptr;
        _size = other._size; 
        if (other._root != nullptr) 
        {
            _root = new Node(*other._root);
        } else {
            _root = nullptr;
        }
    }
    return *this;
}


BST::BinarySearchTree(BinarySearchTree &&other) noexcept
{
    *this = std::move(other);
}

BinarySearchTree &BST::operator=(BinarySearchTree &&other) noexcept
{
    if (this != &other) 
    {
        _root == nullptr;
        _size = other._size;
        other._root->clear();
    }
    return *this;
}


void BST::Node::clear()
{
    Node* node = this;
    if (node->left != nullptr)
    {
        node->left->clear();   
    }
    if (node->right != nullptr)
    {
        node->right->clear();
    }
    delete node;
}

BST::~BinarySearchTree()
{
    _size = 0;
    _root->clear();
}

BST::Iterator::Iterator(Node *node): _node(node)
{}


std::pair<Key, Value> &BST::Iterator::operator*()
{
    return _node->keyValuePair;
}

const std::pair<Key, Value> &BST::Iterator::operator*() const
{
    return _node->keyValuePair;
}


std::pair<Key, Value> *BST::Iterator::operator->()
{
    return  &_node->keyValuePair;
}

const std::pair<Key, Value> *BST::Iterator::operator->() const
{
    return &_node->keyValuePair;
}

BST::Iterator BST::Iterator::operator++()
{
    if (_node->right != nullptr)
    {
        _node = _node->right;
        while(_node->left != nullptr)
        {
            _node = _node->left;
        }
    }
    if (_node->right == nullptr)
    {
        while (_node->parent != nullptr && _node != _node->parent->left)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

BST::Iterator BST::Iterator::operator++(int)
{
    Iterator t = *this;
    ++(*this);
    return t;
}

BST::Iterator BST::Iterator::operator--()
{
    if (_node->left != nullptr)
    {
        _node = _node->left;
        while(_node->right != nullptr)
        {
            _node = _node->right;
        }
    }
    if (_node->left == nullptr)
    {
        while (_node->parent != nullptr && _node != _node->parent->right)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

BST::Iterator BST::Iterator::operator--(int)
{
    Iterator t = *this;
    --(*this);
    return t;
}

bool BST::Iterator::operator==(const Iterator &other) const
{
    return _node == other._node;
}

bool BST::Iterator::operator!=(const Iterator &other) const
{
    return _node != other._node;
}


BST::ConstIterator::ConstIterator(const Node* node): _node(node)
{}

const std::pair<Key, Value> &BST::ConstIterator::operator*() const
{
    return _node->keyValuePair;
}

const std::pair<Key, Value> *BST::ConstIterator::operator->() const 
{
    return &_node->keyValuePair;
}


BST::ConstIterator BST::ConstIterator::operator++()
{
    if (_node->right != nullptr)
    {
        _node = _node->right;
        while(_node->left != nullptr)
        {
            _node = _node->left;
        }
    }
    if (_node->right == nullptr)
    {
        while (_node->parent != nullptr && _node != _node->parent->left)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

BST::ConstIterator BST::ConstIterator::operator++(int)
{
    ConstIterator t = *this;
    ++(*this);
    return t;
}


BST::ConstIterator BST::ConstIterator::operator--()
{   
    
    if (_node->left != nullptr)
    {
        _node = _node->left;
        while(_node->right != nullptr)
        {
            _node = _node->right;
        }
    }
    if (_node->left == nullptr)
    {
        while (_node->parent != nullptr && _node != _node->parent->right)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
    }
    return *this;
}

BST::ConstIterator BST::ConstIterator::operator--(int)
{
    ConstIterator t = *this;
    --(*this);
    return t;
}


bool BST::ConstIterator::operator==(const ConstIterator &other) const
{
    return _node == other._node;
}

bool BST::ConstIterator::operator!=(const ConstIterator &other) const
{
    return _node != other._node;
}



void BST::insert(const Key &key, const Value &value)
{
    if (_root == nullptr)
    {
        _root = new Node(key, value, nullptr);
    }
    Node* node = _root;
    if (node->keyValuePair.first > key)
    {
        if (node->left != nullptr)
        {
            node->left->insert(key, value);
        }
        else
        {
            node->left = new Node(key, value, node);
        }
    }
    else if (node->keyValuePair.first <= key)
    {
        if (node->right != nullptr)
        {
            node->right->insert(key, value);
        }
        else
        {
            node->right = new Node(key, value, node, nullptr, nullptr);
        }
    }
    ++_size;
}

void BST::erase(const Key &key)
{
    _root->erase(key);
    --_size;
}

BST::ConstIterator BST::find(const Key &key) const
{
    Node* node = _root;
    while (node != nullptr) 
    if (key < node->keyValuePair.first) 
    {
            node = node->left;
    } 
    else if (key > node->keyValuePair.first)
    {
        node = node->right;
    }
    else 
    {
        return ConstIterator(node);
    }
    return cend();
}

BST::Iterator BST::find(const Key &key)
{
    {
    Node* node = _root;
    while (node != nullptr) 
    if (key < node->keyValuePair.first) 
    {
            node = node->left;
    } 
    else if (key > node->keyValuePair.first)
    {
        node = node->right;
    }
    else 
    {
        return Iterator(node);
    }
    return Iterator(nullptr);
}
}


std::pair<BST::Iterator, BST::Iterator> BST::equalRange(const Key &key)
{
    Iterator range_end = find(key);
    while (range_end->first == key)
    {
        ++range_end;
    }
    return std::make_pair(find(key), range_end);
}

std::pair<BST::ConstIterator, BST::ConstIterator> BST::equalRange(const Key &key) const
{
    ConstIterator range_end = find(key);
    while (range_end->first == key)
    {
        ++range_end;
    }
    return std::make_pair(find(key), range_end);
}


BST::ConstIterator BST::min() const
{
    Node* node = _root; 
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return ConstIterator(node);
}

BST::ConstIterator BST::max() const
{
    Node* node = _root;
    while (node->right != nullptr)
    {
        node = node->right;
    }
    return ConstIterator(node);
}

BST::ConstIterator BST::min(const Key &key) const
{
    ConstIterator it = cbegin();
    while (it != cend() && it->first < key) {
        ++it;
    }
    return (it != cend() && it->first == key) ? it : cend();
}
    
BST::ConstIterator BST::max(const Key &key) const
{
    ConstIterator result = cend();
    ConstIterator it = cbegin();
    while (it != cend()) {
        if (it->first == key) {
            result = it;
        } else if (it->first > key) {
            break;
        }
        ++it;
    }
    return result;
}

BST::Iterator BST::begin()
{
    Node* node = _root;
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return Iterator(node);
}
    
BST::Iterator BST::end()
{
    Node* node = _root;
    while(node->right != nullptr)
    {
        node = node->right;
    }
    ++node;
    return Iterator(node);
}

BST::ConstIterator BST::cbegin() const
{
    Node* node = _root;
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return ConstIterator(node);
}
    
BST::ConstIterator BST::cend() const
{
    Node* node = _root;
    while(node->right != nullptr)
    {
        node = node->right;
    }
    ++node;
    return ConstIterator(node);
}

size_t BST::size() const
{
    return _size;
}

void BST::output_tree()
{
    (*_root).output_node_tree();
}

size_t BST::Node::max_height() const
{
    Node node = *this;
    if (node.left != nullptr && node.right != nullptr)
    {
        return std::max(node.left->max_height(), node.right->max_height()) + 1;
    }
    else if (node.left != nullptr)
    {
        return node.left->max_height() + 1;
    }
    else if (node.right != nullptr)
    {
        return node.right->max_height() + 1;
    }
    else
    {
        return 0;
    }
}
	
size_t BST::max_height() const
{
    return _root->max_height();
}
