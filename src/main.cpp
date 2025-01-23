//
//  main.cpp
//  Action
//
//  Created by 김건아 on 1/22/25.
//

#include <iostream>
#include <deque>
#include <filesystem>

#include <action_core.hpp>

// ActionFile 경로
std::filesystem::path   ActionFileDir = std::filesystem::current_path() / "ActionFile";

// ActionFile 내용
std::deque<std::string> ActionFile;

// 인자로 받은 명령어들
std::deque<std::string> commands;

// 메인 프로그램
int main(int argc, const char * argv[])
{
    // 1. 명령어 저장
    for (int i = 1; i < argc; ++i) {
        commands.push_back(argv[i]);
    }
    
    // 2. ActionFile 내용 불러오기
    try {
        if (!std::filesystem::exists(ActionFileDir)) {
            throw std::runtime_error("action: ActionFile이 존재하지 않습니다.");
        }
        std::fstream file(ActionFileDir, std::ios::in);
        if (!file) {
            throw std::runtime_error("action: ActionFile을 열 수 없습니다.");
        }
        std::string line;
        while(std::getline(file, line)) {
            ActionFile.push_back(line);
        }
        file.close();
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cout << "action: ActionFile을 읽는 과정에서 알 수 없는 오류가 발생하였습니다." << std::endl;
        return 1;
    }
    
    // 3. ActionBlock 생성
    ActionBlock ab(ActionFile);
    
    // 4. 명령어 실행
    ab.action(commands);
    //ab.print();
    
    return 0;
}
