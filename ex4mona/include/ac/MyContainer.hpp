/*
 * email: 
 * File: MyContainer.hpp
 */
#ifndef AC_MYCONTAINER_HPP
#define AC_MYCONTAINER_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <numeric>
#include <ostream>

namespace ac {

template<typename T = int>
class MyContainer {
private:
    std::vector<T> _data;
    
    const std::vector<T>& raw() const { 
        return _data; 
    }

public:
    void add(const T& v) { 
        _data.push_back(v); 
    }
    
    void remove(const T& v) {
        auto old_size = _data.size();
        _data.erase(std::remove(_data.begin(), _data.end(), v), _data.end());
        
        if (_data.size() == old_size) {
            throw std::runtime_error("Element not found");
        }
    }
    
    std::size_t size() const { 
        return _data.size(); 
    }
    
    friend std::ostream& operator<<(std::ostream& os, const MyContainer& c) {
        os << "[";
        for (std::size_t i = 0; i < c._data.size(); ++i) {
            os << c._data[i];
            if (i + 1 != c._data.size()) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

private:
    template<typename Derived>
    class BaseIterator {
    protected:
        const MyContainer* container;
        std::vector<std::size_t> order;
        std::size_t position;
        
        BaseIterator(const MyContainer* c, std::vector<std::size_t> o, std::size_t p = 0)
            : container(c), order(std::move(o)), position(p) {}
    
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = std::ptrdiff_t;
        
        reference operator*() const {
            return container->raw()[order[position]];
        }
        
        pointer operator->() const {
            return &(**this);
        }
        
        Derived& operator++() {
            ++position;
            return static_cast<Derived&>(*this);
        }
        
        Derived operator++(int) {
            Derived temp = static_cast<Derived&>(*this);
            ++(*this);
            return temp;
        }
        
        bool operator==(const Derived& other) const {
            return container == other.container && position == other.position;
        }
        
        bool operator!=(const Derived& other) const {
            return !(*this == other);
        }
    };
    
    std::vector<std::size_t> ascending_order() const {
        std::vector<std::size_t> indices(_data.size());
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), 
                  [&](size_t a, size_t b) { return _data[a] < _data[b]; });
        return indices;
    }
    
    std::vector<std::size_t> descending_order() const {
        auto indices = ascending_order();
        std::reverse(indices.begin(), indices.end());
        return indices;
    }
    
    std::vector<std::size_t> cross_order() const {
        auto asc_indices = ascending_order();
        std::vector<std::size_t> result;
        
        std::size_t left = 0;
        std::size_t right = asc_indices.size() ? asc_indices.size() - 1 : 0;
        
        while (left <= right && left < asc_indices.size()) {
            result.push_back(asc_indices[left]);
            if (left == right) break;
            
            result.push_back(asc_indices[right]);
            ++left;
            
            if (right == 0) break;
            --right;
        }
        
        return result;
    }
    
    std::vector<std::size_t> insertion_order() const {
        std::vector<std::size_t> indices(_data.size());
        std::iota(indices.begin(), indices.end(), 0);
        return indices;
    }
    
    std::vector<std::size_t> reverse_order() const {
        auto indices = insertion_order();
        std::reverse(indices.begin(), indices.end());
        return indices;
    }
    
    std::vector<std::size_t> middle_order() const {
        std::vector<std::size_t> result;
        size_t n = _data.size();
        
        if (n == 0) return result;
        
        size_t middle = (n - 1) / 2;
        result.push_back(middle);
        
        for (size_t offset = 1; result.size() < n; ++offset) {
            if (middle >= offset) {
                result.push_back(middle - offset);
            }
            if (result.size() == n) break;
            
            if (middle + offset < n) {
                result.push_back(middle + offset);
            }
        }
        
        return result;
    }

public:
    class AscendingIterator : public BaseIterator<AscendingIterator> {
        using Base = BaseIterator<AscendingIterator>;
    public:
        AscendingIterator(const MyContainer* c, bool end = false)
            : Base(c, c->ascending_order(), end ? c->size() : 0) {}
    };
    
    class DescendingIterator : public BaseIterator<DescendingIterator> {
        using Base = BaseIterator<DescendingIterator>;
    public:
        DescendingIterator(const MyContainer* c, bool end = false)
            : Base(c, c->descending_order(), end ? c->size() : 0) {}
    };
    
    class CrossIterator : public BaseIterator<CrossIterator> {
        using Base = BaseIterator<CrossIterator>;
    public:
        CrossIterator(const MyContainer* c, bool end = false)
            : Base(c, c->cross_order(), end ? c->size() : 0) {}
    };
    
    class OrderIterator : public BaseIterator<OrderIterator> {
        using Base = BaseIterator<OrderIterator>;
    public:
        OrderIterator(const MyContainer* c, bool end = false)
            : Base(c, c->insertion_order(), end ? c->size() : 0) {}
    };
    
    class ReverseIterator : public BaseIterator<ReverseIterator> {
        using Base = BaseIterator<ReverseIterator>;
    public:
        ReverseIterator(const MyContainer* c, bool end = false)
            : Base(c, c->reverse_order(), end ? c->size() : 0) {}
    };
    
    class MiddleIterator : public BaseIterator<MiddleIterator> {
        using Base = BaseIterator<MiddleIterator>;
    public:
        MiddleIterator(const MyContainer* c, bool end = false)
            : Base(c, c->middle_order(), end ? c->size() : 0) {}
    };
    
    AscendingIterator beginAscending() const { return AscendingIterator(this); }
    AscendingIterator endAscending() const { return AscendingIterator(this, true); }
    
    DescendingIterator beginDescending() const { return DescendingIterator(this); }
    DescendingIterator endDescending() const { return DescendingIterator(this, true); }
    
    CrossIterator beginSideCross() const { return CrossIterator(this); }
    CrossIterator endSideCross() const { return CrossIterator(this, true); }
    
    OrderIterator begin() const { return OrderIterator(this); }
    OrderIterator end() const { return OrderIterator(this, true); }
    
    ReverseIterator rbegin() const { return ReverseIterator(this); }
    ReverseIterator rend() const { return ReverseIterator(this, true); }
    
    MiddleIterator beginMiddle() const { return MiddleIterator(this); }
    MiddleIterator endMiddle() const { return MiddleIterator(this, true); }
};

} // namespace ac

#endif // AC_MYCONTAINER_HPP