import os

sdl_def = ["EXPORTS"]

with open("SDL2.def", "r") as file:
    for line in file.readlines():
        for word in line.split():
            if "SDL_" in word:
                sdl_def.append(word)

with open('SDL2.def', 'w+') as file:
    for definition in sdl_def:
        file.write(definition + '\n')


