#include "ModuleTexture.h"

#include "Globals.h"
#include "DirectXTex.h"
#include <GL/glew.h>


bool ModuleTexture::CleanUp()
{
	return true;
}

TextureInfo ModuleTexture::LoadTexture(std::string const &InPath)
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


	//texture
	unsigned texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	DirectX::TexMetadata metadata = GetMetadata();
	int internalFormat, format, type;
	switch (metadata.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, metadata.width, metadata.height, 0, format, type, GetImage()->GetImage(0, 0, 0)->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	TextureInfo textureOut;
	textureOut.m_FileName = InPath;
	textureOut.m_Texture = texture;


	return textureOut;
}

DirectX::TexMetadata ModuleTexture::GetMetadata()
{
	return m_MetaData;
}

DirectX::ScratchImage *ModuleTexture::GetImage()
{
	return m_Image;
}
