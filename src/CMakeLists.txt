AUX_SOURCE_DIRECTORY(. DIR_SRCS)
include_directories(../include)
add_executable (../${PROJECT_NAME}.exe ${DIR_SRCS}) # 要求编译可执行文件