file(GLOB_RECURSE async_login_SRCS *.cpp *.h)

set(async_login_SRCS
    ${async_login_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(async_login SHARED ${async_login_SRCS})


target_link_libraries(async_login
    # Link to Cutelyst
    Cutelyst::Core
    Cutelyst::Session
    Cutelyst::Authentication
    Qt5::Core
    Qt5::Network

    # Link to ASql
    ASqlQt5::Core
    ASqlQt5::Pg
)

