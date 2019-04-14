/*腾讯云计算岗位垃圾笔试题1
 *
 * 给定一个01组成的字符串，我可以采取一个操作：消去相邻的一对01. 我想知道不断的消去一直到不能消去为止，我最终得到的字符串长度是多少？
 *
 * 例如： 1000101001 => 10001010 => 001010 => 0010 => 00, 答案是2
 *
 * 输入：
 * 第一行N，字符串长度
 * 第二行就是那个字符串。
 */

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
