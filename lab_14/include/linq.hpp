#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iterator>
#include <functional>
#include <iostream>

// I love this one!

namespace linq {
namespace impl {

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template <class T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;

template <class T>
class enumerator {
public:
    enumerator(const enumerator&) = delete;
    enumerator& operator=(const enumerator&) = delete;
    enumerator& operator=(enumerator&&) = delete;
    enumerator(enumerator&&) = default;
    enumerator() = default;

    virtual ~enumerator() = default;

    virtual operator bool() const = 0;
    virtual const T& operator*() const = 0;
    virtual enumerator& operator++() = 0;

    auto take(int number) {
        return take_enumerator<T>(*this, number);
    }

    auto drop(int number) {
        return drop_enumerator<T>(*this, number);
    }

    auto until_eq(T element) {
        return until_enumerator<T, std::function<bool(T)> >(*this, [element](T a) {return a == element;});
    }

    auto where_neq(T element) {
        return where_enumerator<T, std::function<bool(T)> >(*this, [element](T a) { return ( a != element ); });
    }

    template<typename F>
    auto where(F func) {
        return where_enumerator<T, F>(*this, std::move(func));
    }

    template<typename F>
    auto until(F func) {
        return until_enumerator<T, F>(*this, std::move(func));
    }

    template<typename U = T, typename F>
    auto select(F predicate) {
        return select_enumerator<U, T, F>(*this, std::move(predicate));
    }

    std::vector<T> to_vector() {
        enumerator& self = *this;
        std::vector<T> res;
        while(self) {
            res.push_back(*self);
            ++self;
        }
        return res;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        enumerator& self = *this;

        while (self) {
            *it = *self;
            ++self;
            ++it;
        }
    }
};

template <typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
    range_enumerator(Iter beg, Iter end) : beg_(beg), end_(end) {}

    virtual operator bool() const {
        return beg_ != end_;
    }
    virtual const T& operator*() const {
        return *beg_;
    }
    virtual enumerator<T>& operator++() {
        ++beg_;
        return *this;
    }

private:
    Iter beg_, end_;
};

template <typename T>
class take_enumerator : public enumerator<T> {
public:
    take_enumerator(enumerator<T>& parent, int num) : parent_(parent), number_(num) {}

    virtual operator bool() const {
        return number_ && parent_;
    }
    virtual const T& operator*() const {
        return *parent_;
    }
    virtual enumerator<T>& operator++() {
        number_--;
        if (number_) {
            ++parent_;
        }
        return *this;
    }
private:
    enumerator<T>& parent_;
    int number_;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
    where_enumerator(enumerator<T> &parent, F func) : parent_(parent), func_(std::move(func)) {
        move_forward();
    }

    virtual operator bool() const {
        return (bool) parent_; 
    }
    virtual const T& operator*() const {
        return *parent_;
    }
    virtual enumerator<T>& operator++() {
        ++parent_;
        move_forward();

        return *this;
    }

private:
    enumerator<T>& parent_;
    F func_;

    void move_forward() {
        while (bool(parent_) && !func_(*parent_)) {
            ++parent_;
        }
    }
};


template<typename T>
class drop_enumerator : public enumerator<T> {
public:
    drop_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {
        while (bool(parent_) && count_--) {
            ++parent_;
        }
    }

    virtual operator bool() const {
        return (bool) parent_;
    }

    virtual const T& operator*() const {
        return *parent_;
    }

    virtual enumerator<T>& operator++() {
        ++parent_;
        return *this;
    }
private:
    enumerator<T>& parent_;
    int count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
    select_enumerator(enumerator<U> &parent, F predicate) : parent_(parent), predicate_(std::move(predicate)) {
        update_value();
    }

    virtual operator bool() const {
        return (bool) parent_;
    }

    virtual const T& operator*() const {
        return value_;
    }

    virtual enumerator<T>& operator++() {
        ++parent_;
        update_value();
        return *this;
    }

private:
    enumerator<U>& parent_;
    F predicate_;
    T value_;

    void update_value() {
        if (parent_) {
            value_ = predicate_(*parent_);
        }
    }
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
    until_enumerator(enumerator<T> &parent, F func) : parent_(parent), func_(std::move(func)) {
        if (parent_) {
            value_ = func_(*parent_);
        }
    }
    until_enumerator(until_enumerator&&) = default;

    virtual operator bool() const {
        return (bool) parent_ && !value_;
    }

    virtual const T& operator*() const {
        return *parent_;
    }

    virtual enumerator<T>& operator++() {
        ++parent_;
        if (!parent_) {
            value_ = 0;
        } else {
            value_ = func_(*parent_);
        }
        return *this;
    }

private:
    enumerator<T>& parent_;
    F func_;
    bool value_;
};

} // namespace impl

template <typename Iter>
auto from(Iter beg, Iter end) {
    return impl::range_enumerator<typename std::iterator_traits<Iter>::value_type, Iter>(beg, end);
}

} // namespace linq

#endif


// It was difficult, but very instructive