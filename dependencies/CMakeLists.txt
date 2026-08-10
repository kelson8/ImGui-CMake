cmake_minimum_required(VERSION 3.22)

include(FetchContent)

# This is the CMakeLists file that the ImGui program will use to fetch external dependencies.

#-------------
# Fmt
#-------------

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        12.2.0
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(fmt)
# ------------------------------------------------------------------------------

#-------------
# Spdlog
#-------------

# TODO Fix this to work.
# FetchContent_Declare(
#     spdlog
#     GIT_REPOSITORY https://github.com/gabime/spdlog.git
#     GIT_TAG        v1.17.0
# )
# FetchContent_MakeAvailable(spdlog)
