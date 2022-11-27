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

	TextureInfo LoadTexture(std::string const &InPath);
	DirectX::TexMetadata GetMetadata();
	DirectX::ScratchImage *GetImage();

private:
	DirectX::TexMetadata m_MetaData;
	DirectX::ScratchImage *m_Image;

};

