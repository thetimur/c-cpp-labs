#include <linq.hpp>
#include <cassert>
#include <sstream>
#include <cmath>

int main() {
    auto xs = std::vector<int>{10, 20, 30};
    auto res = linq::from(xs.begin(), xs.end()).until([](int x) {
        std::cerr << x << " ";
      assert(x == 10 || x == 20 || x == 30);
      return false;
    }).to_vector();
    assert((std::vector<int>{10, 20, 30}) == res);

    std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::stringstream iss("4 16");
    std::stringstream oss;
    std::istream_iterator<int> in(iss), eof;
    std::ostream_iterator<double> out(oss, "\n");

    linq::from(in, eof)    // Взять числа из входного потока
    .select([](int x) { return static_cast<int>(sqrt(x) + 1e-6); })  // Извлечь из каждого корень
    .copy_to(out);  // Вывести на экран

    assert(oss.str() == "2\n4\n");

    const int xs1[] = {1, 2, 3, 5};

    auto empty_res = linq::from(xs1, xs1 + 4).drop(4).until([](int a) {return a != 2;}).to_vector();

    assert(empty_res.empty() == true);
}