#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "Vector2.hpp"

namespace gba
{
    class Texture
    {
        public:
            static Texture *textures[4];

            std::string name;
            int id;
            void *raw;
            void *pal;
            Vector2u size;

            Texture(std::string filename);
            ~Texture();

            bool loadFromFile(std::string filename);
    };
}

#endif /* TEXTURE_HPP */
