/*自解跳动笔试4 当时我没写玩，正确的做法是二分查找。
 *
 *
 * 已知有N根长度不一的绳子和他们的长度，我现在需要M根长度相等的绳子。你只能切断绳子，不能粘在一起。
 * 我想知道我的这M根绳子的最大长度是多少？
 *
 * 输入：
 * N M
 * N个整数，表示每个绳子的长度，空格分割
 * N M
 * N个整数，表示每个绳子的长度，空格分割
 * N M
 * N个整数，表示每个绳子的长度，空格分割
 * .........................
 *
 */


/*
 *
 * string.hpp: string process utility.
 * Recolic Keghart <root@recolic.net>
 * MIT License
 *
 * Bensong Liu: This is my "nickname" and this lib is written by me. I want to use 'split string' function.
 *
 */

#ifndef R_STRING_HPP
#define R_STRING_HPP

#include <vector>
#include <string>
#include <stdexcept>

namespace rlib {
    class string : public std::string {
    public:
        using std::string::string;
        string() : std::string() {}
        string(const std::string &s) : std::string(s) {}
        string(std::string &&s) : std::string(std::forward<std::string>(s)) {}

    private:
        template <typename T> struct as_helper {};
        template <typename T>
        T as(as_helper<T>) const {
            if(empty()) return T();
            return T(*this);
        }
        std::string as(as_helper<std::string>) const {
            return std::move(*this);
        }
        rlib::string as(as_helper<rlib::string>) const {
            return std::move(*this);
        }
        char as(as_helper<char>) const {
            if(size() > 1)
                throw std::invalid_argument("Can not convert rlib::string to char: size() > 1.");
            return size() == 0 ? '\0' : *cbegin();
        }
        unsigned char as(as_helper<unsigned char>) const {
            return static_cast<unsigned char>(as<char>());
        }
        bool as(as_helper<bool>) const {
            if(*this == "true") {
                return true;
            }
            else if(*this == "false") {
                return false;
            }
            // Nothing is slower than throw(); Just test more cases...
            else if(*this == "1" || *this == "True" || *this == "TRUE") {
                return true;
            }
            else if(*this == "0" || *this == "False" || *this == "FALSE") {
                return false;
            }
            throw std::invalid_argument("Can not convert rlib::string to bool. Not matching any template.");
        }

#define RLIB_IMPL_GEN_AS_NUMERIC(type, std_conv) \
        type as(as_helper<type>) const { \
            if(empty()) return 0; \
            return std::std_conv(*this); \
        }

        RLIB_IMPL_GEN_AS_NUMERIC(int, stoi)
        RLIB_IMPL_GEN_AS_NUMERIC(long, stol)
        RLIB_IMPL_GEN_AS_NUMERIC(unsigned long, stoul)
        RLIB_IMPL_GEN_AS_NUMERIC(unsigned long long, stoull)
        RLIB_IMPL_GEN_AS_NUMERIC(long long, stoll)
        RLIB_IMPL_GEN_AS_NUMERIC(float, stof)
        RLIB_IMPL_GEN_AS_NUMERIC(double, stod)
        RLIB_IMPL_GEN_AS_NUMERIC(long double, stold)

#define RLIB_IMPL_GEN_AS_ALIAS(new_type, old_type) \
        new_type as(as_helper<new_type>) const { \
            return static_cast<new_type>(as<old_type>()); \
        }

        RLIB_IMPL_GEN_AS_ALIAS(unsigned int, unsigned long)
        RLIB_IMPL_GEN_AS_ALIAS(unsigned short, unsigned long)
        //RLIB_IMPL_GEN_AS_ALIAS(uint8_t, unsigned long)

        RLIB_IMPL_GEN_AS_ALIAS(short, int)
        //RLIB_IMPL_GEN_AS_ALIAS(int8_t, int)

    public:
        template <typename T>
        T as() const {
            return std::forward<T>(as(as_helper<T>()));
        }

        template <typename T>
        std::vector<T> split_as(const char &divider = ' ') const {
            const string &toSplit = *this;
            std::vector<T> buf;
            size_t curr = 0, prev = 0;
            while((curr = toSplit.find(divider, curr)) != std::string::npos) {
                buf.push_back(string(toSplit.substr(prev, curr - prev)).as<T>());
                ++curr; // skip divider
                prev = curr;
            }
            buf.push_back(string(toSplit.substr(prev)).as<T>());
            return std::move(buf);
        }
        template <typename T>
        std::vector<T> split_as(const std::string &divider) const {
            const string &toSplit = *this;
            std::vector<T> buf;
            size_t curr = 0, prev = 0;
            while((curr = toSplit.find(divider, curr)) != std::string::npos) {
                buf.push_back(string(toSplit.substr(prev, curr - prev)).as<T>());
                curr += divider.size(); // skip divider
                prev = curr;
            }
            buf.push_back(string(toSplit.substr(prev)).as<T>());
            return std::move(buf);
        }

    };
}

#endif


#include <iostream>
#include <string>
namespace rlib {
    // This is my own hand-written library. I'm making it easy to use it directly.

    inline rlib::string scanln(std::istream &is = std::cin, char delimiter = '\n') noexcept {
        std::string line;
        std::getline(is, line, delimiter);
        return (line); // RVO
    }

    template <typename PrintFinalT>
    void print(PrintFinalT reqArg)
    {
        std::cout << reqArg;
    }
    template <typename Required, typename... Optional>
    void print(Required reqArgs, Optional... optiArgs)
    {
        std::cout << reqArgs << ' ';
        print(optiArgs ...);
    }
    template <typename... Optional>
    void println(Optional... optiArgs)
    {
        print(optiArgs ...);
        println();
    }
    template <> 
    inline void println()
    {
        //std::cout << rlib::endl;
        std::cout << std::endl;
    }
}

#include <vector>
#include <set>

struct cutted_rope {
    double length;
    size_t cutted_cter;
    cutted_rope(double len) : length(len), cutted_cter(1) {}
    double next_length(size_t level = 1) const {
        return length * cutted_cter / (cutted_cter + level);
    }
    bool operator<(const cutted_rope &right) const {
        const cutted_rope & left = *this;
        return left.next_length() < right.next_length();
    }
    void cut() {
        length = next_length();
        cutted_cter ++;
    }
};

double solve(std::vector<size_t> strings, size_t wanted_count) {
    std::multiset<cutted_rope> solution;
    for(auto &str : strings) {
        solution.emplace(str);
    }

    while(wanted_count < solution.size()) {
        solution.erase(solution.begin());
    }

    size_t solution_realSize = solution.size(); // cutted
    while(wanted_count > solution_realSize) {
        auto tmp = *--solution.end();
        solution.erase(--solution.end());
        tmp.cut();
        solution.emplace(tmp);
        ++solution_realSize;
    }

    return solution.begin()->next_length(0);
}

int main() {
    while(true) {
        auto line1 = rlib::scanln().split_as<size_t>();
        if(std::cin.eof())
            break;
        auto N = line1[0];
        auto M = line1[1];
        auto line2 = rlib::scanln().split_as<size_t>();
        if(N != line2.size())
            throw std::runtime_error("parse error");
        std::printf("%.2f\n", solve(line2, M));
    }
}

