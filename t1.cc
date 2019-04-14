#include "rlib.min.hpp"

#include <algorithm>
auto solution(const std::string &s) {
    size_t count_0 = std::count(s.begin(), s.end(), '0');
    size_t count_1 = s.size() - count_0;
    return std::max(count_0, count_1) - std::min(count_0, count_1);
}

int main() {
    rlib::scanln();
    auto str = rlib::scanln();
    rlib::println(solution(str));
}
