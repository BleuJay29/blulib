namespace Blu {
    Sprite::Sprite(const char* filename) {
        if (filename != (const char*)-1) {
            unsigned char* imageData = stbi_load(filename, &width, &height, 0, 4);
            if (imageData) {
                data.assign(imageData, imageData + (width * height * 4));
                stbi_image_free(imageData);
            }
        }
    }

    void Sprite::load(const char* filename) {
        unsigned char* imageData = stbi_load(filename, &width, &height, 0, 4);
        if (imageData) {
            data.assign(imageData, imageData + (width * height * 4));
            stbi_image_free(imageData);
        }
    }

    void Sprite::resize(int newWidth, int newHeight) {
        width = newWidth;
        height = newHeight;
    }

    void Sprite::draw(Spot pos) {
        Convert();
        gra->bmp(dbmp, { pos.x, pos.y, width, height });
    }

    Sprite::~Sprite() {
        if (dbmp) dbmp->Release();
    }

    void Sprite::Convert() {
        D2D1_BITMAP_PROPERTIES bitmapProperties;
        bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        bitmapProperties.dpiX = 96.0f;
        bitmapProperties.dpiY = 96.0f;
        gra->renderTarget->CreateBitmap(
            D2D1::SizeU(width, height),
            data.data(),
            width * 4,
            &bitmapProperties,
            &dbmp
        );
    }
    struct Font {
        stbtt_fontinfo info;
        int ascent;
        int descent;
        int lineGap;
    };
    Font LoadFont(const char* filepath) {
        Font font;
        std::ifstream file(filepath, std::ios::binary | std::ios::ate);
        size_t fileSize = file.tellg();
        unsigned char* ttfBuffer = new unsigned char[fileSize];
        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char*>(ttfBuffer), fileSize);
        file.close();

        stbtt_InitFont(&font.info, ttfBuffer, stbtt_GetFontOffsetForIndex(ttfBuffer, 0));
        stbtt_GetFontVMetrics(&font.info, &font.ascent, &font.descent, &font.lineGap);
        return font;
    }

    void DrawWords(std::string text, int fontsize, Spot center, Font font, int color) {
        float scale = stbtt_ScaleForPixelHeight(&font.info, fontsize);
        std::vector<Sprite> sprites = {};
        Spot size = { 0, 0 };
        for (auto p : text) {
            int x1, y1, x2, y2;
            stbtt_GetCodepointBitmapBox(&font.info, p, scale, scale, &x1, &y1, &x2, &y2);
            int w = x2 - x1;
            int h = y2 - y1;
            std::vector<uint8_t> bitmap(w * h);
            stbtt_MakeCodepointBitmap(&font.info, bitmap.data(), w, h, w, scale, scale, p);
            if (p == ' ') { w = 20 * fontsize / 80; h = 1; };
            Sprite sprite;
            sprite.width = w;
            sprite.height = h;
            sprite.data.resize(w * h * 4);
            size.x += w + 2 * fontsize / 80;
            if (size.y < h) { size.y = h; }
            for (int i = 0; i < bitmap.size(); i++) {
                if (bitmap[i] > 150) { sprite.data[i * 4 + 3] = 255; }
                else { sprite.data[i * 4 + 3] = 0; }
                sprite.data[i * 4 + 2] = (color)&bitmap[i];
                sprite.data[i * 4 + 1] = (color >> 8) & bitmap[i];
                sprite.data[i * 4] = (color >> 16) & bitmap[i];
            }
            sprites.push_back(sprite);
        }
        Spot pos = { (int)(center.x - size.x / 2), (int)(center.y - size.y / 2) };
        int xOffset = pos.x;
        for (auto sprite : sprites) {
            sprite.draw({ xOffset, pos.y + size.y - sprite.height });
            xOffset += sprite.width + 2 * fontsize / 80;
        }
    }
}