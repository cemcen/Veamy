set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(SOURCE_FILES ParabolicMainT3.cpp)
add_executable(Test ${SOURCE_FILES})
target_link_libraries(Test libutilities libdelynoi libveamy)
