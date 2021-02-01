cmake_minimum_required(VERSION 3.17)
project(Ex_exam C)

set(CMAKE_C_STANDARD 99)

add_executable(Ex_exam_list UNIVERSITY/ANNO_II/List/main.c UNIVERSITY/ANNO_II/List/function_create.h UNIVERSITY/ANNO_II/List/function_create.c UNIVERSITY/ANNO_II/List/function_char.h UNIVERSITY/ANNO_II/List/function_char.c)
add_executable(Ex_exam_array UNIVERSITY/ANNO_II/Array/main_array.c UNIVERSITY/ANNO_II/Array/Function.c UNIVERSITY/ANNO_II/Array/Function.h UNIVERSITY/ANNO_II/Array/Create.h UNIVERSITY/ANNO_II/Array/Create.c)
add_executable(Ex_exam_recursion UNIVERSITY/ANNO_II/Recursion/main_recursion.c UNIVERSITY/ANNO_II/Recursion/Function_recursive.h UNIVERSITY/ANNO_II/Recursion/Function_recursive.c)

add_executable(EX_PAD UNIVERSITY/ANNO_I/EX_PROF/PAD/mian_prof.c UNIVERSITY/ANNO_I/EX_PROF/PAD/pad.c UNIVERSITY/ANNO_I/EX_PROF/PAD/pad.h)
add_executable(EX_1 UNIVERSITY/ANNO_I/EX_PROF/EX_1/main_ex1.c UNIVERSITY/ANNO_I/EX_PROF/EX_1/function_ex1.h UNIVERSITY/ANNO_I/EX_PROF/EX_1/function_ex1.c)


add_executable(Project_PeL UNIVERSITY/PROJECTS/bmp.c UNIVERSITY/PROJECTS/bmp.h UNIVERSITY/PROJECTS/ip_lib.c UNIVERSITY/PROJECTS/ip_lib.h UNIVERSITY/PROJECTS/main_iplib.c)
