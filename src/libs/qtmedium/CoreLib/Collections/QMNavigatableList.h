#ifndef QMNAVIGATABLELIST_H
#define QMNAVIGATABLELIST_H

#include <algorithm>
#include <set>

#include <QDebug>
#include <QSet>

#include "QMGlobal.h"

// Derived From stl::set
template <class _Kty, class _Pr = std::less<_Kty>, class _Alloc = std::allocator<_Kty>>
class QMCORELIB_API QNavigatableList : public std::set<_Kty, _Pr, _Alloc> {
public:
    ~QNavigatableList() = default;

public:
    using _Mybase = std::set<_Kty, _Pr, _Alloc>;
    using key_type = _Kty;
    using key_compare = _Pr;
    using value_compare = typename _Mybase::value_compare;
    using value_type = typename _Mybase::value_type;
    using allocator_type = typename _Mybase::allocator_type;
    using size_type = typename _Mybase::size_type;
    using difference_type = typename _Mybase::difference_type;
    using pointer = typename _Mybase::pointer;
    using const_pointer = typename _Mybase::const_pointer;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = typename _Mybase::iterator;
    using const_iterator = typename _Mybase::const_iterator;
    using reverse_iterator = typename _Mybase::reverse_iterator;
    using const_reverse_iterator = typename _Mybase::const_reverse_iterator;

    QNavigatableList() : _Mybase(key_compare()) {
    }

    explicit QNavigatableList(const allocator_type &_Al) : _Mybase(key_compare(), _Al) {
    }

    QNavigatableList(const _Mybase &_Right) : _Mybase(_Right) {
    }

    QNavigatableList(const _Mybase &_Right, const allocator_type &_Al) : _Mybase(_Right, _Al) {
    }

    explicit QNavigatableList(const key_compare &_Pred) : _Mybase(_Pred) {
    }

    QNavigatableList(const key_compare &_Pred, const allocator_type &_Al) : _Mybase(_Pred, _Al) {
    }

    template <class _Iter>
    QNavigatableList(_Iter _First, _Iter _Last) : _Mybase(key_compare()) {
        this->insert(_First, _Last);
    }

    template <class _Iter>
    QNavigatableList(_Iter _First, _Iter _Last, const key_compare &_Pred) : _Mybase(_Pred) {
        this->insert(_First, _Last);
    }

    template <class _Iter>
    QNavigatableList(_Iter _First, _Iter _Last, const allocator_type &_Al)
        : _Mybase(key_compare(), _Al) {
        this->insert(_First, _Last);
    }

    template <class _Iter>
    QNavigatableList(_Iter _First, _Iter _Last, const key_compare &_Pred, const allocator_type &_Al)
        : _Mybase(_Pred, _Al) {
        this->insert(_First, _Last);
    }

    QNavigatableList &operator=(const _Mybase &_Right) {
        _Mybase::operator=(_Right);
        return *this;
    }

    QNavigatableList(_Mybase &&_Right) : _Mybase(std::move(_Right)) {
    }

    QNavigatableList(_Mybase &&_Right, const allocator_type &_Al)
        : _Mybase(std::move(_Right), _Al) {
    }

    QNavigatableList &operator=(_Mybase &&_Right) {
        _Mybase::operator=(std::move(_Right));
        return *this;
    }

    void swap(_Mybase &_Right) noexcept(noexcept(_Mybase::swap(_Right))) {
        _Mybase::swap(_Right);
    }

    QNavigatableList(std::initializer_list<value_type> _Ilist) : _Mybase(key_compare()) {
        this->insert(_Ilist);
    }

    QNavigatableList(std::initializer_list<value_type> _Ilist, const key_compare &_Pred)
        : _Mybase(_Pred) {
        this->insert(_Ilist);
    }

    QNavigatableList(std::initializer_list<value_type> _Ilist, const allocator_type &_Al)
        : _Mybase(key_compare(), _Al) {
        this->insert(_Ilist);
    }

    QNavigatableList(std::initializer_list<value_type> _Ilist, const key_compare &_Pred,
                     const allocator_type &_Al)
        : _Mybase(_Pred, _Al) {
        this->insert(_Ilist);
    }

    QNavigatableList &operator=(std::initializer_list<value_type> _Ilist) {
        this->clear();
        this->insert(_Ilist);
        return *this;
    }

public:
    typedef _Kty T;

    QNavigatableList(const QSet<T> &set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            this->insert(*it);
        }
    }

    QNavigatableList(QSet<T> &&set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            this->insert(*it);
        }
    }

    QNavigatableList &operator=(const QSet<T> &set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            this->insert(*it);
        }
        return *this;
    }

    QNavigatableList &operator=(QSet<T> &&set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            this->insert(*it);
        }
        return *this;
    }

    iterator lower(T key) {
        if (this->empty()) {
            return _Mybase::end();
        }
        auto it = ceiling(key);
        return --it;
    }

    const_iterator lower(T key) const {
        if (this->empty()) {
            return _Mybase::end();
        }
        auto it = ceiling(key);
        return --it;
    }

    iterator floor(T key) {
        if (this->empty()) {
            return _Mybase::end();
        }
        auto it = ceiling(key);
        if (it != this->end() && *it == key) {
            return it;
        }
        return --it;
    }

    const_iterator floor(T key) const {
        if (this->empty()) {
            return _Mybase::end();
        }
        auto it = ceiling(key);
        if (it != this->end() && *it == key) {
            return it;
        }
        return --it;
    }

    iterator ceiling(T key) {
        return _Mybase::lower_bound(key);
    }

    const_iterator ceiling(T key) const {
        return _Mybase::lower_bound(key);
    }

    iterator higher(T key) {
        return _Mybase::upper_bound(key);
    }

    const_iterator higher(T key) const {
        return _Mybase::upper_bound(key);
    }

    bool contains(T key) const {
        return this->find(key) != this->end();
    }

    bool isEmpty() const {
        return this->empty();
    }

    size_type remove(T key) {
        return this->erase(key);
    }

    QSet<T> toQSet() const {
        QSet<T> res;
        for (auto it = this->begin(); it != this->end(); ++it) {
            res.insert(*it);
        }
        return res;
    }

    QList<T> toQList() const {
        QList<T> res;
        for (auto it = this->begin(); it != this->end(); ++it) {
            res.append(*it);
        }
        return res;
    }

    QNavigatableList &unite(const QNavigatableList &other) {
        for (const T &e : other) {
            this->insert(e);
        }
        return *this;
    }

    QNavigatableList &intersect(const QNavigatableList &other) {
        QNavigatableList copy1;
        QNavigatableList copy2;
        if (this->size() <= other.size()) {
            copy1 = *this;
            copy2 = other;
        } else {
            copy1 = other;
            copy2 = *this;
            *this = copy1;
        }
        for (const auto &e : qAsConst(copy1)) {
            if (!copy2.contains(e)) {
                this->remove(e);
            }
        }
        return *this;
    }

    bool intersects(const QNavigatableList<T> &other) const {
        const bool otherIsBigger = other.size() > this->size();
        const QNavigatableList &smallestSet = otherIsBigger ? *this : other;
        const QNavigatableList &biggestSet = otherIsBigger ? other : *this;

        typename QNavigatableList::const_iterator i = smallestSet.cbegin();
        typename QNavigatableList::const_iterator e = smallestSet.cend();

        while (i != e) {
            if (biggestSet.contains(*i)) {
                return true;
            }
            ++i;
        }

        return false;
    }

    QNavigatableList<T> &subtract(const QNavigatableList<T> &other) {
        for (const auto &e : other) {
            remove(e);
        }
        return *this;
    }

    template <class _Kty1, class _Pr1, class _Alloc1>
    friend QDebug operator<<(QDebug debug, const QNavigatableList<_Kty1, _Pr1, _Alloc1> &set);
};

template <class _Kty1, class _Pr1, class _Alloc1>
QDebug operator<<(QDebug debug, const QNavigatableList<_Kty1, _Pr1, _Alloc1> &set) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "QNavigableSet(";
    for (auto it = set.begin(); it != set.end(); ++it) {
        debug.nospace() << *it;
        if (std::next(it) != set.end()) {
            debug.nospace() << ", ";
        }
    }
    debug.noquote().nospace() << ")";
    return debug;
}

#endif // QMNAVIGATABLELIST_H
