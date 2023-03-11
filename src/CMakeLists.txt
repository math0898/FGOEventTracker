add_executable(fgo-event-planner main.cpp color_codes.hpp event.cpp event.hpp mission.cpp mission.hpp)

install(TARGETS fgo-event-planner DESTINATION bin)
