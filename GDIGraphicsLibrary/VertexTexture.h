#pragma once
class VertexTexture
{
public:
	VertexTexture();
	VertexTexture(const float u, const float v);
	VertexTexture(const VertexTexture& other);
	VertexTexture& operator= (const VertexTexture& other);

	void SetU(const float value);
	void SetV(const float value);
	void SetUV(const float u, const float v);

	float GetU() const;
	float GetV() const;

private:
	float _u;
	float _v;
};

