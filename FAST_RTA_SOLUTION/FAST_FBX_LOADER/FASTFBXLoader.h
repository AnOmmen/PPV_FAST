#pragma once

#ifdef FASTFBXLOADER_EXPORTS
#define FASTFBXLOADER_API __declspec(dllexport)
#else
#define FASTFBXLOADER_API __declspec(dllimport)
#endif

#include <vector>

struct XMFLOAT3;


namespace FASTFBXLoader
{
	class FBXLoader
	{
	public:
		
	};
}