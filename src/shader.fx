/*
    textures
*/
Texture2D Texture : register(t0);

/*
    samplers
*/
sampler   Sampler : register(s0);


/*
    constant vertex buffers
*/
cbuffer VSBuffer : register(b0) 
{
    float4x4 WorldMatrix;
};

cbuffer VSBuffer : register(b1) 
{
    float4x4 ViewProjectionMatrix;
}

/*
    constanct pixel buffers
*/
cbuffer PSBuffer : register(b0)
{
    float3 LightDirection;
    float3 AmbientLight;
}

cbuffer PSBuffer : register(b1)
{
    float3 CameraPosition;
}


/*
    data types
*/
struct VSInput 
{
    float3 position     : POSITION;
    float2 texCoords    : TEXCOORD;
    float3 normal       : NORMAL;
};

struct PSInput 
{
    float4 position     : SV_POSITION;
    float3 normal       : NORMAL;
    float2 texCoords    : TEXCOORD0;
};


/*
    vertex shader
*/
PSInput VShader(VSInput input) 
{
    float4 worldSpacePosition = mul(float4(input.position, 1.0f), WorldMatrix);

    PSInput result = (PSInput) 0;
    result.position = mul(worldSpacePosition, ViewProjectionMatrix);
    result.normal = mul(input.normal, (float3x3) WorldMatrix);
    result.texCoords = input.texCoords;
    
    return result;
}

/*
    pixel shader
*/
float4 PShader(PSInput input) : SV_Target
{
    float3 lightVector = normalize(-LightDirection);
    float3 viewVector = normalize(CameraPosition - input.position.xyz);
    float3 halfVector = normalize(lightVector + viewVector);

    float3 normal = normalize(input.normal);

    float4 ambientLight = float4(AmbientLight, 1.0f);
    float4 diffuseLight = max(dot(normal, lightVector), 0.0f);
    float4 specularLight = pow(max(dot(normal, halfVector), 0.0f), 110.0f);

    float4 light = ambientLight + diffuseLight + specularLight;

    return Texture.Sample(Sampler, input.texCoords) * light;
}

