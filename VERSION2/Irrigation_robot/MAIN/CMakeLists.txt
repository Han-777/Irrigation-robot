# cmake_minimum_required(VERSION 3.16)
# # 指定编译平台/架构与语言标准, 推荐指定Ninja为构建工具,可以加快编译速度(相比make)
# set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR arm)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
# # 指定工具链
# set(CMAKE_C_COMPILER_FORCED TRUE) # skip compiler test
# set(CMAKE_CXX_COMPILER_FORCED TRUE)
# set(CMAKE_C_COMPILER arm-none-eabi-gcc)
# set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
# set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
# set(CMAKE_OBJDUMP arm-none-eabi-objdump)
# set(SIZE arm-none-eabi-size) 
# set(CMAKE_AR arm-none-eabi-ar)
# set(CMAKE_C_STANDARD 17)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# # 指定工程名称和语言类型
# project(Irrigating_robot C ASM) 

# # 选择构建类型
# set(CMAKE_BUILD_TYPE Debug) # Debug Release RelWithDebInfo MinSizeRel

# # board specific settings, arch/fpu/instruction
# set(MCU_FLAGS -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard)
# set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32H743XIHx_FLASH.ld")
# # set(DSP_NAME "libCMSISDSP.a") # 指定DSP库名称
# # link_directories(${CMAKE_SOURCE_DIR}/Middlewares/ST/ARM/DSP/Lib)

# # Generic compiler settings for optimization and basic link lib
# add_compile_options(-pipe ${MCU_FLAGS} -Wall -Werror -fmessage-length=0 # basic options
#                     -ffunction-sections -fdata-sections -fno-common # optimize options 
#                     )

# add_link_options(-pipe ${MCU_FLAGS} -T${LINKER_SCRIPT} -Wl,--no-warn-rwx-segments # close RWX warning
#                  -lm -lc -lnosys # lib options
#                  -Wl,--gc-sections -flto -specs=nano.specs -specs=nosys.specs # optimize options
#                  -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map -Wl,--cref -Wl,--print-memory-usage # map options
#                  ) # if your executable is too large , try option '-s' to strip symbols

# # add_compile_definitions() works for compile stage
# # while add_definitions() works for both compile and link stage
# add_definitions(
#     -DUSE_HAL_DRIVER 
#     -DSTM32H743xx 
#     ) # need -D<macro> to define macro

# # add inc
# # 递归包含头文件的函数
# function(include_sub_directories_recursively root_dir)
#     if (IS_DIRECTORY ${root_dir})               # 当前路径是一个目录吗，是的话就加入到包含目录
#         message("include dir: " ${root_dir})
#         include_directories(${root_dir})
#     endif()

#     file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
#     foreach(sub ${ALL_SUB})
#         if (IS_DIRECTORY ${root_dir}/${sub})
#             include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
#         endif()
#     endforeach()
# endfunction()
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Drivers)
# # include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Middlewares)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/bsp)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/modules)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/application)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Core/Inc)

# # add source, only surfix .c
# file(GLOB_RECURSE SOURCES
#     "Drivers/*.c"
#     "Core/Src/*.c"
#     # "Middlewares/*.c"
#     "bsp/*.c"
#     "modules/*.c"
#     "application/*.c"
# )

# # 汇编文件路径
# # ENABLE_LANGUAGE(ASM)
# set(ASM_SOURCES
#     startup_stm32h743xx.s
#     # Middlewares/Third_Party/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.s
#     )
# set_source_files_properties(${ASM_SOURCES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

# # # Build types 有问题版本
# # if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
# #     message(STATUS "Maximum optimization for speed")
# #     add_compile_options(-Ofast)
# # elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
# #     message(STATUS "Maximum optimization for speed, debug info included")
# #     add_compile_options(-Ofast -g)
# # elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
# #     message(STATUS "Maximum optimization for size")
# #     add_compile_options(-Os)
# # else ()
# #     message(STATUS "Minimal optimization, debug info included")
# #     add_compile_options(-Og -g -gdwarf-2)
# #     add_definitions(-DESC_DEBUG) # ESC Debug
# # endif ()

# # Build types
# if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
#     message(STATUS "Maximum optimization for speed")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Ofast)
# elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
#     message(STATUS "Maximum optimization for speed, debug info included")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Ofast -g)
# elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
#     message(STATUS "Maximum optimization for size")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Os)
# else ()
#     message(STATUS "Minimal optimization, debug info included")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Og -g -gdwarf-2)
#     add_definitions(-DESC_DEBUG)
# endif ()

# # build binary and hex file
# add_executable(${PROJECT_NAME}.elf  ${SOURCES} ${ASM_SOURCES})
# # target_link_libraries(${PROJECT_NAME}.elf ${DSP_NAME} m) # link DSP lib and math lib

# add_custom_command(
#     TARGET ${PROJECT_NAME}.elf POST_BUILD
#     COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
#     COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin
#     COMMENT "Building hex & bin file..."
#     COMMENT "EXCUTABLE SIZE:"
#     COMMAND ${SIZE} ${PROJECT_NAME}.elf
#   )

# VERSION 1
# cmake_minimum_required(VERSION 3.16)

# # 指定编译平台/架构与语言标准
# set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR arm)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# # 指定工具链
# set(CMAKE_C_COMPILER_FORCED TRUE) # skip compiler test
# set(CMAKE_CXX_COMPILER_FORCED TRUE)
# set(CMAKE_C_COMPILER arm-none-eabi-gcc)
# set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
# set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
# set(CMAKE_OBJDUMP arm-none-eabi-objdump)
# set(SIZE arm-none-eabi-size)
# set(CMAKE_AR arm-none-eabi-ar)
# set(CMAKE_C_STANDARD 17)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# # 指定工程名称和语言类型
# project(Irrigating_robot C ASM) 

# # 选择构建类型
# set(CMAKE_BUILD_TYPE Debug) # Debug Release RelWithDebInfo MinSizeRel

# # board specific settings, arch/fpu/instruction
# set(MCU_FLAGS "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard")
# set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32H743XIHx_FLASH.ld")

# # Generic compiler settings for optimization and basic link lib
# add_compile_options(
#     -pipe ${MCU_FLAGS} -Wall -Werror -fmessage-length=0 # basic options
#     -ffunction-sections -fdata-sections -fno-common # optimize options
# )

# add_link_options(
#     -pipe ${MCU_FLAGS} -T${LINKER_SCRIPT} -Wl,--no-warn-rwx-segments # close RWX warning
#     -lm -lc -lnosys # lib options
#     -Wl,--gc-sections -flto -specs=nano.specs -specs=nosys.specs # optimize options
#     -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map -Wl,--cref -Wl,--print-memory-usage
# ) # if your executable is too large, try option '-s' to strip symbols

# # add_compile_definitions() works for compile stage
# # while add_definitions() works for both compile and link stage
# add_definitions(
#     -DUSE_HAL_DRIVER 
#     -DSTM32H743xx 
# ) # need -D<macro> to define macro

# # 递归包含头文件的函数
# function(include_sub_directories_recursively root_dir)
#     if (IS_DIRECTORY ${root_dir}) # 当前路径是一个目录吗，是的话就加入到包含目录
#         message("include dir: " ${root_dir})
#         include_directories(${root_dir})
#     endif()

#     file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
#     foreach(sub ${ALL_SUB})
#         if (IS_DIRECTORY ${root_dir}/${sub})
#             include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
#         endif()
#     endforeach()
# endfunction()
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Drivers)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/bsp)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/modules)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/application)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Core/Inc)

# # 添加源文件
# file(GLOB_RECURSE SOURCES
#     "Drivers/*.c"
#     "Core/Src/*.c"
#     "bsp/*.c"
#     "modules/*.c"
#     "application/*.c"
# )

# # 汇编文件路径
# set(ASM_SOURCES
#     startup_stm32h743xx.s
# )
# set_source_files_properties(${ASM_SOURCES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

# # 构建可执行文件
# add_executable(${PROJECT_NAME}.elf ${SOURCES} ${ASM_SOURCES})

# # Build types
# if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
#     message(STATUS "Maximum optimization for speed")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Ofast)
# elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
#     message(STATUS "Maximum optimization for speed, debug info included")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Ofast -g)
# elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
#     message(STATUS "Maximum optimization for size")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Os)
# else ()
#     message(STATUS "Minimal optimization, debug info included")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Og -g -gdwarf-2)
#     add_definitions(-DESC_DEBUG)
# endif ()

# # 添加自定义命令生成 HEX 和 BIN 文件
# add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
#     COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
#     COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin
#     COMMENT "Building hex & bin file..."
#     COMMAND ${SIZE} ${PROJECT_NAME}.elf
# )

# VERSION2
# cmake_minimum_required(VERSION 3.16)

# # 指定编译平台/架构与语言标准
# set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR ARM)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# # 指定工具链
# set(CMAKE_C_COMPILER_FORCED TRUE) # skip compiler test
# set(CMAKE_CXX_COMPILER_FORCED TRUE)
# set(CMAKE_C_COMPILER arm-none-eabi-gcc)
# set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
# set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
# set(CMAKE_OBJDUMP arm-none-eabi-objdump)
# set(SIZE arm-none-eabi-size) 
# set(CMAKE_AR arm-none-eabi-ar)
# set(CMAKE_C_STANDARD 11)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# # 指定工程名称和语言类型
# project(Irrigation_framework C ASM) 

# # 选择构建类型
# set(CMAKE_BUILD_TYPE Debug)

# # board specific settings, arch/fpu/instruction
# set(MCU_FLAGS -mcpu=cortex-m7 -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv5-d16)
# set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32H743XIHx_FLASH.ld")

# # Generic compiler settings for optimization and basic link lib
# add_compile_options(-pipe ${MCU_FLAGS} -Wall -Werror -fmessage-length=0 # basic options
#                     -ffunction-sections -fdata-sections -fno-common # optimize options 
#                     )
# add_link_options(-pipe ${MCU_FLAGS} -T${LINKER_SCRIPT} -Wl,--no-warn-rwx-segments # close RWX warning
# -lm -lc -lnosys # lib options
# -Wl,--gc-sections -flto -specs=nano.specs -specs=nosys.specs # optimize options
# -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map -Wl,--cref -Wl,--print-memory-usage # map options
# ) # if your executable is too large , try option '-s' to strip symbols

# add_definitions(
#     -DUSE_HAL_DRIVER 
#     -DSTM32H743xx 
# )

# set_source_files_properties(${ASM_SOURCES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")
# # Build types
# if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
#     message(STATUS "Maximum optimization for speed")
#     add_compile_options(-Ofast)
# elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
#     message(STATUS "Maximum optimization for speed, debug info included")
#     add_compile_options(-Ofast -g)
# elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
#     message(STATUS "Maximum optimization for size")
#     add_compile_options(-Os)
# else ()
#     message(STATUS "Minimal optimization, debug info included")
#     add_compile_options(-Og -g -gdwarf-2)
#     add_definitions(-DESC_DEBUG) # ESC Debug
# endif ()

# # 添加源文件
# file(GLOB_RECURSE SOURCES
#     "Drivers/*.c"
#     "Core/Src/*.c"
#     "bsp/*.c"
#     "modules/*.c"
#     "application/*.c"
# )

# # 汇编文件路径
# set(ASM_SOURCES
#     startup_stm32h743xx.s
# )


# # 构建可执行文件
# add_executable(${PROJECT_NAME}.elf ${SOURCES} ${ASM_SOURCES})
# target_link_libraries(${PROJECT_NAME}.elf) # link DSP lib and math lib


# # 添加自定义命令生成 HEX 和 BIN 文件
# add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
#     COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
#     COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin
#     COMMENT "Building hex & bin file..."
#     COMMENT "EXCUTABLE SIZE:"
#     COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
# )

# VERSION 3
# cmake_minimum_required(VERSION 3.16)
# # 指定编译平台/架构与语言标准, 推荐指定Ninja为构建工具,可以加快编译速度(相比make)
# set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR arm)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
# # 指定工具链
# set(CMAKE_C_COMPILER_FORCED TRUE) # skip compiler test
# set(CMAKE_CXX_COMPILER_FORCED TRUE)
# set(CMAKE_C_COMPILER arm-none-eabi-gcc)
# set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
# set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
# set(CMAKE_OBJDUMP arm-none-eabi-objdump)
# set(SIZE arm-none-eabi-size) 
# set(CMAKE_AR arm-none-eabi-ar)
# set(CMAKE_C_STANDARD 11)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# # 指定工程名称和语言类型
# project(Irrigating_robot C ASM) 

# # 选择构建类型
# set(CMAKE_BUILD_TYPE Debug) # Debug Release RelWithDebInfo MinSizeRel

# # board specific settings, arch/fpu/instruction
# set(MCU_FLAGS -mcpu=cortex-m7 -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv5-d16)
# set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32H743XIHx_FLASH.ld") # 指定链接脚本

# # Generic compiler settings for optimization and basic link lib
# add_compile_options(-pipe ${MCU_FLAGS} -Wall -Werror -fmessage-length=0 # basic options
#                     -ffunction-sections -fdata-sections -fno-common # optimize options 
#                     )
# add_link_options(-pipe ${MCU_FLAGS} -T${LINKER_SCRIPT} -Wl,--no-warn-rwx-segments # close RWX warning
#                  -lm -lc -lnosys # lib options
#                  -Wl,--gc-sections -flto -specs=nano.specs -specs=nosys.specs # optimize options
#                  -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map -Wl,--cref -Wl,--print-memory-usage # map options
#                  ) # if your executable is too large , try option '-s' to strip symbols

# # add_compile_definitions() works for compile stage
# # while add_definitions() works for both compile and link stage
# add_definitions(
#     -DUSE_HAL_DRIVER 
#     -DSTM32H743xx 
#     ) # need -D<macro> to define macro

# # add inc
# # 递归包含头文件的函数
# function(include_sub_directories_recursively root_dir)
#     if (IS_DIRECTORY ${root_dir})               # 当前路径是一个目录吗，是的话就加入到包含目录
#         message("include dir: " ${root_dir})
#         include_directories(${root_dir})
#     endif()

#     file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
#     foreach(sub ${ALL_SUB})
#         if (IS_DIRECTORY ${root_dir}/${sub})
#             include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
#         endif()
#     endforeach()
# endfunction()
# # include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Drivers)
# # include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/bsp)
# # include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/modules)
# # include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/application)
# # include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Core/Inc)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32H7xx/Include)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/bsp)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/modules)
# # include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/application)
# include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/Core/Inc)
# # add source, only surfix .c
# file(GLOB_RECURSE SOURCES

#     "Drivers/STM32H7xx_HAL_Driver/Src*.c"
#     "Drivers/STM32H7xx_HAL_Driver/Inc/Legacy*.c"
#     "Drivers/CMSIS/Device/ST/STM32H7xx/Include*.c"
#     "Drivers/CMSIS/Include*.c"

#     "Core/Src/*.c"
#     "bsp/*.c"
#     "modules/*.c"
#     # "application/*.c"
# )

# # 汇编文件路径
# # ENABLE_LANGUAGE(ASM)
# set(ASM_SOURCES
#     startup_stm32h743xx.s
#     )
# set_source_files_properties(${ASM_SOURCES} PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

# # build binary and hex file
# add_executable(${PROJECT_NAME}.elf  ${SOURCES} ${ASM_SOURCES})
# # 如果有需要的库，取消下面的注释，并添加相应的库名称
# # target_link_libraries(${PROJECT_NAME}.elf ${DSP_NAME} m)

# # Build types
# if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
#     message(STATUS "Maximum optimization for speed")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Ofast)
# elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
#     message(STATUS "Maximum optimization for speed, debug info included")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Ofast -g)
# elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
#     message(STATUS "Maximum optimization for size")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Os)
# else ()
#     message(STATUS "Minimal optimization, debug info included")
#     target_compile_options(${PROJECT_NAME}.elf PRIVATE -Og -g -gdwarf-2)
#     add_definitions(-DESC_DEBUG) # ESC Debug
# endif ()

# add_custom_command(
#     TARGET ${PROJECT_NAME}.elf POST_BUILD
#     COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
#     COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin
#     COMMENT "Building hex & bin file..."
#     COMMENT "EXCUTABLE SIZE:"
#     COMMAND ${SIZE} ${PROJECT_NAME}.elf
# )
