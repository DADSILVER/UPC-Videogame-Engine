#include "ModuleTexture.h"

#include "Globals.h"
#include "DirectXTex.h"
#include <GL/glew.h>

#include "Application.h"

#include "ModuleEditor.h"

bool ModuleTexture::CleanUp()
{
	delete m_Image;
	return true;
}

bool ModuleTexture::LoadTexture(TextureInfo &InOutTextureInfo)
{
	m_Image = new DirectX::ScratchImage;
	DirectX::ScratchImage *NotFlip = new DirectX::ScratchImage;
    HRESULT loadResult;
    std::string extension = InOutTextureInfo.m_FileName.substr(InOutTextureInfo.m_FileName.size() - 4, 4);
    std::wstring widePath = std::wstring(InOutTextureInfo.m_FileName.begin(), InOutTextureInfo.m_FileName.end());
	std::string name = InOutTextureInfo.m_FileName;


	App->m_Editor->m_Console->AddLog(engLOG("Trying load material texture from %s.\n", name.c_str()));

	if (extension == ".dds")
	{
		loadResult = LoadFromDDSFile(widePath.c_str(), DirectX::DDS_FLAGS_NONE, NULL, *NotFlip);
		if (FAILED(loadResult))
		{
			App->m_Editor->m_Console->AddLog(engLOG("Material convertor error : DDS texture loading failed (\%s)", name.c_str()));
			NotFlip = nullptr;
			return 0;
		}
	}
	else if (extension == ".tga")
	{
		loadResult = DirectX::LoadFromTGAFile(widePath.c_str(), NULL, *NotFlip);
		if (FAILED(loadResult))
		{
			App->m_Editor->m_Console->AddLog(engLOG("Material convertor error : TGA texture loading failed (\%s)", name.c_str()));
			NotFlip = nullptr;
			return 0;
		}
	}
	else
	{
		loadResult = LoadFromWICFile(widePath.c_str(), DirectX::WIC_FLAGS_DEFAULT_SRGB, NULL, *NotFlip);
		if (FAILED(loadResult))
		{
			App->m_Editor->m_Console->AddLog(engLOG("Material convertor error : WIC texture loading failed (\%s)", name.c_str()));
			NotFlip = nullptr;
			return 0;
		}
	}
	DirectX::FlipRotate(NotFlip->GetImages(), NotFlip->GetImageCount(), NotFlip->GetMetadata(), DirectX::TEX_FR_FLIP_VERTICAL, *m_Image);

	delete NotFlip;
	//texture
	unsigned texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	DirectX::TexMetadata metadata = m_Image->GetMetadata();
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
		App->m_Editor->m_Console->AddLog(engLOG("Unsupported format\n"));
		return 0;
		//assert(false && "Unsupported format");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, metadata.width, metadata.height, 0, format, type, GetImage()->GetImage(0, 0, 0)->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	App->m_Editor->m_Console->AddLog(engLOG("Material texture load from %s.\n", name.c_str()));
	InOutTextureInfo.m_Texture = texture;


	return 1;
}

DirectX::ScratchImage* ModuleTexture::GetImage()
{
	return m_Image;
}
