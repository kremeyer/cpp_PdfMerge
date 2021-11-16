cmake_minimum_required(VERSION 3.20)
project(pdf_merger)

set(CMAKE_CXX_STANDARD 20)

include_directories("/usr/local/Cellar/boost/1.76.0/include")

add_executable(PdfMerge main.cpp main.h)
