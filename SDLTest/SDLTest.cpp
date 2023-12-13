// SDLTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "SDL.h"


int main(int argc, char *argv[])
{
    const int w = 800;
    const int h = 600;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        return -1;
    }

    auto windows = SDL_CreateWindow("window"
        , SDL_WINDOWPOS_CENTERED
        , SDL_WINDOWPOS_CENTERED
        , w
        , h
        , SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!windows) {
        return -2;
    }

    auto renderer = SDL_CreateRenderer(windows, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        return -3;
    }

    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA4444, SDL_TEXTUREACCESS_STREAMING, w, h);
    if (!texture) {
        return -4;
    }

    std::shared_ptr<unsigned char > pixels(new unsigned char[w * h * 4]);
    unsigned char *p = pixels.get();
    unsigned char tmp = 255;
    while (1) {
        SDL_Event evt;
        SDL_WaitEventTimeout(&evt, 10);
        if (evt.type == SDL_QUIT) {
            SDL_DestroyWindow(windows);
            break;
        }

        for (int i = 0; i < h; i++) {
            int b = i * w * 4;  // 每一行的起始字节处

            for (int j = 0; j < w * 4; j += 4) {
                p[b + j] = 0;        // B
                p[b + j + 1] = 0;    // G
                p[b + j + 2] = tmp;  // R
                p[b + j + 3] = 0;    // A
            }
        }
        tmp--;
        SDL_UpdateTexture(texture, NULL, p, w * 4);
        SDL_RenderClear(renderer);
        SDL_Rect dst;

        dst.x = 0;
        dst.y = 0;
        dst.w = w;
        dst.h = h;

        SDL_RenderCopy(renderer, texture, nullptr, &dst);

        SDL_RenderPresent(renderer);

    }

    auto a = getchar();

    return 0;
}
