
#include <iostream>
#include <string>
#include "rlib.min.hpp"

#include <vector>
#include <deque>
#include <algorithm>

uint64_t save_gift_for(const std::vector<size_t> &their_scores, std::vector<size_t> &answer_table, size_t index) {
    const auto left_index = index == 0 ? their_scores.size()-1 : index - 1,
                right_index = index == their_scores.size()-1 ? 0 : index+1;
    const auto left_score = their_scores[left_index],
                right_score = their_scores[right_index];
    
    size_t gifts = 1;
    if(their_scores[index] > left_score) {
        gifts = std::max(gifts, answer_table[left_index] + 1);
    }
    if(their_scores[index] > right_score) {
        gifts = std::max(gifts, answer_table[right_index] + 1);
    }

    answer_table[index] = gifts;
    //rlib::println("index", index, "used",gifts,"gifts");
    return gifts;
}

                       // can change vector to list and save interator. but too lazy.
uint64_t solve_problem(std::vector<size_t> their_scores) {
    if(their_scores.size() == 0) return 0;
    if(their_scores.size() == 1) return 1;

    std::vector<std::pair<size_t, size_t>> sort_table;
    //           pair <   score , index >
    std::vector<size_t> answer_table(their_scores.size()); // one-by-one corresponding to argument vector.

    for(auto cter = 0; cter < their_scores.size(); ++cter) {
        sort_table.emplace_back(their_scores[cter], cter);
    }

    std::sort(sort_table.begin(), sort_table.end(), [](const auto &left, const auto &right) {
        return left.first < right.first;
    });

    uint64_t used_gifts = 0;
    for(const auto &entry : sort_table) {
        const auto index = entry.second;
        used_gifts += save_gift_for(their_scores, answer_table, index);
    }

    return used_gifts;
}



int main() {
    rlib::scanln(); // remove the first line: junk input.
    while(true) {
        rlib::scanln(); // remove a junk line.
        auto line = rlib::scanln();
        if(std::cin.eof())
            break;
        rlib::println(solve_problem(line.split_as<size_t>()));
    }

}
