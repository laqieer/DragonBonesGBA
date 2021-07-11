#include <tonc.h>

#include <cstring>

#include "gbfs.h"

#include "Texture.hpp"

namespace gba
{
    Texture* Texture::gTextures[4] = { NULL };

    Texture::Texture(std::string filename)
    {
        name = filename;

        for(id = 0; id < 4 && gTextures[id]; id++);
        if(id < 4)
            loadFromFile(filename);
    }

    Texture::~Texture()
    {
        if(id < 4)
            gTextures[id] = NULL;
    }

    bool Texture::loadFromFile(std::string filename)
    {
        const GBFS_FILE *dat = find_first_gbfs_file((const void *)(&find_first_gbfs_file));
        const char *fp = (const char *)gbfs_get_obj(dat, filename.c_str(), NULL);
        
        name = filename;
        raw = &tile_mem_obj[0][256 * id];
        pal = &pal_obj_bank[id];
        size.x = 256;
        size.y = 64;

        memcpy(pal, fp, 32);
        LZ77UnCompVram(fp + 32, raw);

        gTextures[id] = this;

        return true; 
    }
}
