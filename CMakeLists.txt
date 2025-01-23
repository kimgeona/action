# ==== cmake 설정 ====
cmake_minimum_required(VERSION 3.28)
project(
    Action
    VERSION 0.0.0
    DESCRIPTION "Use shell script like commands."
    LANGUAGES CXX
)

# ==== 프로젝트 버전 정보를 컴파일러 옵션으로 전달합니다. ====
add_compile_definitions(ACTION_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_compile_definitions(ACTION_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_compile_definitions(ACTION_VERSION_PATCH=${PROJECT_VERSION_PATCH})

# ==== C++ 표준 설정 ====
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==== include 디렉토리 설정 ====
include_directories(
    ./include
)

# ==== 파일 조사, 타겟 생성 ====
add_subdirectory(./include)
add_subdirectory(./src)

# ==== 운영체제 관련 설정 ====
if(APPLE)
    # Xcode : Working Directory 설정
    set_target_properties(
        action PROPERTIES
        XCODE_GENERATE_SCHEME TRUE
        XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/io/
    )
elseif(WIN32)
    # MSVC : Working Directory 설정
    set_target_properties(
        action PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/io/
    )
    target_compile_options(action PRIVATE "/utf-8")
endif()

# ==== 프로젝트 설치 ====
install(TARGETS action DESTINATION bin) # 설치 경로 지정

# ==== 변수 출력 ====
# include(CMakePrintHelpers)
# cmake_print_variables(CMAKE_PROJECT_VERSION)
# cmake_print_variables(INCLUDE_LIST)
# cmake_print_variables(LIB_LIST)
# cmake_print_variables(SRC_LIST)
