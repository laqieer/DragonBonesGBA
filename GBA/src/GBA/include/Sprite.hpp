#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Vector2.hpp"
#include "Rect.hpp"
#include <dragonBones/geom/Transform.h>
#include "Texture.hpp"

namespace gba
{
    class Sprite
    {
        public:
            static Sprite *sprites[32];

            Texture *tex;
            IntRect *rect;
            Vector2f *ori;
            int id;

            Sprite(Texture *texture);
            Sprite(Texture *texture, IntRect *rectangle);
            Sprite(Texture *texture, IntRect *rectangle, Vector2f *origin);
            ~Sprite();

            void setOrigin(float x, float y);
            void draw(dragonBones::Transform *transform);
    };
}

#endif /* SPRITE_HPP */
