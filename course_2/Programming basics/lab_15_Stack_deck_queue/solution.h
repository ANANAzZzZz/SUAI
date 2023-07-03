#ifndef __SOLUTION_H_
#define __SOLUTION_H_

#include <string>
#include <vector>
#include <sstream>
#include <queue>

bool isOddSum(std::string_view word)
{
    int sum = 0;
    for (auto ch : word)
    {
        sum += ch - '0';
    }
    return sum % 2;
}

std::vector<std::string> solution(const std::string& line)
{
    std::deque<std::string> queue;
    std::vector<std::string> result;
    std::stringstream stream(line);

    for (std::string word; stream >> word;)
    {
        if (isOddSum(word))
        {
            queue.push_back(word);
        }
        else
        {
            result.push_back(word);
        }
    }
    
    while (!queue.empty())
    {
        result.push_back(queue.front());
        queue.pop_front();
    }

    return result;
}

#endif   // __SOLUTION_H_