if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW) # CMake 3.0
endif(POLICY CMP0042)

project(libxmount_input_nbd C)

add_library(xmount_input_nbd SHARED libxmount_input_nbd.c ../../libxmount/libxmount.c)

install(TARGETS xmount_input_nbd DESTINATION lib/xmount)
