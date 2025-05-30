#pragma once

#include <utility>
#include <cstdint>
#include <string>

using Key = uint32_t; //!< тип ключей в дереве
using Value = double; //!< тип значений в дереве

//! Имплементация бинарного дерева поиска
class BinarySearchTree 
{
    struct Node 
    {
        //! Конструктор с параметрами
        //! \param key - ключ
        //! \param value - значение
        //! \param parent - родительский узел
        //! \param left - левый дочерний узел
        //! \param right - правый дочерний узел
        Node(Key key, Value value, 
             Node *parent = nullptr, Node *left = nullptr, 
             Node *right = nullptr);

        //! Конструктор копирования
        Node(const Node &other);
        //! Оператор сравнения ==
        bool operator==(const Node &other) const;

        //! Вывод в консоль поддерева, где текущий узел - корень
        void output_node_tree() const;
        //! Вставить новый узел в поддерево, где текущий узел - корень
        void insert(const Key &key, const Value &value);
        //! Удалить узел из поддерева, где текущий узел - корень
        void erase(const Key &key);
        size_t max_height() const;
        void clear();
        std::pair<Key, Value> keyValuePair; //!< Пара ключ - значение
        Node *parent = nullptr; //!< родительский узел
        Node *left = nullptr;   //!< левый потомок
        Node *right = nullptr;  //!< правый потомок
    };

public:
    //! Конструктор по умолчанию
    BinarySearchTree() = default;
    //! Конструктор копирования
    explicit BinarySearchTree(const BinarySearchTree &other);
    //! Оператор присваивания копированием
    BinarySearchTree &operator=(const BinarySearchTree &other);
    //! Конструктор перемещения
    explicit BinarySearchTree(BinarySearchTree &&other) noexcept;
    //! Оператор присваивания перемещением
    BinarySearchTree &operator=(BinarySearchTree &&other) noexcept;
    //! Деструктор
    ~BinarySearchTree();

    //! \brief Итератор бинарного дерева поиска
    //! \note Обходит дерево последовательно от узла с меньшим ключом к узлу с большим 
    class Iterator  
    {
    public:
        explicit Iterator(Node *node);

        std::pair<Key, Value> &operator*();
        const std::pair<Key, Value> &operator*() const;

        std::pair<Key, Value> *operator->();
        const std::pair<Key, Value> *operator->() const;

        Iterator operator++();
        Iterator operator++(int);

        Iterator operator--();
        Iterator operator--(int);

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

    private:
        Node *_node;
    };

    //! Константный итератор бинарного дерева поиска
    class ConstIterator 
    {
    public:
        explicit ConstIterator(const Node *node);

        const std::pair<Key, Value> &operator*() const;
        const std::pair<Key, Value> *operator->() const;

        ConstIterator operator++();
        ConstIterator operator++(int);

        ConstIterator operator--();
        ConstIterator operator--(int);

        bool operator==(const ConstIterator &other) const;
        bool operator!=(const ConstIterator &other) const;

    private:
        const Node *_node;
    };

    //! Вставить элемент с ключем key и значением value
    void insert(const Key &key, const Value &value);
    //! Удалить все элементы с ключем key
    void erase(const Key &key);
    //! Найти первый элемент в дереве, равный ключу key
    ConstIterator find(const Key &key) const;
    //! Найти первый элемент в дереве, равный ключу key
    Iterator find(const Key &key);
    /*!***********************************************************
    Найти все элементы, у которых ключ равен key:
      - первый итератор пары - первый элемент в дереве, равный key
      - второй итератор пары - первый элемент в дереве больший, чем key
     
    [pair.first, pair.second) - полуинтервал, содержащий все 
    элементы с ключем key
    **************************************************************/
    std::pair<Iterator, Iterator> equalRange(const Key &key);
    std::pair<ConstIterator, ConstIterator> equalRange(const Key &key) const;
    
    //! Получить итератор на элемент с наименьшим ключем в дереве
    ConstIterator min() const;
    //! Получить итератор на элемент с наибольшим ключем в дереве
    ConstIterator max() const;
    //! Получить итератор на элемент с ключем key с наименьшим значением 
    ConstIterator min(const Key &key) const;
    //! Получить итератор на элемент с ключем key с наибольшим значением
    ConstIterator max(const Key &key) const;

    //! Получить итератор на первый элемент дерева (элемент с наименьшим key)
    Iterator begin();
    //! Получить итератор на элемент, следующий за последним элементом дерева
    //! \note Т.е. tree.end()-- == tree.max()
    Iterator end();

    //! Получить константный итератор на начало
    ConstIterator cbegin() const;
    //! Получить константный итератор на конец
    ConstIterator cend() const;

    //! Получить размер дерева
    size_t size() const;
    //! Вывести дерево в консоль
    void output_tree();
	//! Получить максимальную высоту в дереве
	size_t max_height() const;

private:
    size_t _size = 0; //!< размер дерева
    Node *_root = nullptr; //!< корневой узел дерева
};
