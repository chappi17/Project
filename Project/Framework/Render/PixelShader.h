#pragma once
class PixelShader : public Shader
{
public:
    PixelShader(wstring file);
    virtual ~PixelShader();

    virtual void CreateBlob(wstring file) override;
    void CreatePixelShader();

    virtual void Set() override;
private:
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader;
};

