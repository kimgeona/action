//
//  action_util.hpp
//  Action
//
//  Created by 김건아 on 1/22/25.
//

#include <Includes.hpp>

#ifndef utility_hpp
#define utility_hpp

// 탭 갯수 세기
int countLineTab(const std::string& str)
{
    int count = 0;
    for (int i=0; i<str.length(); i++) {
        if      (str[i] == '\t') count += 4;
        else if (str[i] == ' ')  count += 1;
        else                     break;
    }
    return count /= 4;
}

// 문자열 공백 제거
std::string trim(const std::string& str)
{
    // 왼쪽 공백 제거
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";  // 공백만 있을 경우 빈 문자열 반환

    // 오른쪽 공백 제거
    size_t end = str.find_last_not_of(" \t\n\r");

    return str.substr(start, end - start + 1);
}


#endif /* utility_hpp */
