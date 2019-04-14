/* 字节跳动
 * 笔试q2
 * 转换字符串。对于字符串中的AAA，去掉一个变成AA
 * 对于字符串中的AABB，去掉一个变成AAB
 * 从左往右操作。
 *
 * 输入：第一行N
 * 接下来有N行，每行一个待处理字符串
 *
 * 输出：处理结果
 */

#include <iostream>
#include <string>

namespace rlib {
    // This is my own hand-written library. I'm making it easy to use it directly.
    using string = std::string;

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

size_t detect_dup_char(const std::string &str, size_t begin) {
    // If str is empty or begin is zero, there's no prev char.
    char prev = (begin*str.size() == 0) ? '\0' : str[begin-1];
    // NO!!! DO NOT SEE PREV!!
    //char prev = '\0';
    for(auto cter = begin; cter < str.size(); ++cter) {
        if(str[cter] == prev)
            return cter;
        prev = str[cter];
    }
    return std::string::npos;
}

void fuck_line(std::string &line) {
    size_t curr = 0;
    while(true) {
        curr = detect_dup_char(line, curr);
        if(curr == std::string::npos)
            return;
        if(curr + 1 >= line.size())
            return;
        if(line[curr+1] == line[curr]) // line[curr+1] is always valid.
        {
            line.erase(curr+1, 1);
            continue;
        }
        if(curr + 2 >= line.size())
            return;
        if(line[curr+1] == line[curr+2]) {
            line.erase(curr+2, 1);
            continue;
        }
        ++curr;
    }
}

int main() {
    rlib::scanln(); // remove the first line: junk input.
    while(true) {
        auto line = rlib::scanln();
        if(std::cin.eof())
            break;
        fuck_line(line);
        rlib::println(line);
    }
}

