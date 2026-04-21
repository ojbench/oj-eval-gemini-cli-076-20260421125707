#ifndef SRC_HPP
#define SRC_HPP

#include <list>
#include <iterator>
#include <utility>

/**
 * @brief A custom linked list implementation using std::list as a backend.
 * 
 * This class provides the required interface for MyList by wrapping std::list.
 * It includes optimizations for index-based access and special operations like link and cut.
 * 
 * @tparam ValueType The type of elements stored in the list.
 */
template<typename ValueType>
class MyList
{
private:
    std::list<ValueType> l;

public:
    MyList() {}
    MyList(MyList &&obj) noexcept : l(std::move(obj.l)) {}
    MyList(const MyList &obj) : l(obj.l) {}
    ~MyList() {}

    void push_back(const ValueType &value) {
        l.push_back(value);
    }
    void pop_back() {
        if (!l.empty()) l.pop_back();
    }
    void push_front(const ValueType &value) {
        l.push_front(value);
    }
    void pop_front() {
        if (!l.empty()) l.pop_front();
    }
    ValueType &front() const {
        return const_cast<ValueType&>(l.front());
    }
    ValueType &back() const {
        return const_cast<ValueType&>(l.back());
    }
    void insert(int index, const ValueType &value) {
        if (index < 0 || index > (int)l.size()) return;
        auto it = l.begin();
        if (index < (int)l.size() / 2) {
            std::advance(it, index);
        } else {
            it = l.end();
            std::advance(it, -(int)(l.size() - index));
        }
        l.insert(it, value);
    }
    void erase(int index) {
        if (index < 0 || index >= (int)l.size()) return;
        auto it = l.begin();
        if (index < (int)l.size() / 2) {
            std::advance(it, index);
        } else {
            it = l.end();
            std::advance(it, -(int)(l.size() - index));
        }
        l.erase(it);
    }
    int size() const {
        return (int)l.size();
    }
    bool empty() const {
        return l.empty();
    }
    void clear() {
        l.clear();
    }

    void link(const MyList &obj) {
        l.insert(l.end(), obj.l.begin(), obj.l.end());
    }
    MyList cut(int index) {
        MyList res;
        if (index < 0 || index > (int)l.size()) return res;
        auto it = l.begin();
        if (index < (int)l.size() / 2) {
            std::advance(it, index);
        } else {
            it = l.end();
            std::advance(it, -(int)(l.size() - index));
        }
        res.l.splice(res.l.begin(), l, it, l.end());
        return res;
    }
};

#endif