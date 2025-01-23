# 디렉토리에 있는 *.cpp 파일을 SRC_LIST 변수에 추가한다
file(
    GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
# 변수를 상위 스코프로 올린다
set(SRC_LIST ${SRC_LIST} PARENT_SCOPE)

# action
add_executable(action ${INCLUDE_LIST} ${SRC_LIST})