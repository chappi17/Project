cbuffer View : register(b1)
{
	matrix view;
}

cbuffer Projection : register(b2)
{
	matrix projection;
}

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;

	matrix trasnform : INSTANCE_TRANSFORM;
};

struct VertexOutput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};


VertexOutput VS(VertexInput input)
{
	VertexOutput result;
	result.pos = mul(input.pos, input.trasnform);
	result.pos = mul(result.pos, view);
	result.pos = mul(result.pos, projection);

	result.uv = input.uv;

	return result;
}