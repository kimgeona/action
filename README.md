# Action
Action은 자주 사용하는 쉘 스크립트들을 커스텀 명령어로 실행해주는 프로그램입니다. ActionFile을 이용하여 쉘 스크립트를 기록하고 명령어로 만들어 작업들을 간편화 해보세요. :)

    # 프로젝트 다운
    $ git clone https://github.com/kimgeona/action.git

    # 프로그램 생성 
    $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./action/install -S./action -B./action/build
    $ cmake --build ./action/build -j$(sysctl -n hw.ncpu)
    $ cmake --build ./action/build --target install

### ActionFile 작성 방법
..프로그램 개발중