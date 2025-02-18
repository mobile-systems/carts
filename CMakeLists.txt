cmake_minimum_required(VERSION 3.16) # Проверка версии CMake.
					# Если версия установленой программы
					# старее указаной, произайдёт аварийный выход.

project(carts LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CXX_EXTENSIONS NO)

add_executable(${PROJECT_NAME} objects.cpp)	# Создает исполняемый файл с именем main
