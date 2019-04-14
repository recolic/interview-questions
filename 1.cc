/* Bytedance
 * 笔试 q1
 * 有1 4 16 64这几种硬币，凑出N元钱，最少用多少个硬币？N<=1024
 *
 */

#include <iostream>
#include <utility>

size_t try_return(size_t &todo_ret, size_t coin_val) {
    auto count = todo_ret / coin_val;
    todo_ret %= coin_val;
    return count;
}

int main() {
    size_t N;
    std::cin >> N;

    if(N > 1024)
        throw std::invalid_argument("Insufficent money");
    
    auto ret = 1024 - N;
    auto answer = try_return(ret, 64) + try_return(ret, 16) + try_return(ret, 4) + try_return(ret, 1);

    std::cout << answer << std::endl;
}

