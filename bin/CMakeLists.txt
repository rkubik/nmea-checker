add_definitions( -Wall -ggdb -std=c++11 -D_FORTIFY_SOURCE=2 -O2 -fstack-protector-strong -Wformat -Werror=format-security )

include_directories(
    .
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
)

set( SOURCES
    ${PROJECT_SOURCE_DIR}/src/nmea_checker.cc
    ${PROJECT_SOURCE_DIR}/src/nmea_streamer.cc
    ${PROJECT_SOURCE_DIR}/src/basic_command.cc
    ${PROJECT_SOURCE_DIR}/src/valid_command.cc
    ${PROJECT_SOURCE_DIR}/src/checksum_command.cc
    ${PROJECT_SOURCE_DIR}/src/file_reader.cc
    ${PROJECT_SOURCE_DIR}/src/serial_reader.cc
    ${PROJECT_SOURCE_DIR}/src/string_reader.cc
    ${PROJECT_SOURCE_DIR}/src/utils.cc
    ${PROJECT_SOURCE_DIR}/src/minimea.cc
)

add_executable( nmea-checker ${SOURCES} )

target_link_libraries( nmea-checker -lboost_program_options )

install( TARGETS nmea-checker RUNTIME DESTINATION usr/bin )
