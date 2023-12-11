#include "VertexTexture.h"

VertexTexture::VertexTexture()
{
	SetUV(0, 0);
}

VertexTexture::VertexTexture(const float u, const float v)
{
	SetUV(u, v);
}

VertexTexture::VertexTexture(const VertexTexture& other)
{
	SetUV(other.GetU(), other.GetV());
}

VertexTexture& VertexTexture::operator=(const VertexTexture& other)
{
	SetUV(other.GetU(), other.GetV());
	return *this;
}

void VertexTexture::SetU(const float value)
{
	_u = value;
}

void VertexTexture::SetV(const float value)
{
	_v = value;
}

void VertexTexture::SetUV(const float u, const float v)
{
	SetU(u);
	SetV(v);
}

float VertexTexture::GetU() const
{
	return _u;
}

float VertexTexture::GetV() const
{
	return _v;
}
