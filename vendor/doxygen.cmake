find_package(Doxygen REQUIRED)

FetchContent_Declare(
    doxygen-awesome-css
    GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
    GIT_TAG v2.3.4
)
FetchContent_MakeAvailable(doxygen-awesome-css)
