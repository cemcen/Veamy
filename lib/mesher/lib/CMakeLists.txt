add_library(triangle STATIC triangle.o)
SET_SOURCE_FILES_PROPERTIES(
        triangle.o
        PROPERTIES
        EXTERNAL_OBJECT true
        GENERATED true
)
SET_TARGET_PROPERTIES(
        triangle
        PROPERTIES
        LINKER_LANGUAGE C
)

install(TARGETS triangle EXPORT TriangleConfig
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(EXPORT TriangleConfig DESTINATION share/TriangleConfig/cmake)
export(TARGETS triangle FILE TriangleConfig.cmake)