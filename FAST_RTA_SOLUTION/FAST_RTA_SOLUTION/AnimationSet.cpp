#include "AnimationSet.h"
#include "BindPose.h"
#include "../FAST_BINARY_IO/FASTBinaryIO.h"


AnimationSet::AnimationSet() : m_bindPose(nullptr), m_defaultAnim(NULL)
{
}


AnimationSet::~AnimationSet()
{
}

#define HEADER_SIZE			16
#define INDICES_PER_TRI		3
bool AnimationSet::LoadAnimationFile(const char *_filePath, unsigned short *_indices, unsigned long &_indexCount,
	FullVertex *_vertices, unsigned long &_vertexCount)
{
	FASTBinaryIO::FASTFile *fastFile = FASTBinaryIO::Create(FASTBinaryIO::READ);
	if (FASTBinaryIO::Open(fastFile, _filePath))
	{
		char *header;
		unsigned long read;
		if (FASTBinaryIO::ReadTo(fastFile, HEADER_SIZE, &header, read))
		{
			char *block;
			unsigned long toRead = (*(unsigned long*)&header[0] * INDICES_PER_TRI * sizeof(unsigned short)) +
				(*(unsigned long*)&header[4] * sizeof(FullVertex)) +
				(*(unsigned long*)&header[8] * sizeof(DirectX::XMFLOAT4X4));
			if (m_bindPose)
				FASTBinaryIO::Move(fastFile, toRead);
			else
			{
				if (!FASTBinaryIO::ReadTo(fastFile, toRead, &block, read))
					return false;
			}
		}
	}

	return false;
}

unsigned int AnimationSet::GetAnimationCount() const
{
	return m_animations.size();
}

const Animation * AnimationSet::GetAnimation(int _key) const
{
	if (_key < m_animations.size())
		return &m_animations[_key];
	return nullptr;
}

const BlendInfo * AnimationSet::GetBlendInfo(int _animationFrom, int _animationTo)
{
	return nullptr;
}

const BindPose * AnimationSet::GetBindPose() const
{
	return m_bindPose;
}

const Animation * AnimationSet::GetDefaultAnimation()
{
	return nullptr;
}
