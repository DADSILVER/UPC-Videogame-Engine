#pragma once
#include "Module.h"
#include <string>
#include "DirectXTex.h"

struct TextureInfo
{
	std::string m_FileName = "";
	unsigned m_Texture = 0;
};


class ModuleTexture :
    public Module
{
public:
	bool CleanUp();

	bool LoadTexture(TextureInfo& InOutTextureInfo);
	DirectX::ScratchImage* GetImage();

private:
	
	DirectX::ScratchImage *m_Image;

};

