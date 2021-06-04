#include <iostream>
#include <cassert>
#include <cstring>
#include "my_vector.h"

namespace product {

class Product {
public:
	Product() = delete;
    Product(const char* name, int quantity, double price);
    Product(const Product &p);
    ~Product();
    friend std::ostream& operator <<(std::ostream& os, const Product &p);

public:
    char *name_;  // Указатель владеет C-style строкой, на которую указывает.
    int quantity_;
    double price_;
};

Product::Product(const char* name, int quantity, double price) : quantity_(quantity), price_(price) {
	name_ = new char[std::strlen(name) + 1];
	std::strcpy((char*)name_, name);
}

Product::Product(const Product &p) : Product(p.name_, p.quantity_, p.price_) {}


Product::~Product() {
	delete [] name_;
	name_ = nullptr;
}

std::ostream& operator <<(std::ostream& os, const Product &p) {
	os << p.name_ << " " << p.quantity_ << " " << p.price_;
	return os;
}

void print(const containers::my_vector<Product>& v) {
    std::cout << v << std::endl;
}

}  // namespace product

using namespace product;
using namespace containers;

int main() {
	
	my_vector<int> ints;
	for (int i = 0; i < 5; i++) {
		ints.push_back(i);
	}
	assert(ints.size() == 5);
	assert(ints.capacity() == 8);

	ints.resize(10);
	assert(ints.size() == 10);
	assert(ints.capacity() == 16);
	assert(ints[9] == int());

	std::cout << ints << std::endl;

	my_vector<int> bigints(20);

	assert(bigints.size() == 20);
	assert(bigints.capacity() == 32);

	my_vector<Product> a;
    assert(a.size() == 0);
    assert(a.capacity() == 1);

    Product tmp = Product("asap!!", 2, 14.0);

    a.push_back(tmp);
    assert(a.size() == 1);
    assert(!a.empty());
    assert(a[0].quantity_ == tmp.quantity_);
    assert(a.capacity() == 1);

    my_vector<Product> b = a;
    assert(b.size() == 1);
    assert(b.capacity() == 1);
    assert(b[0].price_ == tmp.price_);

    b.clear();
    assert(b.empty());

    b.reserve(10);
    assert(b.capacity() == 16);

    a.push_back(tmp);
    assert(a.size() == 2);
    assert(a[1].price_ == tmp.price_);

    b.push_back(tmp);
    b.push_back(tmp);
    assert(b.size() == 2);
    assert((b[0].quantity_ == tmp.quantity_) && (b[1].price_ == tmp.price_));

    my_vector<Product> c;
    c = b;
    assert(c.size() == 2);
    assert((c[0].price_ == tmp.price_) && (c[1].quantity_ == tmp.quantity_));

    c.pop_back();
    assert(c.size() == 1);
    assert(c[0].price_ == tmp.price_);

    c.pop_back();
    assert(c.size() == 0);

    print(a);

    return 0;
}
