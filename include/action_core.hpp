//
//  action_core.hpp
//  Action
//
//  Created by 김건아 on 1/22/25.
//

#include <Includes.hpp>
#include <action_util.hpp>

#ifndef action_core_hpp
#define action_core_hpp

// 명령어 블럭
class ActionBlock
{
private:
    std::deque<std::pair<char, std::string>> list; // 스크립트 목록
    std::map<std::string, ActionBlock>       link; // ActionBlock 목록
    
public:
    ActionBlock(std::deque<std::string>& ActionFile, int preCount=0)
    {
        // ActionFile의 line을 하나씩 읽어 list에 저장한다.
        while (!ActionFile.empty())
        {
            // 1. line 얻기
            std::string line = ActionFile.front();
            
            // 2-1. line 비어있는지 확인
            if (trim(line)=="") {
                ActionFile.pop_front();
                continue;
            }
            
            // 2-2. ActionBlock이 끝나는 지점인지 들여쓰기 갯수로 확인
            int tabCount = countLineTab(line);
            if (tabCount < preCount)
                break;
            ActionFile.pop_front();
            
            // 3. 구분자와 내용 분리
            line = trim(line);
            char        type = line[0];                                  // 구분자 추출
            std::string content = trim(line.substr(1, line.length()-1)); // 내용 추출
            
            // 4. list, link 목록에 추가
            list.push_back({type, content});
            if (type == ':') {
                link.emplace(content, ActionBlock(ActionFile, tabCount + 1));
            }
        }
    }
    
    // 명령어 블럭 찾아서 반환
    ActionBlock& operator[](const std::string& command)
    {
        // CommandBlock 찾기
        auto it = link.find(command);
        
        // CommandBlock 반환
        if (it == link.end())   throw std::out_of_range("action: 정의되지 않은 명령어 호출.");
        else                    return it->second;
    }
    
    // 명령어 블럭 실행
    void action(std::deque<std::string>& commands)
    {
        if (commands.empty())
        {
            // 스크립트 실행
            for (const auto& [type, content] : list) {
                if (type == '$') {
                    std::cout << content << std::endl; // TODO: 스크립트를 실행하는 코드로 바꾸기
                }
            }
        }
        else
        {
            // 명령어 추출
            std::string command = commands.front();
            commands.pop_front();
            
            // 스크립트 실행
            for (const auto& [type, content] : list)
            {
                switch (type)
                {
                    case '$':
                        std::cout << content << std::endl; // TODO: 스크립트를 실행하는 코드로 바꾸기
                        break;
                    case ':':
                        if (content == command) {
                            (*this)[content].action(commands);
                        }
                        break;
                }
            }
        }
    }
    
    // 저장된 스크립트 출력(디버깅용)
    void print(int level=0)
    {
        for (const auto& [type, content] : list)
        {
            for (int i=0; i<level; i++) {
                std::cout << '\t';
            }
            switch (type)
            {
                case '#':
                    std::cout << type << " " << content << std::endl;
                    break;
                case '$':
                    std::cout << type << " " << content << std::endl;
                    break;
                case ':':
                    std::cout << type << content << std::endl;
                    (*this)[content].print(level+1);
                    break;
            }
        }
    }
};


#endif /* action_core_hpp */
