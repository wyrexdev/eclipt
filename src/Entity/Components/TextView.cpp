#include "Entity/Components/TextView.hpp"

namespace Eclipt
{
    namespace Components
    {
        std::map<char, MSDFCharacter> TextView::MSDFCharacters;
        FT_Library TextView::ft;
        bool TextView::isFTInitialized = false;

        TextView::TextView(const std::string &text, const std::string &fontPath,
                           unsigned int fontSize, unsigned int msdfResolution)
            : text(text), fontPath(fontPath), fontSize(fontSize),
              msdfResolution(msdfResolution), textVAO(0), textVBO(0),
              textColor(1.0f, 1.0f, 1.0f, 1.0f)
        {
        }

        float TextView::median(float r, float g, float b)
        {
            return std::max(std::min(r, g), std::min(std::max(r, g), b));
        }

        float TextView::computeDistance(FT_Bitmap *bitmap, int x, int y, int targetX, int targetY)
        {
            if (!bitmap || !bitmap->buffer)
            {
                return std::numeric_limits<float>::max();
            }

            int width = bitmap->width;
            int height = bitmap->rows;
            int pitch = bitmap->pitch;

            if (x < 0 || x >= width || y < 0 || y >= height ||
                targetX < 0 || targetX >= width || targetY < 0 || targetY >= height)
            {
                return std::numeric_limits<float>::max();
            }

            unsigned char sourceValue = bitmap->buffer[std::abs(y * pitch) + x];
            unsigned char targetValue = bitmap->buffer[std::abs(targetY * pitch) + targetX];

            bool sourceInside = sourceValue > 128;
            bool targetInside = targetValue > 128;

            if (sourceInside == targetInside)
            {
                return std::numeric_limits<float>::max();
            }

            int dx = targetX - x;
            int dy = targetY - y;
            return std::sqrt(dx * dx + dy * dy);
        }

        void TextView::findClosestEdge(FT_Bitmap *bitmap, int x, int y, int searchRadius,
                                       int &edgeX, int &edgeY, float &minDistance)
        {
            if (!bitmap || !bitmap->buffer)
            {
                minDistance = std::numeric_limits<float>::max();
                edgeX = edgeY = -1;
                return;
            }

            minDistance = std::numeric_limits<float>::max();
            edgeX = -1;
            edgeY = -1;

            // int width = bitmap->width;
            // int height = bitmap->rows;

            static int debugCount = 0;
            if (debugCount < 5)
            {
                debugCount++;
            }

            for (int dy = -searchRadius; dy <= searchRadius; ++dy)
            {
                for (int dx = -searchRadius; dx <= searchRadius; ++dx)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (dx == 0 && dy == 0)
                        continue;

                    float distance = computeDistance(bitmap, x, y, nx, ny);
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        edgeX = nx;
                        edgeY = ny;
                    }
                }
            }

            if (minDistance == std::numeric_limits<float>::max())
            {
                minDistance = searchRadius;
                edgeX = x;
                edgeY = y;
            }
        }

        void TextView::computeMSDFPixel(FT_Bitmap *bitmap, int x, int y, int outputSize,
                                        unsigned char *outR, unsigned char *outG, unsigned char *outB)
        {
            if (!bitmap || !bitmap->buffer || !outR || !outG || !outB)
            {
                *outR = *outG = *outB = 0;
                return;
            }

            int width = bitmap->width;
            int height = bitmap->rows;
            int pitch = bitmap->pitch;

            static int pixelDebugCount = 0;
            if (pixelDebugCount < 3)
            {
                pixelDebugCount++;
            }

            if (width == 0 || height == 0)
            {
                *outR = *outG = *outB = 128;
                return;
            }

            float scaleX = (float)width / outputSize;
            float scaleY = (float)height / outputSize;

            int srcX = (int)(x * scaleX);
            int srcY = (int)(y * scaleY);

            srcX = std::max(0, std::min(width - 1, srcX));
            srcY = std::max(0, std::min(height - 1, srcY));

            int searchRadius = std::max(2, std::min(8, std::max(width, height) / 16));
            if (searchRadius < 2)
                searchRadius = 2;

            unsigned char pixelValue = bitmap->buffer[std::abs(srcY * pitch) + srcX];
            bool inside = pixelValue > 128;

            int edge1X, edge1Y, edge2X, edge2Y, edge3X, edge3Y;
            float dist1, dist2, dist3;

            findClosestEdge(bitmap, srcX, srcY, searchRadius, edge1X, edge1Y, dist1);
            findClosestEdge(bitmap, srcX + 1, srcY, searchRadius, edge2X, edge2Y, dist2);
            findClosestEdge(bitmap, srcX, srcY + 1, searchRadius, edge3X, edge3Y, dist3);

            float signedDist1 = inside ? dist1 : -dist1;
            float signedDist2 = inside ? dist2 : -dist2;
            float signedDist3 = inside ? dist3 : -dist3;

            float range = (float)searchRadius;
            float r = (signedDist1 / range + 1.0f) / 2.0f;
            float g = (signedDist2 / range + 1.0f) / 2.0f;
            float b = (signedDist3 / range + 1.0f) / 2.0f;

            r = std::max(0.0f, std::min(1.0f, r));
            g = std::max(0.0f, std::min(1.0f, g));
            b = std::max(0.0f, std::min(1.0f, b));

            *outR = (unsigned char)(r * 255);
            *outG = (unsigned char)(g * 255);
            *outB = (unsigned char)(b * 255);

            static int outputDebugCount = 0;
            if (outputDebugCount < 3)
            {
                outputDebugCount++;
            }
        }

        void TextView::generateMSDF(FT_Bitmap *bitmap, unsigned char *output, int outputSize)
        {
            if (!bitmap || !bitmap->buffer || !output)
            {
                std::cout << "❌ ERROR: Invalid parameters in generateMSDF" << std::endl;
                return;
            }

            int totalSize = outputSize * outputSize * 3;

            std::fill(output, output + totalSize, 128);

            int processedPixels = 0;
            for (int y = 0; y < outputSize; ++y)
            {
                for (int x = 0; x < outputSize; ++x)
                {
                    unsigned char r, g, b;
                    computeMSDFPixel(bitmap, x, y, outputSize, &r, &g, &b);

                    int index = (y * outputSize + x) * 3;
                    output[index] = r;
                    output[index + 1] = g;
                    output[index + 2] = b;
                    processedPixels++;
                }
            }
        }

        bool TextView::loadMSDFFont()
        {
            if (!isFTInitialized)
            {
                FT_Error error = FT_Init_FreeType(&ft);
                if (error)
                {
                    std::cout << "ERROR: FT_Init_FreeType failed: " << error << std::endl;
                    return false;
                }
                isFTInitialized = true;
            }

            std::ifstream fontFile(fontPath);
            if (!fontFile.good())
            {
                std::cout << "ERROR: Font file not found: " << fontPath << std::endl;
                return false;
            }
            fontFile.close();

            FT_Face face;
            FT_Error error = FT_New_Face(ft, fontPath.c_str(), 0, &face);
            if (error)
            {
                std::cout << "ERROR: Cannot load font face: " << fontPath << " (error: " << error << ")" << std::endl;
                return false;
            }

            error = FT_Set_Pixel_Sizes(face, 0, 128);
            if (error)
            {
                std::cout << "ERROR: FT_Set_Pixel_Sizes failed: " << error << std::endl;
                FT_Done_Face(face);
                return false;
            }

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            int loadedCount = 0;
            int failedCount = 0;

            for (unsigned char c = 32; c < 127; c++)
            {
                if (FT_Load_Char(face, c, FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL))
                {
                    failedCount++;
                    continue;
                }

                FT_GlyphSlot glyph = face->glyph;
                FT_Bitmap *bitmap = &glyph->bitmap;

                if (c == ' ')
                {
                    int msdfSize = std::max<unsigned int>(1u, msdfResolution / 16);
                    unsigned char *msdfData = new unsigned char[msdfSize * msdfSize * 3];
                    std::fill(msdfData, msdfData + msdfSize * msdfSize * 3, 128);

                    unsigned int texture;
                    glGenTextures(1, &texture);
                    glBindTexture(GL_TEXTURE_2D, texture);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    glTexImage2D(
                        GL_TEXTURE_2D,
                        0,
                        GL_RGB,
                        msdfSize,
                        msdfSize,
                        0,
                        GL_RGB,
                        GL_UNSIGNED_BYTE,
                        msdfData);

                    delete[] msdfData;

                    MSDFCharacter character = {
                        texture,
                        QTX::Ivec2(bitmap->width, bitmap->rows),
                        QTX::Ivec2(glyph->bitmap_left, glyph->bitmap_top),
                        static_cast<unsigned int>(glyph->advance.x),
                        1.0f,
                        QTX::Ivec2(msdfSize, msdfSize)};
                    MSDFCharacters[c] = character;
                    loadedCount++;

                    continue;
                }

                if (!bitmap->buffer || bitmap->width == 0 || bitmap->rows == 0)
                {
                    failedCount++;
                    continue;
                }

                int msdfSize = msdfResolution;
                unsigned char *msdfData = new unsigned char[msdfSize * msdfSize * 3];
                generateMSDF(bitmap, msdfData, msdfSize);

                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RGB,
                    msdfSize,
                    msdfSize,
                    0,
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    msdfData);

                delete[] msdfData;

                MSDFCharacter character = {
                    texture,
                    QTX::Ivec2(bitmap->width, bitmap->rows),
                    QTX::Ivec2(glyph->bitmap_left, glyph->bitmap_top),
                    static_cast<unsigned int>(glyph->advance.x),
                    128.0f / msdfSize,
                    QTX::Ivec2(msdfSize, msdfSize)};
                MSDFCharacters[c] = character;
                loadedCount++;
            }

            FT_Done_Face(face);

            int count = 0;
            for (const auto &pair : MSDFCharacters)
            {
                count++;
            }

            return loadedCount > 0;
        }

        void TextView::onStart()
        {
            if (MSDFCharacters.empty())
            {
                if (!loadMSDFFont())
                {
                    std::cout << "❌ Failed to load MSDF font" << std::endl;
                    return;
                }
            }

            glGenVertexArrays(1, &textVAO);
            glGenBuffers(1, &textVBO);
            glBindVertexArray(textVAO);
            glBindBuffer(GL_ARRAY_BUFFER, textVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void TextView::renderTextMSDF(const std::string &text, float x, float y, float scale)
        {
            if (MSDFCharacters.empty())
            {
                std::cout << "⚠️ No MSDF characters available" << std::endl;
                return;
            }

            glUseProgram(getEntity()->shaderProgram);

            GLint hasTextLoc = glGetUniformLocation(getEntity()->shaderProgram, "hasText");
            GLint textColorLoc = glGetUniformLocation(getEntity()->shaderProgram, "textColor");
            GLint useMSDFLoc = glGetUniformLocation(getEntity()->shaderProgram, "useMSDF");
            GLint msdfRangeLoc = glGetUniformLocation(getEntity()->shaderProgram, "msdfRange");

            if (hasTextLoc != -1)
                glUniform1i(hasTextLoc, 1);
            if (textColorLoc != -1)
                glUniform4f(textColorLoc, 1, 1, 1, 1);
            if (useMSDFLoc != -1)
                glUniform1i(useMSDFLoc, 1);
            if (msdfRangeLoc != -1)
                glUniform1f(msdfRangeLoc, 0.5f);

            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(textVAO);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // float startX = x;
            int renderedChars = 0;

            for (char c : text)
            {
                if (MSDFCharacters.find(c) == MSDFCharacters.end())
                {
                    std::cout << "⚠️ Character not in MSDF map: '" << c << "'" << std::endl;
                    continue;
                }

                MSDFCharacter ch = MSDFCharacters[c];

                float xpos = x + ch.Bearing.getX() * scale;
                float ypos = y - (ch.Size.getY() - ch.Bearing.getY()) * scale;
                float w = ch.Size.getX() * scale * ch.Scale;
                float h = ch.Size.getY() * scale * ch.Scale;

                float vertices[6][4] = {
                    {xpos, ypos + h, 0.0f, 0.0f},
                    {xpos, ypos, 0.0f, 1.0f},
                    {xpos + w, ypos, 1.0f, 1.0f},
                    {xpos, ypos + h, 0.0f, 0.0f},
                    {xpos + w, ypos, 1.0f, 1.0f},
                    {xpos + w, ypos + h, 1.0f, 0.0f}};

                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                glBindBuffer(GL_ARRAY_BUFFER, textVBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glDrawArrays(GL_TRIANGLES, 0, 6);

                x += (ch.Advance >> 6) * 0.002f;
                renderedChars++;
            }

            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);

            if (hasTextLoc != -1)
                glUniform1i(hasTextLoc, 0);
            if (useMSDFLoc != -1)
                glUniform1i(useMSDFLoc, 0);

            static bool firstRender = true;
            if (firstRender)
            {
                firstRender = false;
            }
        }

        void TextView::onRender()
        {
            if (MSDFCharacters.empty())
            {
                onStart();
                if (MSDFCharacters.empty())
                    return;
            }

            renderTextMSDF(text, 0.0f, 0.0f, 0.001f);
        }

        void TextView::setText(const std::string &newText)
        {
            text = newText;
        }

        void TextView::setColor(float r, float g, float b, float a)
        {
            textColor = QTX::Color(r, g, b, a);
        }

        void TextView::setFontSize(unsigned int size)
        {
            fontSize = size;
        }

        void TextView::setMSDFResolution(unsigned int resolution)
        {
            msdfResolution = resolution;

            MSDFCharacters.clear();
            onStart();
        }

        void TextView::cleanup()
        {
            for (auto &pair : MSDFCharacters)
            {
                glDeleteTextures(1, &pair.second.TextureID);
            }
            MSDFCharacters.clear();

            if (textVAO)
                glDeleteVertexArrays(1, &textVAO);
            if (textVBO)
                glDeleteBuffers(1, &textVBO);

            if (isFTInitialized)
            {
                FT_Done_FreeType(ft);
                isFTInitialized = false;
            }
        }
    }
}