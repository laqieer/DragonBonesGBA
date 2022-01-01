#include <tonc.h>

#include "tonc_mgba.h"

#include "Sprite.hpp"

namespace gba
{
    Sprite* Sprite::sprites[32] = { NULL };

    Sprite::Sprite(Texture *texture, IntRect *rectangle, Vector2f *origin)
    {
        for(id = 0; id < 32 && sprites[id]; id++);
        if(id < 32)
        {
            tex = texture;
            rect = rectangle;
            ori = origin;
            sprites[id] = this;
        }
        mgba_printf(LOG_INFO, "Sprite: id: %d, texture: 0x%x", id, texture);
    }

    Sprite::Sprite(Texture *texture, IntRect *rectangle)
    {
        for(id = 0; id < 32 && sprites[id]; id++);
        if(id < 32)
        {
            tex = texture;
            rect = rectangle;
            ori = new Vector2f();
            sprites[id] = this;
        }
        mgba_printf(LOG_INFO, "Sprite: id: %d, texture: 0x%x", id, texture);
    }

    Sprite::Sprite(Texture *texture)
    {
        for(id = 0; id < 32 && sprites[id]; id++);
        if(id < 32)
        {
            tex = texture;
            rect = new IntRect(0, 0, 64, 64);
            ori = new Vector2f();
            sprites[id] = this;
        }
        mgba_printf(LOG_INFO, "Sprite: id: %d, texture: 0x%x", id, texture);
    }

    Sprite::~Sprite()
    {
        if(id < 32)
            sprites[id] = NULL;
    }

    void Sprite::setOrigin(float x, float y)
    {
        //FIXME: convert pivot to origin
        mgba_printf(LOG_INFO, "setOrigin: pivotX: %.2f, pivotY: %.2f", x, y);
        //ori->x = rect->getSize().x * (x + 0.5);
        //ori->y = rect->getSize().y * (y + 0.5);
        ori->x = x;
        ori->y = y;
    }

    void Sprite::draw(dragonBones::Transform *transform)
    {
        OBJ_ATTR obj;

        mgba_printf(LOG_INFO, "draw: w %d, h: %d, x: %.2f, y: %.2f, origin: (%.2f, %.2f), rotation: %.2f, scaleX: %.2f, scaleY: %.2f", rect->getSize().x, rect->getSize().y, transform->x, transform->y, ori->x, ori->y, transform->rotation, transform->scaleX, transform->scaleY);

        switch (rect->getSize().y + 100 * rect->getSize().x)
        {
            case 808:
                obj.attr1 = ATTR1_SIZE_8x8;
                obj.attr0 = ATTR0_SQUARE;
                break;
            case 1616:
                obj.attr1 = ATTR1_SIZE_16x16;
                obj.attr0 = ATTR0_SQUARE;
                break;
            case 3232:
                obj.attr1 = ATTR1_SIZE_32x32;
                obj.attr0 = ATTR0_SQUARE;
                break;
            case 6464:
                obj.attr1 = ATTR1_SIZE_64x64;
                obj.attr0 = ATTR0_SQUARE;
                break;
            case 816:
                obj.attr1 = ATTR1_SIZE_8x16;
                obj.attr0 = ATTR0_TALL;
                break;
            case 832:
                obj.attr1 = ATTR1_SIZE_8x32;
                obj.attr0 = ATTR0_TALL;
                break;
            case 1632:
                obj.attr1 = ATTR1_SIZE_16x32;
                obj.attr0 = ATTR0_TALL;
                break;
            case 3264:
                obj.attr1 = ATTR1_SIZE_32x64;
                obj.attr0 = ATTR0_TALL;
                break;
            case 168:
                obj.attr1 = ATTR1_SIZE_16x8;
                obj.attr0 = ATTR0_WIDE;
                break;
            case 328:
                obj.attr1 = ATTR1_SIZE_32x8;
                obj.attr0 = ATTR0_WIDE;
                break;
            case 3216:
                obj.attr1 = ATTR1_SIZE_32x16;
                obj.attr0 = ATTR0_WIDE;
                break;
            case 6416:
            case 6432:
                obj.attr1 = ATTR1_SIZE_64x32;
                obj.attr0 = ATTR0_WIDE;
                break;
            default:
                return;
        }

        obj.attr2 = ATTR2_BUILD(256 * tex->id + 32 * rect->getPosition().y / 8 + rect->getPosition().x / 8, tex->id, 0);

        if(transform->rotation == 0.0f && transform->scaleX == 1.0f && transform->scaleY == 1.0f)
        {
            obj.attr0 |= ATTR0_REG;
            obj_set_pos(&obj, (int)transform->x, (int)transform->y);
        }
        else
        {
            //if (rect->getSize().x == rect->getSize().y || ((transform->rotation < 0.25) && (transform->rotation > -0.25)))
            //{
            //    obj.attr0 |= ATTR0_AFF;
            //}
            //else
            {
                obj.attr0 |= ATTR0_AFF_DBL;
            }

             obj.attr1 |= ATTR1_AFF_ID(id);

            s16 sx = 256 / transform->scaleX;
            s16 sy = 256 / transform->scaleY;
            u16 alpha = (transform->rotation + (transform->rotation < 0? dragonBones::Transform::PI_D : 0)) * 0xffff / dragonBones::Transform::PI_D;
            AFF_SRC_EX asx = {ori->x * 256, ori->y * 256, (s16)transform->x, (s16)transform->y, sx, sy, alpha};
            obj_rotscale_ex(&obj, &obj_aff_mem[id], &asx);
        }

        obj.attr2 |= ATTR2_PRIO(1);
        obj.fill = obj_mem[id].fill;
        oam_copy(&obj_mem[id], &obj, 1);
    }
}
