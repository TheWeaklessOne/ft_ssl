cmake_minimum_required(VERSION 3.17)
project(ft_ssl C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS -lreadline)
include_directories(Includes)
add_executable(ft_ssl
        Sources/Ft/ft_1.c
        Sources/Ft/ft_2.c
        Sources/Ft/ft_open_file.c
        Sources/Ft/ft_read_file.c
        Sources/Ft/ft_strsplit.c
        Sources/main.c
        Sources/put_info.c
        Sources/setup_readline.c
        Sources/Ft/ft_3.c
        Sources/setup_ssl.c
        Sources/check_flags.c
        Includes/list.h
        Sources/Ft/list.c
        Sources/check_command.c
        Sources/do_hash.c
        Sources/hash.c
        Sources/Algorithms/utils.c

        Includes/md5.h
        Sources/Algorithms/md5.c

        Sources/Algorithms/sha224.c

        Includes/sha256.h
        Sources/Algorithms/sha256.c

        Sources/Algorithms/sha384.c

        Includes/sha512.h
        Sources/Algorithms/sha512.c


        Sources/Algorithms/sha512_224.c

        Sources/Algorithms/sha512_256.c)