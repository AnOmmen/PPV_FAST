#include "Interpolator.h"



Interpolator::Interpolator()
{
}


Interpolator::~Interpolator()
{
}

Bone * Interpolator::GetCurrentWorld(int & _num)
{
	return &m_world[_num];
}

float Interpolator::GetTime()
{
	return 0.0f;
}

void Interpolator::SetAnimation(const Animation * _anim)
{
	m_animation = _anim;
}

void Interpolator::SetCurrTime(float _time)
{
	m_currBlendTime = _time;
}

void Interpolator::SetTotalTime(float _time)
{
	m_totalBlendTime = _time;
}

ANIM_TYPE Interpolator::Update(float _time)
{
	float frameTime = 0;
	float tweenTime = 0;
	SetCurrTime(m_currBlendTime + _time);
	SetTotalTime(m_animation->GetTotalTime());
	float previousTime = 0;
	float nextTime = 0;
	std::vector<Bone> prevVec;
	std::vector<Bone> nextVec;
	unsigned int numBones = 0;
	for (unsigned int i = 0; i < m_animation->GetNumKeyFrames(); i++)
	{
		if (m_animation->GetFrame(i)->m_time > m_currBlendTime)
		{
			nextTime = m_animation->GetFrame(i)->m_time;
			nextVec = m_animation->GetFrame(i)->m_bones;
			break;
		}
		else if (m_animation->GetFrame(i)->m_time == m_currBlendTime)
		{
			m_currFrame.m_bones = m_animation->GetFrame(i)->m_bones;
			m_currFrame.m_time = m_animation->GetFrame(i)->m_time;
			break;
		}

		previousTime = m_animation->GetFrame(i)->m_time;
		prevVec = m_animation->GetFrame(i)->m_bones;
		numBones = m_animation->GetNumBones();
	}
	//DO THE MATHS
	tweenTime = nextTime - previousTime;
	frameTime = m_currFrame.m_time - previousTime;
	float ratio = frameTime / tweenTime;
	//DirectX::XMVectorLerp()
	//DirectX::XMQuaternionSlerp()
	for (int i = 0; i < numBones; i++)
	{
		DirectX::XMVECTORF32 prevPos;
		DirectX::XMVECTORF32 nextPos;
		DirectX::XMVECTORF32 currPos;
		prevPos.f[0] = prevVec[i].m_world._41;
		prevPos.f[1] = prevVec[i].m_world._42;
		prevPos.f[2] = prevVec[i].m_world._43;
		prevPos.f[3] = prevVec[i].m_world._44;

		nextPos.f[0] = nextVec[i].m_world._41;
		nextPos.f[1] = nextVec[i].m_world._42;
		nextPos.f[2] = nextVec[i].m_world._43;
		nextPos.f[3] = nextVec[i].m_world._44;

		currPos.v = DirectX::XMVectorLerp(prevPos.v, nextPos.v, ratio);
		DirectX::XMVECTOR* prevScale;
		DirectX::XMVECTOR* prevQuat;
		DirectX::XMVECTOR* prevTrans;
		DirectX::XMVECTOR* nextScale;
		DirectX::XMVECTOR* nextQuat;
		DirectX::XMVECTOR* nextTrans;
		DirectX::XMMATRIX prevMat;
		DirectX::XMMATRIX nextMat;
		prevMat = DirectX::XMLoadFloat4x4(&prevVec[i].m_world);
		nextMat = DirectX::XMLoadFloat4x4(&nextVec[i].m_world);
		DirectX::XMMatrixDecompose(prevScale, prevQuat, prevTrans, prevMat);
		DirectX::XMMatrixDecompose(nextScale, nextQuat, nextTrans, nextMat);
		DirectX::XMQuaternionSlerp(*prevQuat, *nextQuat, ratio);
	}
	return ANIM_TYPE();
}
