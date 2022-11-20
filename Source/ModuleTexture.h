#pragma once
#include "Module.h"
#include <string>
#include "DirectXTex.h"

class ModuleTexture :
    public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	//update_status PreUpdate();
	update_status Update();
	//update_status PostUpdate();
	bool CleanUp();

	void LoadTexture(std::string const &InPath);
	DirectX::TexMetadata GetMetadata();

	DirectX::ScratchImage *GetImage();

private:
	DirectX::TexMetadata m_MetaData;
	DirectX::ScratchImage *m_Image;
};

