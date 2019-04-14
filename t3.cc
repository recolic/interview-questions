/* tx
 *
 * 我需要通过一个怪兽谷，这里面依次有N个怪兽
 * 每一个怪兽都可以用一定的金币来收买他，这样她就会为你护航。
 * 你必须保证，在任何时候，保护你的怪兽的总武力值大于你遇到的这一个怪兽的武力值。
 * 求你要通过这个怪兽谷，需要的最少金币数。
 *
 * 输入：
 * N
 * N个元素的数组，表示每一个怪兽的武力值。
 * N个元素的数组，表示每一个怪兽的价格。
 *
 * N<1024
 *
 */

#include "rlib.min.hpp"


struct mon_info { uint64_t power, price; };
auto solution(const std::vector<mon_info> &mon, size_t curr_pos, size_t curr_cost, uint64_t curr_power) {
    if(curr_pos == mon.size())
        return curr_cost;
    const auto &curr_mon = mon.at(curr_pos);

    const auto cost_buy_him = solution(mon, curr_pos + 1, curr_cost + curr_mon.price, curr_power + curr_mon.power);
    if(curr_power < curr_mon.power) {
        return cost_buy_him;
    }
    else {
        const auto cost_without_buy_him = solution(mon, curr_pos + 1, curr_cost, curr_power);
        return std::min(cost_buy_him, cost_without_buy_him);
    }
}
auto solution(const std::vector<mon_info> &mon) {
    return solution(mon, 0, 0, 0);
}

int main() {
    rlib::scanln();
    const auto power_buf = rlib::scanln().split_as<uint64_t>();
    const auto price_buf = rlib::scanln().split_as<uint64_t>();

    std::vector<mon_info> mon_info_buf;
    for(auto cter = 0; cter < power_buf.size(); ++cter) {
        mon_info_buf.emplace_back(mon_info{power_buf[cter], price_buf[cter]});
    }

    rlib::println(solution(mon_info_buf));

}
