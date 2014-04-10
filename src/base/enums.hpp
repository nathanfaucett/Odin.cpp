#ifndef ODIN_ENUMS_HPP
#define ODIN_ENUMS_HPP


namespace Odin {
	
	enum class AxisType: uint32 {
		Button = 1, Mouse, MouseWheel, Touch, Joystick
	};
	
	enum class Blending: uint32 {
		None = 1, Default, Additive, Subtractive, Muliply, Custom
	};
	
	enum class CullFace: GLenum {
		None = 0,
		Front = GL_FRONT,
		Back = GL_BACK,
		Both = GL_FRONT_AND_BACK
	};
	
	enum class FilterMode: uint32 {
		None = 1, Linear
	};
	
	enum class FrontFace: GLenum {
		CounterClockWise = GL_CCW,
		ClockWise = GL_CW
	};
	
	enum class LightType: uint32 {
		Point = 1, Directional, Spot, Hemi
	};
	
	enum class TextureFormat: GLenum {
		Alpha = GL_ALPHA,
		Rgb = GL_RGB,
		Rgba = GL_RGBA,
		Luminance = GL_LUMINANCE,
		LuminanceAlpha = GL_LUMINANCE_ALPHA
	};
	
	enum class TextureWrap: uint32 {
		Repeat = 1, Clamp, MirrorRepeat
	};
	
	enum class ShadowMapType: uint32 {
		BasicShadowMap = 1, PCFShadowMap, PCFSoftShadowMap
	};
	
	enum class WrapMode: uint32 {
		Once = 1, Loop, PingPong, Clamp
	};
}

#endif