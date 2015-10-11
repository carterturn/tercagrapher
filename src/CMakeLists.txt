#Local libraries
add_executable(tercagrapher main.cpp grapher.cpp grapher.h grapher2d.cpp grapher2d.h grapher3d.cpp grapher3d.h window.cpp window.h graphwindow.cpp graphwindow.h equwindow.cpp equwindow.h)

#ctvector TODO: make platform independant
include_directories(/usr/include/ctvector)
link_directories(/usr/lib)
link_directories(/usr/lib64)
target_link_libraries(tercagrapher ctvector)

#futuregl TODO: make platform independant
include_directories(/usr/include/futuregl)
link_directories(/usr/lib)
link_directories(/usr/lib64)
target_link_libraries(tercagrapher futuregl)

#muparser TODO: make platform independant
include_directories(/usr/include/)
link_directories(/usr/lib)
link_directories(/usr/lib64)
target_link_libraries(tercagrapher muparser)

#OpenGL, GLFW, and FTGL TODO: make platform independant
include_directories(/usr/include/)
link_directories(/usr/lib)
link_directories(/usr/lib64)
target_link_libraries(tercagrapher GL)
target_link_libraries(tercagrapher glfw)
target_link_libraries(tercagrapher ftgl)

add_definitions(--std=c++11)

install(TARGETS tercagrapher DESTINATION bin)

