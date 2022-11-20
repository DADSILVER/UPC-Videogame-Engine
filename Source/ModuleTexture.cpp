#include "ModuleTexture.h"

#include "Globals.h"
#include "DirectXTex.h"

ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init()
{
	
    //LoadTexture("Test-image-Baboon.ppm");
	if (m_Image) 
	{
		//DirectX::FlipRotate(*m_Image->GetImages(), DirectX::TEX_FR_FLIP_VERTICAL, *m_Image);
	}
	
    return true;
}

update_status ModuleTexture::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	return true;
}

void ModuleTexture::LoadTexture(std::string const &InPath)
{
	m_Image = new DirectX::ScratchImage;
	DirectX::ScratchImage *NotFlip = new DirectX::ScratchImage;
    HRESULT loadResult;
    std::string extension = InPath.substr(InPath.size() - 4, 4);
    std::wstring widePath = std::wstring(InPath.begin(), InPath.end());

	if (extension == ".dds")
	{
		loadResult = LoadFromDDSFile(widePath.c_str(), DirectX::DDS_FLAGS_NONE, &m_MetaData, *NotFlip);
		if (FAILED(loadResult))
		{
			engLOG("Material convertor error : DDS texture loading failed (\%s)", InPath);
			NotFlip = nullptr;
		}
	}
	else if (extension == ".tga")
	{
		loadResult = DirectX::LoadFromTGAFile(widePath.c_str(), &m_MetaData, *NotFlip);
		if (FAILED(loadResult))
		{
			engLOG("Material convertor error : DDS texture loading failed (\%s)", InPath);
			NotFlip = nullptr;
		}
	}
	else
	{
		loadResult = LoadFromWICFile(widePath.c_str(), DirectX::WIC_FLAGS_DEFAULT_SRGB, &m_MetaData, *NotFlip);
		if (FAILED(loadResult))
		{
			engLOG("Material convertor error : DDS texture loading failed (\%s)", InPath);
			NotFlip = nullptr;
		}
	}
	DirectX::FlipRotate(NotFlip->GetImages(), NotFlip->GetImageCount(), NotFlip->GetMetadata(), DirectX::TEX_FR_FLIP_VERTICAL, *m_Image);
}

DirectX::TexMetadata ModuleTexture::GetMetadata()
{
	return m_MetaData;
}

DirectX::ScratchImage *ModuleTexture::GetImage()
{
	return m_Image;
}
