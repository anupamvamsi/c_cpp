#include "Screen.hpp"

#include <SDL2/SDL.h>

#include <iostream>

namespace pfe {

Screen::Screen()
    : m_window{nullptr},
      m_renderer{nullptr},
      m_texture{nullptr},
      m_buffer{nullptr} {}

bool Screen::Init() {
  bool success = true, error = false;

  // Init
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL Init failed. SDL Error: " << SDL_GetError() << std::endl;
    return error;
  }

  // Window
  m_window = SDL_CreateWindow("Particle Fire Explosion!",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (m_window == nullptr) {
    std::cout << "SDL Window unable to initialize. SDL Error: "
              << SDL_GetError() << std::endl;
    return error;
  }

  // Renderer
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (m_renderer == nullptr) {  // bug was doing assignment instead of "=="
    std::cout << "Could not create the renderer. SDL Error: " << SDL_GetError()
              << std::endl;
    return error;
  }

  // Texture
  m_texture =
      SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (m_texture == nullptr) {  // bug was here, doing assignment instead of "=="
    std::cout << "Could not create the texture. SDL Error: " << SDL_GetError()
              << std::endl;
    return error;
  }

  // Array of screen pixels stored in a buffer (w x h)
  m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
  /*  FUTURE WORK:

      ADD AN EXCEPTION FOR ERROR HANDLING
      IN THE CASE MEMORY ALLOCATION
      THROUGH "new" ISN'T WORKING.
  */

  // Set the memory of the buffer
  memset(m_buffer, 0x128, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

  for (int i{0}; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
    m_buffer[i] = 0xFFFF0000;  // set each pixel
  }

  // Pitch = The number of bytes b/w rows of pixel data (w x sizeof(Uint32))
  SDL_UpdateTexture(m_texture, nullptr, m_buffer,
                    SCREEN_WIDTH * sizeof(Uint32));
  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
  SDL_RenderPresent(m_renderer);

  return success;
}

bool Screen::ProcessEvent() {
  // Event
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false;
    }
  }

  return true;
}

void Screen::Close() {
  delete[] m_buffer;
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyTexture(m_texture);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

}  // namespace pfe
