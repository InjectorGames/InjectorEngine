project(SDL_net LANGUAGES C)

add_library(SDL_net STATIC
    ${PROJECT_SOURCE_DIR}/3rdparty/SDL_net/SDLnet.c
    ${PROJECT_SOURCE_DIR}/3rdparty/SDL_net/SDLnetselect.c
    ${PROJECT_SOURCE_DIR}/3rdparty/SDL_net/SDLnetTCP.c
    ${PROJECT_SOURCE_DIR}/3rdparty/SDL_net/SDLnetUDP.c
)
target_link_libraries(SDL_net PUBLIC 
    SDL2main
	SDL2-static
)
target_include_directories(SDL_net PUBLIC
    ${PROJECT_SOURCE_DIR}/3rdparty/SDL_net
    ${PROJECT_SOURCE_DIR}/3rdparty/SDL/include
)
