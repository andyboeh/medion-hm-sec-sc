CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_CROSSCOMPILING 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
SET(CMAKE_C_COMPILER sdcc)

SET(CMAKE_OBJCOPY stm8-objcopy)

SET(PROJECT_NAME medion-hm-sec-sc)
PROJECT(${PROJECT_NAME} C)


SET(CMAKE_VERBOSE_MAKEFILE TRUE)

# here is the target environment is located
#SET(CMAKE_FIND_ROOT_PATH  /usr/share/sdcc)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

message(STATUS "Cross-compiling with the sdcc toolchain")

SET(CMAKE_C_FLAGS "-mstm8 --opt-code-size --std-sdcc99 --nogcse --fverbose-asm --float-reent -DCONSTMEM=const --debug --all-callee-saves --verbose --stack-auto --no-peep")


#link_directories(
#    ${NRF_GCC}
#    )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin
    ${CMAKE_CURRENT_SOURCE_DIR}/radio
    ${CMAKE_CURRENT_SOURCE_DIR}/timer
    ${CMAKE_CURRENT_SOURCE_DIR}/spi
    ${CMAKE_CURRENT_SOURCE_DIR}/led
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(SOURCES
    main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/led/led_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/led/led_on.c
    ${CMAKE_CURRENT_SOURCE_DIR}/led/led_off.c
    ${CMAKE_CURRENT_SOURCE_DIR}/led/led_toggle.c
    ${CMAKE_CURRENT_SOURCE_DIR}/crc16.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_config_end.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_config_start.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_config_write.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_decode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_encode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_handle_packet.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_listen.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_poll.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_send.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_send_contact_state.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_send_device_info.c
    ${CMAKE_CURRENT_SOURCE_DIR}/asksin/as_send_status.c
    ${CMAKE_CURRENT_SOURCE_DIR}/battery/measure_battery.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_deinit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_enter_receive.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_poll.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_read_burst.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_read_reg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_read_status.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_read_int.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_receive.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_received.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_send.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_sent.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_switch_100k.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_wait.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_wait_int.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_white.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_write_burst.c
    ${CMAKE_CURRENT_SOURCE_DIR}/radio/radio_write_reg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/spi/spi_disable.c
    ${CMAKE_CURRENT_SOURCE_DIR}/spi/spi_enable.c
    ${CMAKE_CURRENT_SOURCE_DIR}/spi/spi_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/spi/spi_send_byte.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timer/clear_timeout.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timer/get_tick.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timer/set_timeout.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timer/tick_deinit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timer/tick_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timer/wait_timeout.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timer/set_singleshot_timer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/timer/clear_singleshot_timer.c
    )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/flash.sh.in ${CMAKE_CURRENT_SOURCE_DIR}/flash.sh @ONLY)
file(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/flash.sh
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    )

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS
        "--out-fmt-ihx --code-loc 0x8000"
)

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
                   ${CMAKE_OBJCOPY} -I ihex ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.ihx -O binary ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin
                  )

#ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
#                   ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/flash.sh ${CMAKE_CURRENT_BINARY_DIR}/flash.sh)

#ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND
#                   ${CMAKE_OBJCOPY} -S -O binary
#                   ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)


