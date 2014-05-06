#ifndef ODIN_ENUMS_HPP
#define ODIN_ENUMS_HPP

namespace Odin {
	
	enum class FrontFace : GLenum {
		CounterClockWise = GL_CCW,
		ClockWise = GL_CW
	};
	enum class CullFace : GLenum {
		Front = GL_FRONT,
		Back = GL_BACK,
		FrontAndBack = GL_FRONT_AND_BACK
	};
	enum class StencilFunction : GLenum {
		Never = GL_NEVER,
		Always = GL_ALWAYS,
		Less = GL_LESS,
		LessOrEqual = GL_LEQUAL,
		Equal = GL_EQUAL,
		NotEqual = GL_NOTEQUAL,
		GreaterOrEqual = GL_GEQUAL,
		Greater = GL_GREATER
	};
	
	enum class Blending : uint32 {
		None = 1 << 0,
		Additive = 1 << 1,
		Subtractive = 1 << 2,
		Multiply = 1 << 3,
		Screen = 1 << 4,
		Default = 1 << 5
	};
	
	enum class TextureFilter : uint32 {
		None = 1 << 0,
		Linear = 1 << 1,
		Bilinear = 1 << 2
	};
	enum class TextureFormat : uint32 {
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		Luminance = GL_LUMINANCE,
		Alpha = GL_ALPHA,
		LuminanceAlpha = GL_LUMINANCE_ALPHA
	};
	enum class TextureType : uint32 {
		UnsignedByte = GL_UNSIGNED_BYTE,
		Float = GL_FLOAT,
		DepthComponent = GL_DEPTH_COMPONENT,
		UnsignedShort = GL_UNSIGNED_SHORT,
		UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,
		UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
		UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1
	};
	enum class TextureWrap : uint32 {
		Repeat = GL_REPEAT,
		Clamp = GL_CLAMP_TO_EDGE,
		MirrorRepeat = GL_MIRRORED_REPEAT
	};
}

#endif