project (crimson)

# Compile external dependencies
include_directories(
        .
        framework
        util
        render
        resource
)

set(SOURCE_FILES
        os/linux/main.c
        framework/entity.h
        framework/component.h
        framework/world.c
        framework/component_manager.c
        framework/entity_manager.c
        framework/world.c
        framework/game_system.c
        system/render_system.c
        system/keyboard_input_system.c
        component/position_component.c
        component/sprite_component.c
        component/keyboard_input_component.c
        resource/resource_manager.c
        util/bitset.c
        util/intrusive_linked_list.c

        assets/character/player.bmp
)

# REQUIRED does not work in CMake <=2.4.6 for SDL
Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED ) # if using SDL_image

# Workaround for the non-working REQUIRED flag
if ( NOT SDL_FOUND )
   message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

link_libraries (
   ${SDL_LIBRARY}
   ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
   SDLmain # Sadly not included in SDL_LIBRARY variable
)


add_executable(crimson ${SOURCE_FILES})

file(COPY ${crimson_SOURCE_DIR}/../assets DESTINATION ${crimson_BINARY_DIR})
