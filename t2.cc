/*tx2
 *
 * 我现在有N种面值的硬币。
 * 我现在去菜市场，希望带尽可能少的这些硬币，同时又必须能够凑出[1, M]范围内的任何一个的整数面值。
 * 我最少带多少硬币？
 *
 * 输入：
 * M N
 * 空格分割的N个整数，表示面值数。
 *
 * N<1024, M<10^10
 */

#include "rlib.min.hpp"

#include <algorithm>
#include <vector>

using std::size_t;
auto solution(std::vector<size_t> coins, size_t m) {
    std::sort(coins.begin(), coins.end());
    size_t sum = 0;
    size_t count = 0;
    for(auto iter = coins.begin(); iter != coins.end(); ++iter) {
        if(m <= sum)
            return count;
    loop_head:
        if(*iter > sum + 1) {
            if(iter == coins.begin())
                throw std::runtime_error("no solution");
            --iter;
            goto loop_head;
        }
        else if(*iter < sum + 1) {
            if(iter+1 != coins.end() && *(iter+1) <= sum + 1) {
                continue;
            }
        }
        sum += *iter;
        ++count;
    }
    if(m > sum) {
        auto biggest = coins.back();
        count += (m-sum) / biggest;
        if((m-sum) % biggest != 0)
            ++ count;
    }
    return count;
}

int main() {
    auto m = rlib::scanln().split_as<size_t>()[0];
    std::vector<size_t> coins;
    while(!std::cin.eof())
        coins.emplace_back(rlib::scanln().as<size_t>());
    try {
        rlib::println(solution(coins, m));
    }
    catch(...) {
        rlib::println(-1);
    }
}
