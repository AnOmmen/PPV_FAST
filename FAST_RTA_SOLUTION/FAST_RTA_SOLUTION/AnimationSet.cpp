#include "AnimationSet.h"
#include "BindPose.h"
#include "../FAST_BINARY_IO/FASTBinaryIO.h"


AnimationSet::AnimationSet() : m_bindPose(nullptr), m_defaultAnim(NULL)
{
}


AnimationSet::~AnimationSet()
{
	delete m_bindPose;
}

#define HEADER_SIZE			16
#define INDICES_PER_TRI		3
#define TRIANGLE_COUNT		0
#define VERTEX_COUNT		1
#define BONE_COUNT			2
#define KEYFRAME_COUNT		3
bool AnimationSet::LoadAnimationFile(const char *_filePath, unsigned short **_indices, unsigned long *_indexCount,
	FullVertex **_vertices, unsigned long *_vertexCount)
{
	FASTBinaryIO::FASTFile *fastFile = FASTBinaryIO::Create(FASTBinaryIO::READ);
	if (FASTBinaryIO::Open(fastFile, _filePath))
	{
		unsigned long *header;
		unsigned long read;
		if (FASTBinaryIO::ReadTo(fastFile, HEADER_SIZE, (char**)&header, read))
		{
			char *block;
			unsigned long toRead = (header[TRIANGLE_COUNT] * INDICES_PER_TRI * sizeof(unsigned short)) +
				(header[VERTEX_COUNT] * sizeof(FullVertex)) +
				(header[BONE_COUNT] * sizeof(DirectX::XMFLOAT4X4));

			if (m_bindPose)
				FASTBinaryIO::Move(fastFile, toRead);
			else
			{
				if (!FASTBinaryIO::ReadTo(fastFile, toRead, &block, read))
				{
					FASTBinaryIO::Close(fastFile);
					FASTBinaryIO::Destroy(fastFile);
					return false;
				}

				if (!_indexCount)
				{
					FASTBinaryIO::Close(fastFile);
					FASTBinaryIO::Destroy(fastFile);
					return false;
				}
				*_indexCount = header[TRIANGLE_COUNT] * INDICES_PER_TRI;

				if (!_indices)
				{
					FASTBinaryIO::Close(fastFile);
					FASTBinaryIO::Destroy(fastFile);
					return false;
				}
				*_indices = new unsigned short[*_indexCount];
				unsigned long size = *_indexCount * sizeof(unsigned short);
				memcpy_s(*_indices, size, block, size);

				if (!_vertexCount)
				{
					FASTBinaryIO::Close(fastFile);
					FASTBinaryIO::Destroy(fastFile);
					return false;
				}
				*_vertexCount = header[VERTEX_COUNT];

				if (!_vertices)
				{
					FASTBinaryIO::Close(fastFile);
					FASTBinaryIO::Destroy(fastFile);
					return false;
				}
				*_vertices = new FullVertex[*_vertexCount];
				size = *_vertexCount * sizeof(FullVertex);
				memcpy_s(*_vertices, size, &block[*_indexCount * sizeof(unsigned short)], size);

				m_bindPose = new BindPose;
				m_bindPose->init(
					header[BONE_COUNT],
					(DirectX::XMFLOAT4X4*)&block[(*_indexCount * sizeof(unsigned short)) + (*_vertexCount * sizeof(FullVertex))]
				);

				delete[] block;
			}
			
			toRead = (sizeof(float) + sizeof(DirectX::XMFLOAT4X4) * header[BONE_COUNT]) * header[KEYFRAME_COUNT];
			if (FASTBinaryIO::ReadTo(fastFile, toRead, &block, read))
			{
				std::vector<KeyFrame> keyFrames;
				keyFrames.resize(header[KEYFRAME_COUNT]);
				for (unsigned int i = 0; i < keyFrames.size(); ++i)
				{
					keyFrames[i].m_time = *(float*)&block[i * sizeof(float) + sizeof(DirectX::XMFLOAT4X4) * header[BONE_COUNT] * i];
					keyFrames[i].m_bones.resize(header[BONE_COUNT]);
					memcpy_s(&keyFrames[i].m_bones[0], keyFrames[i].m_bones.size() * sizeof(DirectX::XMFLOAT4X4),
						&block[(i + 1) * sizeof(float) + sizeof(DirectX::XMFLOAT4X4) * header[BONE_COUNT] * i], header[BONE_COUNT] * sizeof(DirectX::XMFLOAT4X4));
				}
				delete[] block;

				Animation temp;
				temp.Init(keyFrames, LOOP);
				m_animations.push_back(temp);

				FASTBinaryIO::Close(fastFile);
				FASTBinaryIO::Destroy(fastFile);
				return true;
			}
		}
	}

	FASTBinaryIO::Close(fastFile);
	FASTBinaryIO::Destroy(fastFile);
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

const BlendInfo * AnimationSet::GetBlendInfo(int _animationFrom, int _animationTo) const
{
	if (_animationFrom < m_blendTimes.size() && _animationTo < m_blendTimes[0].size())
		return &m_blendTimes[_animationFrom][_animationTo];
	return nullptr;
}

const BindPose * AnimationSet::GetBindPose() const
{
	return m_bindPose;
}

const Animation * AnimationSet::GetDefaultAnimation() const
{
	return &m_animations[m_defaultAnim];
}

void AnimationSet::SetBlendTimes(std::vector<std::vector<BlendInfo>>& _blendTimes)
{
	m_blendTimes = _blendTimes;
}

void AnimationSet::SetBlendTime(int _animationFrom, int _animationTo, BlendInfo & _blendInfo)
{
	if (_animationFrom < m_blendTimes.size() && _animationTo < m_blendTimes[0].size())
		m_blendTimes[_animationFrom][_animationTo] = _blendInfo;
}

void AnimationSet::SetDefaultAnimation(unsigned long _defaultAnim)
{
	m_defaultAnim = _defaultAnim;
}
