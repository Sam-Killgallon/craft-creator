cmake_minimum_required(VERSION 3.0.0)
project(crossstitch_creator VERSION 0.1.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GDK_PIXBUF REQUIRED gdk-pixbuf-2.0)

# Tell the compiler where to find the files
include_directories(${GDK_PIXBUF_INCLUDE_DIRS})
link_directories(${GDK_PIXBUF_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GDK_PIXBUF_CFLAGS_OTHER})

file(GLOB SOURCES "*.c")
add_executable(crossstitch_creator ${SOURCES})
target_link_libraries(crossstitch_creator ${GDK_PIXBUF_LIBRARIES})
