
cbuffer Frame : register(b0)
{
	float2 startPos;
	float2 imageSize;
	float2 size;
	int leftRight;
	int padding;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// SV_TARGET -> 그릴 곳... 우리한테는 후면버퍼(RTV)
float4 PS(PixelInput input) : SV_TARGET
{
	float2 spriteUV;
	spriteUV.x = abs(input.uv.x - leftRight) * (size.x / imageSize.x) + (startPos.x / imageSize.x);
	spriteUV.y = input.uv.y * (size.y / imageSize.y) + (startPos.y / imageSize.y);

	float4 result = map.Sample(samp, spriteUV);

	return result;
}