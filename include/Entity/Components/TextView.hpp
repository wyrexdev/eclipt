#pragma once

#include "Headers/Headers.hpp"
#include "Entity/Component/Component.hpp"
#include "QTX/Ivecs/Ivec2.hpp"

namespace Eclipt
{
    struct MSDFCharacter 
    {
        unsigned int TextureID;
        QTX::Ivec2 Size;
        QTX::Ivec2 Bearing;
        unsigned int Advance;
        float Scale;
        QTX::Ivec2 TextureSize;
    };

    class TextView : public Component
    {
    private:
        std::string text;
        std::string fontPath;
        unsigned int fontSize;
        unsigned int msdfResolution;
        
        QTX::Color textColor;
        unsigned int textVAO, textVBO;
        
        static std::map<char, MSDFCharacter> MSDFCharacters;
        static FT_Library ft;
        static bool isFTInitialized;
        
        void generateMSDF(FT_Bitmap* bitmap, unsigned char* output, int outputSize);
        void computeMSDFPixel(FT_Bitmap* bitmap, int x, int y, int outputSize, 
                             unsigned char* outR, unsigned char* outG, unsigned char* outB);
        float median(float r, float g, float b);
        
        float computeDistance(FT_Bitmap* bitmap, int x, int y, int targetX, int targetY);
        void findClosestEdge(FT_Bitmap* bitmap, int x, int y, int searchRadius,
                            int& edgeX, int& edgeY, float& minDistance);
        
    public:
        TextView(const std::string &text = "Hello World", 
                const std::string &fontPath = "fonts/nunito.ttf", 
                unsigned int fontSize = 48,
                unsigned int msdfResolution = 64);
        
        void onStart() override;
        void onRender() override;
        
        void setText(const std::string &newText);
        void setColor(float r, float g, float b, float a = 1.0f);
        void setFontSize(unsigned int size);
        void setMSDFResolution(unsigned int resolution);
        
        void renderTextMSDF(const std::string &text, float x, float y, float scale);
        
        bool loadMSDFFont();
        void cleanup();
    };
}