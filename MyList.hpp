#ifndef MYLIST_HPP
#define MYLIST_HPP

template<typename ValueType>
class MyList
{
private:
    struct Node {
        ValueType value;
        Node *prev;
        Node *next;
        Node(const ValueType &v, Node *p = nullptr, Node *n = nullptr)
            : value(v), prev(p), next(n) {}
    };

    Node *head;
    Node *tail;
    int _size;

public:
    MyList() : head(nullptr), tail(nullptr), _size(0) {}

    MyList(MyList &&obj) noexcept : head(obj.head), tail(obj.tail), _size(obj._size) {
        obj.head = nullptr;
        obj.tail = nullptr;
        obj._size = 0;
    }

    MyList(const MyList &obj) : head(nullptr), tail(nullptr), _size(0) {
        Node *curr = obj.head;
        while (curr) {
            push_back(curr->value);
            curr = curr->next;
        }
    }

    ~MyList() {
        clear();
    }

    void push_back(const ValueType &value) {
        Node *newNode = new Node(value, tail, nullptr);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        _size++;
    }

    void pop_back() {
        if (empty()) return;
        Node *temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        _size--;
    }

    void push_front(const ValueType &value) {
        Node *newNode = new Node(value, nullptr, head);
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        _size++;
    }

    void pop_front() {
        if (empty()) return;
        Node *temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        _size--;
    }

    ValueType &front() const {
        return head->value;
    }

    ValueType &back() const {
        return tail->value;
    }

    void insert(int index, const ValueType &value) {
        if (index < 0 || index > _size) return;
        if (index == 0) {
            push_front(value);
        } else if (index == _size) {
            push_back(value);
        } else {
            Node *curr = head;
            for (int i = 0; i < index; ++i) {
                curr = curr->next;
            }
            Node *newNode = new Node(value, curr->prev, curr);
            curr->prev->next = newNode;
            curr->prev = newNode;
            _size++;
        }
    }

    void erase(int index) {
        if (index < 0 || index >= _size) return;
        if (index == 0) {
            pop_front();
        } else if (index == _size - 1) {
            pop_back();
        } else {
            Node *curr = head;
            for (int i = 0; i < index; ++i) {
                curr = curr->next;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            _size--;
        }
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void link(const MyList &obj) {
        Node *curr = obj.head;
        while (curr) {
            push_back(curr->value);
            curr = curr->next;
        }
    }

    MyList cut(int index) {
        if (index < 0 || index > _size) return MyList();
        if (index == _size) {
            return MyList();
        }
        
        MyList res;
        if (index == 0) {
            res.head = head;
            res.tail = tail;
            res._size = _size;
            head = nullptr;
            tail = nullptr;
            _size = 0;
        } else {
            Node *curr = head;
            for (int i = 0; i < index; ++i) {
                curr = curr->next;
            }
            
            res.head = curr;
            res.tail = tail;
            res._size = _size - index;
            
            tail = curr->prev;
            tail->next = nullptr;
            curr->prev = nullptr;
            _size = index;
        }
        return res;
    }
};

#endif
