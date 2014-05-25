#ifndef ODIN_OPENGL_RENDERER_CPP
#define ODIN_OPENGL_RENDERER_CPP

namespace Odin {
	
	inline OpenGLRenderer::OpenGLRenderer(void) {
		p_surface = NULL;
		m_enabledAttributes = NULL;
	}
	inline OpenGLRenderer::~OpenGLRenderer(void) {
		uint32 i, il;
		for (i = 0, il = p_textures.Length(); i < il; i++) DeleteTexture(p_textures[i]);
		for (i = 0, il = p_vertexBuffers.Length(); i < il; i++) DeleteVertexBuffer(p_vertexBuffers[i]);
		for (i = 0, il = p_programs.Length(); i < il; i++) DeleteProgram(p_programs[i]);
		p_textures.Clear();
		p_vertexBuffers.Clear();
		p_programs.Clear();
		
		p_surface = NULL;
		if (m_enabledAttributes != NULL) delete []m_enabledAttributes;
	}

	inline void OpenGLRenderer::m_ClearGL(void) {
		if (p_surface != NULL) {
			uint32 i, il;
			for (i = 0, il = p_textures.Length(); i < il; i++) DeleteTexture(p_textures[i]);
			for (i = 0, il = p_vertexBuffers.Length(); i < il; i++) DeleteVertexBuffer(p_vertexBuffers[i]);
			for (i = 0, il = p_programs.Length(); i < il; i++) DeleteProgram(p_programs[i]);
			p_textures.Clear();
			p_vertexBuffers.Clear();
			p_programs.Clear();
			p_shaders.Clear();
		}
		
		m_precision = "highp";
		m_extensions.Clear();

		m_spriteAttributesInit = false;
		m_spriteVertexBuffers = 0;
		
		m_maxAnisotropy = 0.0f;
		m_maxTextures = 0;
		m_maxVertexTextures = 0;
		m_maxTextureSize = 0;
		m_maxCubeTextureSize = 0;
		m_maxRenderBufferSize = 0;

		m_maxUniforms = 0;
		m_maxVaryings = 0;
		m_maxAttributes = 0;
		
		if (m_enabledAttributes != NULL) delete []m_enabledAttributes;
		m_enabledAttributes = NULL;
		
		m_program = 0;
		m_programForce = true;
		m_textureIndex = 0;
		m_activeTexture = 0;
		m_activeTextureLocation = -1;
		m_viewportX = 0.0f;
		m_viewportY = 0.0f;
		m_viewportWidth = 1.0f;
		m_viewportHeight = 1.0f;
		m_depthTest = true;
		m_depthWrite = true;
		m_blendingDisabled = false;
		m_blending = Blending::Default;
		m_clearColor.Zero();
		m_clearAlpha = 1.0f;
		m_clearDepth = 1.0f;
		m_clearStencil = 0;
		m_frontFace = FrontFace::CounterClockWise;
		m_cullFaceDisabled = false;
		m_cullFace = CullFace::Back;
		m_lineWidth = 1.0f;
		m_stencilFunction = StencilFunction::Always;
		m_stencilReferenceValue = 0;
		m_stencilMask = 1;
		
		m_currentVertexBuffer = 0;
	}
	
	inline void OpenGLRenderer::m_InitGL(void) {
		int32 tmp1, tmp2;
		#ifdef Mobile
		bool isMobile = true;
		#else
		bool isMobile = false;
		#endif
		
		int32 vsHighpRange, vsHighpPrecision,
			  vsMediumpRange, vsMediumpPrecision,
			  fsHighpRange, fsHighpPrecision,
			  fsMediumpRange, fsMediumpPrecision;

		bool highpAvailable, mediumpAvailable;
		std::string precision = "highp";
		
		glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_HIGH_FLOAT, &vsHighpRange, &vsHighpPrecision);
		glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_MEDIUM_FLOAT, &vsMediumpRange, &vsMediumpPrecision);
		
		glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_HIGH_FLOAT, &fsHighpRange, &fsHighpPrecision);
		glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_MEDIUM_FLOAT, &fsMediumpRange, &fsMediumpPrecision);
		
		highpAvailable = vsHighpPrecision > 0 && vsHighpPrecision > 0;
        mediumpAvailable = fsHighpPrecision > 0 && fsHighpPrecision > 0;
		
		if (!highpAvailable || isMobile) {
			if (mediumpAvailable) {
				precision = "mediump";
			} else {
				precision = "lowp";
			}
		}
		
		m_precision = precision;
		if (GLEW_EXT_texture_filter_anisotropic) {
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &m_maxAnisotropy);
		}
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextures);
		glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &m_maxVertexTextures);
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_maxTextureSize);
		glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &m_maxCubeTextureSize);
		glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &m_maxRenderBufferSize);
		
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &tmp1);
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &tmp2);
		m_maxUniforms = Mathf.Min(tmp1, tmp2) * 4;
		
		glGetIntegerv(GL_MAX_VARYING_VECTORS, &m_maxVaryings);
		m_maxVaryings *= 4;
		
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &m_maxAttributes);
		
		if (m_enabledAttributes != NULL) delete []m_enabledAttributes;
		m_enabledAttributes = new uint32[m_maxAttributes];
		for (int32 i = 0; i < m_maxAttributes; i++) m_enabledAttributes[i] = 0;
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-1, 1, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glViewport(0.0f, 0.0f, 1.0f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0f);
		glClearStencil(0);
		glDepthMask(true);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glLineWidth(1.0f);
		
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	}
	
	inline void OpenGLRenderer::SetSurface(SDL_Surface* surface) {
		p_surface = surface;
		
		m_ClearGL();
		m_InitGL();
	}
	inline SDL_Surface* OpenGLRenderer::GetSurface(void) {
		return p_surface;
	}
	
	inline uint32 OpenGLRenderer::p_CreateGLShader(uint32 shaderType, const std::string& shaderString) {
		uint32 shader = glCreateShader(shaderType);
		const char *shaderSource = shaderString.c_str();
		glShaderSource(shader, 1, &shaderSource, NULL);
		
		glCompileShader(shader);
		
		int32 status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == false) {
			int32 infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			
			char8 *strInfoLog = new char8[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
			
			const char *strShaderType = NULL;
			switch(shaderType) {
				case GL_VERTEX_SHADER:
					strShaderType = "vertex";
					break;
				case GL_GEOMETRY_SHADER:
					strShaderType = "geometry";
					break;
				case GL_FRAGMENT_SHADER:
					strShaderType = "fragment";
					break;
			}
			
			fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
			delete[] strInfoLog;
		}
		
		return shader;
	}
	inline uint32 OpenGLRenderer::CreateProgram(std::string& vertexShaderSource, std::string& fragmentShaderSource) {
		uint32 vertexShader = p_CreateGLShader(GL_VERTEX_SHADER, vertexShaderSource);
		uint32 fragmentShader = p_CreateGLShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
		uint32 program = glCreateProgram();
    
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		
		glLinkProgram(program);
		
		int32 status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == false) {
			int32 infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
			
			char8 *strInfoLog = new char8[infoLogLength + 1];
			glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "Linker failure: %s\n", strInfoLog);
			delete[] strInfoLog;
		}
		GLCheckError(__LINE__);
		
		glDetachShader(program, vertexShader);
		glDeleteShader(vertexShader);
		
		glDetachShader(program, fragmentShader);
		glDeleteShader(fragmentShader);
	
		p_programs.Push(program);
		return program;
	}
	inline uint32 OpenGLRenderer::UpdateProgram(uint32 program, std::string& vertexShaderSource, std::string& fragmentShaderSource) {
		uint32 vertexShader = p_CreateGLShader(GL_VERTEX_SHADER, vertexShaderSource);
		uint32 fragmentShader = p_CreateGLShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
		
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		
		glLinkProgram(program);
		
		int32 status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == false) {
			int32 infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
			
			char8 *strInfoLog = new char8[infoLogLength + 1];
			glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			fprintf(stderr, "Linker failure: %s\n", strInfoLog);
			delete[] strInfoLog;
		}
		GLCheckError(__LINE__);
		
		glDetachShader(program, vertexShader);
		glDeleteShader(vertexShader);
		
		glDetachShader(program, fragmentShader);
		glDeleteShader(fragmentShader);
	
		return program;
	}

	inline OpenGLShader* OpenGLRenderer::CreateShader(std::string& vertexShaderSource, std::string& fragmentShaderSource) {
		OpenGLShader* openGLShader = new OpenGLShader(this, vertexShaderSource, fragmentShaderSource);
		
		p_shaders.Push(openGLShader);
		return openGLShader;
	}

	inline OpenGLShader* OpenGLRenderer::UpdateShader(OpenGLShader* openGLShader, std::string& vertexShaderSource, std::string& fragmentShaderSource) {
		
		openGLShader->Update(vertexShaderSource, fragmentShaderSource);
		return openGLShader;
	}
	
	inline void OpenGLRenderer::CreateMaterial(Material* material) {
		if (!material->m_needsUpdate) return;
		
		if (material->m_openGLShader != NULL) {
			material->m_openGLShader = UpdateShader(material->m_openGLShader, material->vertex, material->fragment);
		} else {
			material->m_openGLShader = CreateShader(material->vertex, material->fragment);
		}
		
		material->m_needsUpdate = false;
	}
	
	inline void OpenGLRenderer::CreateSpriteAttributes(void) {
		if (m_spriteAttributesInit) return;
		
		float32 vertexBuffers[68] = {
			-0.5f, 0.5f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
			
			-0.5f, -0.5f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			
			0.5f, 0.5f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			
			0.5f, -0.5f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f
		};
		m_spriteVertexBuffers = CreateVertexBuffer<float32>(vertexBuffers, sizeof(vertexBuffers));
		
		m_spriteAttributesInit = true;
	}
	
	inline void OpenGLRenderer::CreateMeshAttributes(Mesh* mesh) {
		if (!mesh->m_needsUpdate) return;
	
		uint32 vertexCount = mesh->vertices.Length(),
			   colorCount = mesh->colors.Length(),
			   normalCount = mesh->normals.Length(),
			   tangentCount = mesh->tangents.Length(),
			   uvCount = mesh->uv.Length(),
			   uv2Count = mesh->uv2.Length(),
			   length = (vertexCount * 3) + (colorCount * 3) + (normalCount * 3) + (tangentCount * 4) + (uvCount * 2) + (uv2Count * 2),
		       index, i, j, il;
		
		int32 positionLocation = 0,
			  colorLocation = -1,
			  normalLocation = -1,
			  tangentLocation = -1,
			  uvLocation = -1,
			  uv2Location = -1;
		
		bool hasColors = colorCount > 0,
			 hasNormals = normalCount > 0,
			 hasTangents = tangentCount > 0,
			 hasUvs = uvCount > 0,
			 hasUv2s = uv2Count > 0;
		
		uint32 stride = 3, offset = 0, last = 3;
		if (hasColors) {
			stride += 3;
			offset += last;
			last = 3;
			colorLocation = offset;
		}
		if (hasNormals) {
			stride += 3;
			offset += last;
			last = 3;
			normalLocation = offset;
		}
		if (hasTangents) {
			stride += 4;
			offset += last;
			last = 4;
			tangentLocation = offset;
		}
		if (hasUvs) {
			stride += 2;
			offset += last;
			last = 2;
			uvLocation = offset;
		}
		if (hasUv2s) {
			stride += 2;
			offset += last;
			last = 2;
			uv2Location = offset;
		}
		float32 vertexArray[length];
		
		for (i = 0, il = length, j = 0; i < il; i += stride, j++) {
			index = i + positionLocation;
			vertexArray[index] = mesh->vertices[j]->x;
			vertexArray[index + 1] = mesh->vertices[j]->y;
			vertexArray[index + 2] = mesh->vertices[j]->z;
			
			if (hasColors) {
				index = i + colorLocation;
				vertexArray[index] = mesh->colors[j]->r;
				vertexArray[index + 1] = mesh->colors[j]->g;
				vertexArray[index + 2] = mesh->colors[j]->b;
			}
			if (hasNormals) {
				index = i + normalLocation;
				vertexArray[index] = mesh->normals[j]->x;
				vertexArray[index + 1] = mesh->normals[j]->y;
				vertexArray[index + 2] = mesh->normals[j]->z;
			}
			if (hasTangents) {
				index = i + tangentLocation;
				vertexArray[index] = mesh->tangents[j]->x;
				vertexArray[index + 1] = mesh->tangents[j]->y;
				vertexArray[index + 2] = mesh->tangents[j]->z;
				vertexArray[index + 4] = mesh->tangents[j]->w;
			}
			if (hasUvs) {
				index = i + uvLocation;
				vertexArray[index] = mesh->uv[j]->x;
				vertexArray[index + 1] = mesh->uv[j]->y;
			}
			if (hasUv2s) {
				index = i + uv2Location;
				vertexArray[index] = mesh->uv2[j]->x;
				vertexArray[index + 1] = mesh->uv2[j]->y;
			}
		}
		
		mesh->m_vertexArray = vertexArray;
		mesh->m_stride = stride;
		mesh->m_positionLocation = positionLocation;
		mesh->m_colorLocation = colorLocation;
		mesh->m_normalLocation = normalLocation;
		mesh->m_tangentLocation = tangentLocation;
		mesh->m_uvLocation = uvLocation;
		mesh->m_uv2Location = uv2Location;
		
		if (mesh->m_vertexBuffer == 0) {
			mesh->m_vertexBuffer = CreateVertexBuffer<float32>(vertexArray, sizeof(vertexArray), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
		} else {
			mesh->m_vertexBuffer = UpdateVertexBuffer<float32>(mesh->m_vertexBuffer, vertexArray, sizeof(vertexArray), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
		}
		if (mesh->m_indexBuffer == 0) {
			uint32* array = mesh->indices.GetArray();
			mesh->m_indexBuffer = CreateVertexBuffer<uint32>(array, mesh->indices.Length() * BYTES_PER_UINT32, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
		} else {
			uint32* array = mesh->indices.GetArray();
			mesh->m_indexBuffer = UpdateVertexBuffer<uint32>(mesh->m_indexBuffer, array, mesh->indices.Length() * BYTES_PER_UINT32, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
		}
		
		Array<uint32>& indices = mesh->indices;
		uint32 lineCount = mesh->indices.Length() * 2,
			   triangleIndex = 0;

		index = 0;
		uint32 lineBuffer[lineCount];

		for (i = 0, il = mesh->indices.Length(); i < il; i += 3) {

			lineBuffer[index] = indices[triangleIndex];
			lineBuffer[index + 1] = indices[triangleIndex + 1];

			lineBuffer[index + 2] = indices[triangleIndex];
			lineBuffer[index + 3] = indices[triangleIndex + 2];

			lineBuffer[index + 4] = indices[triangleIndex + 1];
			lineBuffer[index + 5] = indices[triangleIndex + 2];
			
			triangleIndex += 3;
			index += 6;
		}
		if (mesh->m_lineBuffer == 0) {
			mesh->m_lineBuffer = CreateVertexBuffer<uint32>(lineBuffer, lineCount * BYTES_PER_UINT32, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
		} else {
			mesh->m_lineBuffer = UpdateVertexBuffer<uint32>(mesh->m_lineBuffer, lineBuffer, lineCount * BYTES_PER_UINT32, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
		}

		mesh->m_needsUpdate = false;
	}
	
	template <typename Type> inline uint32 OpenGLRenderer::CreateVertexBuffer(Type items[], int32 size, uint32 type, uint32 draw) {
		uint32 vertexBuffer;
		
		glGenBuffers(1, &vertexBuffer);
		
		glBindBuffer(type, vertexBuffer);
		glBufferData(type, size, items, draw);
		glBindBuffer(type, 0);
		
		p_vertexBuffers.Push(vertexBuffer);
		return vertexBuffer;
	}
	
	template <typename Type> inline uint32 OpenGLRenderer::UpdateVertexBuffer(uint32 vertexBuffer, Type items[], int32 size, uint32 type, uint32 draw) {
		
		glBindBuffer(type, vertexBuffer);
		glBufferData(type, size, items, draw);
		glBindBuffer(type, 0);
		
		return vertexBuffer;
	}
	
	inline uint32 OpenGLRenderer::CreateTexture(Texture* texture) {
		if (!texture->m_needsUpdate) return texture->m_textureID;
		
		SDL_Surface* image = texture->m_image;
		if (image == NULL) {
			QuitError("texture "+ texture->p_name +" image is NULL");
		}
		image = SDL_ConvertSurface(image, p_surface->format, 0);
		bool isPOT = Mathf.IsPowerOfTwo(image->w) && Mathf.IsPowerOfTwo(image->h);
		
		bool mipmap = texture->m_generateMipmap;
		float32 anisotropy = texture->m_anisotropy;
		TextureFilter filter = texture->m_filter;
		TextureFormat format = texture->m_format;
		TextureWrap wrap = texture->m_wrap;
		TextureType type = texture->m_type;
		
		uint32& textureID = texture->m_textureID;
		int32 minFilter = GL_NEAREST, magFilter = GL_NEAREST;

		if (wrap == TextureWrap::MirrorRepeat) {
			wrap = isPOT ? TextureWrap::MirrorRepeat : TextureWrap::Clamp;
		} else if (wrap == TextureWrap::Repeat) {
			wrap = isPOT ? TextureWrap::Repeat : TextureWrap::Clamp;
		}
		if (filter == TextureFilter::None) {
			magFilter = GL_NEAREST;
			if (mipmap && isPOT) {
				minFilter = GL_LINEAR_MIPMAP_NEAREST;
			} else {
				minFilter = GL_NEAREST;
			}
		} else if (filter == TextureFilter::Linear) {
			magFilter = GL_LINEAR;
			if (mipmap && isPOT) {
				minFilter = GL_LINEAR_MIPMAP_LINEAR;
			} else {
				minFilter = GL_LINEAR;
			}
		}
		
		int32 bytesPerPixel = image->format->BytesPerPixel;
		if (bytesPerPixel == 4) {
			if (image->format->Rmask == 0x000000ff) {
				format = TextureFormat::RGBA; 
			} else {
				format = TextureFormat::BGRA; 
			}
		} else if (bytesPerPixel == 3) { 
            if (image->format->Rmask == 0x000000ff) {
				format = TextureFormat::RGB; 
            } else {
				format = TextureFormat::BGR; 
            }
        } 
		
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, bytesPerPixel, image->w, image->h, 0, static_cast<uint32>(format), static_cast<uint32>(type), image->pixels);
		
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, magFilter);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int32>(wrap));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int32>(wrap));
		
		if (anisotropy > 0.0f && GLEW_EXT_texture_filter_anisotropic) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Mathf.Clamp(anisotropy, 1.0f, m_maxAnisotropy));
		}
		if (mipmap && isPOT) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		
		p_textures.Push(textureID);
		texture->m_needsUpdate = false;
		
		return textureID;
	}
	
	inline void OpenGLRenderer::DeleteProgram(uint32 program) {
		glDeleteProgram(program);
	}
	inline void OpenGLRenderer::DeleteVertexBuffer(uint32 vertexBuffer) {
		glDeleteBuffers(1, &vertexBuffer);
	}
	inline void OpenGLRenderer::DeleteTexture(uint32 texture) {
		glDeleteTextures(1, &texture);
	}
	
	inline void OpenGLRenderer::ClearCanvas(bool color, bool depth, bool stencil) {
		uint32 bits = 0;

		if (color) bits |= GL_COLOR_BUFFER_BIT;
		if (depth) bits |= GL_DEPTH_BUFFER_BIT;
		if (stencil) bits |= GL_STENCIL_BUFFER_BIT;

		glClear(bits);
	}
	inline void OpenGLRenderer::ClearColor(void) {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	inline void OpenGLRenderer::ClearDepth(void) {
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	inline void OpenGLRenderer::ClearStencil(void) {
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	inline void OpenGLRenderer::EnableAttribute(int32 attribute) {
		if (attribute >= m_maxAttributes) {
			LogError("OpenGLRenderer::EnableAttribute(uint32 attribute) Max attributes excedded for this machine "+ ToString(m_maxAttributes), __LINE__);
			return;
		}
		
		if (m_enabledAttributes[attribute] == 0) {
			glEnableVertexAttribArray(attribute);
			m_enabledAttributes[attribute] = 1;
		}
	}
	inline void OpenGLRenderer::DisableAttribute(int32 attribute) {
		if (attribute >= m_maxAttributes) return;

		if (m_enabledAttributes[attribute] == 1) {
			glDisableVertexAttribArray(attribute);
			m_enabledAttributes[attribute] = 0;
		}
	}
	inline void OpenGLRenderer::DisableAttributes(void) {
		uint32 i = m_maxAttributes;

		while (i--) {
			if (m_enabledAttributes[i] == 1) {
				glDisableVertexAttribArray(i);
				m_enabledAttributes[i] = 0;
			}
		}
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	inline void OpenGLRenderer::BindBuffer(int32 location, uint32 buffer, uint32 arrayType, int32 itemSize, uint32 type, int32 stride, int32 first) {
		glBindBuffer(arrayType, buffer);
		EnableAttribute(location);
		glVertexAttribPointer(location, itemSize, type, GL_FALSE, stride, BUFFER_OFFSET(first));
	}
	
	inline void OpenGLRenderer::BindTexture(int32 location, Texture* texture) {
		bool& needsUpdate = texture->m_needsUpdate;
		uint32 textureID = CreateTexture(texture);

		if (m_textureIndex >= m_maxTextures) {
			LogError("OpenGLRenderer::BindTexture(int32 location, Texture* texture) Max textures excedded for this machine "+ ToString(m_maxTextures), __LINE__);
			return;
		}

		if (needsUpdate || (m_activeTextureLocation != location && m_activeTexture != textureID)) {
			glActiveTexture(GL_TEXTURE0 + m_textureIndex);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glUniform1i(location, m_textureIndex);

			if (m_activeTextureLocation != location && m_activeTexture != textureID) {
				m_textureIndex++;
			}
			m_activeTextureLocation = location;
			m_activeTexture = textureID;
		}
	}
	
	inline void OpenGLRenderer::BindMaterial(Material* material, Mat4f& projectionMatrix, Mat4f& viewMatrix, Transform* transform) {
		CreateMaterial(material);
		
		OpenGLShader* openGLShader = material->m_openGLShader;
		std::unordered_map<std::string, Uniform*>& shaderUniforms = openGLShader->uniforms;
		std::unordered_map<std::string, MaterialUniform*>& materialUniforms = material->uniforms;
		
		SetBlending(material->m_blending);
		switch(material->m_side) {
			case Side::Front:
				SetCullFace(CullFace::Back);
				break;
			case Side::Back:
				SetCullFace(CullFace::Front);
				break;
			case Side::FrontAndBack:
				SetCullFace(false);
				break;
		}
		
		Uniform* modelView = shaderUniforms["modelView"];
		if (modelView != NULL) static_cast<UniformMatrix4fv*>(modelView)->Set(transform->modelView);
		Uniform* model = shaderUniforms["model"];
		if (model != NULL) static_cast<UniformMatrix4fv*>(model)->Set(transform->matrixWorld);
		Uniform* normalMatrix = shaderUniforms["normalMatrix"];
		if (normalMatrix != NULL) static_cast<UniformMatrix3fv*>(normalMatrix)->Set(transform->normalMatrix);
		
		Uniform* view = shaderUniforms["view"];
		if (view != NULL) static_cast<UniformMatrix4fv*>(view)->Set(viewMatrix);
		Uniform* projection = shaderUniforms["projection"];
		if (projection != NULL) static_cast<UniformMatrix4fv*>(projection)->Set(projectionMatrix);
		
		for (auto it = shaderUniforms.begin(); it != shaderUniforms.end(); ++it) {
			Uniform* uniform = it->second;
			if (uniform == NULL) continue;
			MaterialUniform* materialUniform = materialUniforms[uniform->name];
			if (materialUniform == NULL) continue;
			
			switch(uniform->type) {
				case GL_INT:
					static_cast<Uniform1i*>(uniform)->Set(static_cast<MaterialUniform1i*>(materialUniform)->value);
					break;
				case GL_INT_VEC2:
					static_cast<Uniform2i*>(uniform)->Set(static_cast<MaterialUniform2i*>(materialUniform)->value);
					break;
				case GL_INT_VEC3:
					static_cast<Uniform3i*>(uniform)->Set(static_cast<MaterialUniform3i*>(materialUniform)->value);
					break;
				case GL_INT_VEC4:
					static_cast<Uniform4i*>(uniform)->Set(static_cast<MaterialUniform4i*>(materialUniform)->value);
					break;

				case GL_FLOAT:
					static_cast<Uniform1f*>(uniform)->Set(static_cast<MaterialUniform1f*>(materialUniform)->value);
					break;
				case GL_FLOAT_VEC2:
					static_cast<Uniform2f*>(uniform)->Set(static_cast<MaterialUniform2f*>(materialUniform)->value);
					break;
				case GL_FLOAT_VEC3:
					static_cast<Uniform3f*>(uniform)->Set(static_cast<MaterialUniform3f*>(materialUniform)->value);
					break;
				case GL_FLOAT_VEC4:
					static_cast<Uniform4f*>(uniform)->Set(static_cast<MaterialUniform4f*>(materialUniform)->value);
					break;

				case GL_FLOAT_MAT2:
					static_cast<UniformMatrix2fv*>(uniform)->Set(static_cast<MaterialUniformMatrix2fv*>(materialUniform)->value);
					break;
				case GL_FLOAT_MAT3:
					static_cast<UniformMatrix3fv*>(uniform)->Set(static_cast<MaterialUniformMatrix3fv*>(materialUniform)->value);
					break;
				case GL_FLOAT_MAT4:
					static_cast<UniformMatrix4fv*>(uniform)->Set(static_cast<MaterialUniformMatrix4fv*>(materialUniform)->value);
					break;

				case GL_SAMPLER_2D:
					static_cast<UniformSampler2D*>(uniform)->Set(static_cast<MaterialUniformSampler2D*>(materialUniform)->value);
					break;
				case GL_SAMPLER_CUBE:
					static_cast<UniformSamplerCube*>(uniform)->Set(static_cast<MaterialUniformSamplerCube*>(materialUniform)->value);
					break;
				default:
					break;
			}
		}
	}
	
	inline void OpenGLRenderer::BindSpriteAttributes(Material* material) {
		if (m_currentVertexBuffer == m_spriteVertexBuffers) return;
		m_currentVertexBuffer = m_spriteVertexBuffers;
		DisableAttributes();
		
		OpenGLShader* openGLShader = material->m_openGLShader;
		std::unordered_map<std::string, Attribute*>& shaderAttributes = openGLShader->attributes;
		
		Attribute* position = shaderAttributes["position"];
		if (position != NULL) {
			BindBuffer(position->location, m_spriteVertexBuffers, GL_ARRAY_BUFFER, 3, GL_FLOAT, (BYTES_PER_FLOAT32 * 17), 0);
		}
		Attribute* normal = shaderAttributes["normal"];
		if (normal != NULL) {
			BindBuffer(normal->location, m_spriteVertexBuffers, GL_ARRAY_BUFFER, 3, GL_FLOAT, (BYTES_PER_FLOAT32 * 17), (BYTES_PER_FLOAT32 * 3));
		}
		Attribute* color = shaderAttributes["color"];
		if (color != NULL) {
			BindBuffer(color->location, m_spriteVertexBuffers, GL_ARRAY_BUFFER, 3, GL_FLOAT, (BYTES_PER_FLOAT32 * 17), (BYTES_PER_FLOAT32 * 6));
		}
		Attribute* uv = shaderAttributes["uv"];
		if (uv != NULL) {
			BindBuffer(uv->location, m_spriteVertexBuffers, GL_ARRAY_BUFFER, 2, GL_FLOAT, (BYTES_PER_FLOAT32 * 17), (BYTES_PER_FLOAT32 * 9));
		}
		Attribute* uv2 = shaderAttributes["uv2"];
		if (uv2 != NULL) {
			BindBuffer(uv2->location, m_spriteVertexBuffers, GL_ARRAY_BUFFER, 2, GL_FLOAT, (BYTES_PER_FLOAT32 * 17), (BYTES_PER_FLOAT32 * 11));
		}
		Attribute* tangent = shaderAttributes["tangent"];
		if (tangent != NULL) {
			BindBuffer(tangent->location, m_spriteVertexBuffers, GL_ARRAY_BUFFER, 4, GL_FLOAT, (BYTES_PER_FLOAT32 * 17), (BYTES_PER_FLOAT32 * 13));
		}
	}
	
	inline void OpenGLRenderer::BindMeshAttributes(Material* material, Mesh* mesh) {
		if (m_currentVertexBuffer == mesh->m_vertexBuffer) return;
		m_currentVertexBuffer = mesh->m_vertexBuffer;
		DisableAttributes();
		
		OpenGLShader* openGLShader = material->m_openGLShader;
		std::unordered_map<std::string, Attribute*>& shaderAttributes = openGLShader->attributes;
		
		Attribute* position = shaderAttributes["position"];
		if (position != NULL && mesh->m_positionLocation != -1) {
			BindBuffer(position->location, mesh->m_vertexBuffer, GL_ARRAY_BUFFER, 3, GL_FLOAT, (BYTES_PER_FLOAT32 * mesh->m_stride), (BYTES_PER_FLOAT32 * mesh->m_positionLocation));
		}
		Attribute* normal = shaderAttributes["normal"];
		if (normal != NULL && mesh->m_normalLocation != -1) {
			BindBuffer(normal->location, mesh->m_vertexBuffer, GL_ARRAY_BUFFER, 3, GL_FLOAT, (BYTES_PER_FLOAT32 * mesh->m_stride), (BYTES_PER_FLOAT32 * mesh->m_normalLocation));
		}
		Attribute* color = shaderAttributes["color"];
		if (color != NULL && mesh->m_colorLocation != -1) {
			BindBuffer(color->location, mesh->m_vertexBuffer, GL_ARRAY_BUFFER, 3, GL_FLOAT, (BYTES_PER_FLOAT32 * mesh->m_stride), (BYTES_PER_FLOAT32 * mesh->m_colorLocation));
		}
		Attribute* uv = shaderAttributes["uv"];
		if (uv != NULL && mesh->m_uvLocation != -1) {
			BindBuffer(uv->location, mesh->m_vertexBuffer, GL_ARRAY_BUFFER, 2, GL_FLOAT, (BYTES_PER_FLOAT32 * mesh->m_stride), (BYTES_PER_FLOAT32 * mesh->m_uvLocation));
		}
		Attribute* uv2 = shaderAttributes["uv2"];
		if (uv2 != NULL && mesh->m_uvLocation != -1) {
			BindBuffer(uv2->location, mesh->m_vertexBuffer, GL_ARRAY_BUFFER, 2, GL_FLOAT, (BYTES_PER_FLOAT32 * mesh->m_stride), (BYTES_PER_FLOAT32 * mesh->m_uv2Location));
		}
		Attribute* tangent = shaderAttributes["tangent"];
		if (tangent != NULL && mesh->m_tangentLocation != -1) {
			BindBuffer(tangent->location, mesh->m_vertexBuffer, GL_ARRAY_BUFFER, 4, GL_FLOAT, (BYTES_PER_FLOAT32 * mesh->m_stride), (BYTES_PER_FLOAT32 * mesh->m_tangentLocation));
		}
		
		if (material->m_wireframe) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_lineBuffer);
		} else {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_indexBuffer);
		}
	}

	inline bool OpenGLRenderer::GetProgramForce(void) {
		return m_programForce;
	}
	
	inline void OpenGLRenderer::SetProgram(uint32 program) {
		
		if (m_program != program) {
			m_program = program;
			m_programForce = true;
			m_activeTexture = 0;
			m_activeTextureLocation = -1;
			m_textureIndex = 0;

			glUseProgram(program);
		} else {
			m_programForce = false;
		}
	}
	
	inline void OpenGLRenderer::SetViewport(float32 x, float32 y, float32 width, float32 height) {
		if (m_viewportX != x || m_viewportY != y || m_viewportWidth != width || m_viewportHeight != height) {
			m_viewportX = x;
			m_viewportY = y;
			m_viewportWidth = width;
			m_viewportHeight = height;
			glViewport(x, y, width, height);
		}
	}
	inline void OpenGLRenderer::SetDepthTest(bool depthTest) {
		if (m_depthTest != depthTest) {
			m_depthTest = depthTest;
			
			if (depthTest) {
				glEnable(GL_DEPTH_TEST);
			} else {
				glDisable(GL_DEPTH_TEST);
			}
		}
	}
	inline void OpenGLRenderer::SetDepthWrite(bool depthWrite) {
		if (m_depthWrite != depthWrite) {
			m_depthWrite = depthWrite;
			glDepthMask(depthWrite);
		}
	}
	inline void OpenGLRenderer::SetBlending(Blending blending) {
		if (m_blendingDisabled || m_blending != blending) {
			m_blending = blending;
			
			switch (blending) {
				case Blending::Additive:
					if (m_blendingDisabled) glEnable(GL_BLEND);
					glBlendEquation(GL_FUNC_ADD);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE);
					break;
				
				case Blending::Subtractive:
					if (m_blendingDisabled) glEnable(GL_BLEND);
					glBlendEquation(GL_FUNC_ADD);
					glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
					break;
				
				case Blending::Multiply:
					if (m_blendingDisabled) glEnable(GL_BLEND);
					glBlendEquation(GL_FUNC_ADD);
					glBlendFunc(GL_ZERO, GL_SRC_COLOR);
					break;
				
				case Blending::Screen:
					if (m_blendingDisabled) glEnable(GL_BLEND);
					glBlendEquation(GL_FUNC_ADD);
					glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
					break;
				
				case Blending::Default:
					if (m_blendingDisabled) glEnable(GL_BLEND);
					glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
					glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
					break;
				
				case Blending::None:
				default:
					glDisable(GL_BLEND);
					m_blendingDisabled = true;
					m_blending = Blending::None;
					return;
			}
			
			m_blendingDisabled = false;
		}
	}
	inline void OpenGLRenderer::SetBlending(bool value) {
		if (m_blendingDisabled == value) {
			if (value) {
				m_blendingDisabled = false;
				glEnable(GL_BLEND);
			} else {
				m_blendingDisabled = true;
				glDisable(GL_BLEND);
			}
		}
	}
	inline void OpenGLRenderer::SetClearColor(const Colorf& color, float32 alpha) {
		if (m_clearColor != color || m_clearAlpha != alpha) {
			m_clearColor = color;
			m_clearAlpha = alpha;
			glClearColor(color.r, color.g, color.b, alpha);
		}
	}
	inline void OpenGLRenderer::SetClearDepth(float32 depth) {
		if (m_clearDepth != depth) {
			m_clearDepth = depth;
			glClearDepth(depth);
		}
	}
	inline void OpenGLRenderer::SetClearStencil(int32 stencil) {
		if (m_clearStencil != stencil) {
			m_clearStencil = stencil;
			glClearStencil(stencil);
		}
	}
	inline void OpenGLRenderer::SetFrontFace(FrontFace mode) {
		if (m_frontFace != mode) {
			m_frontFace = mode;
			glFrontFace(static_cast<GLenum>(mode));
		}
	}
	inline void OpenGLRenderer::SetCullFace(CullFace mode) {
		if (m_cullFaceDisabled || m_cullFace != mode) {
			m_cullFace = mode;
			if (m_cullFaceDisabled) {
				m_cullFaceDisabled = false;
				glEnable(GL_CULL_FACE);
			}
			glCullFace(static_cast<GLenum>(mode));
		}
	}
	inline void OpenGLRenderer::SetCullFace(bool value) {
		if (m_cullFaceDisabled == value) {
			if (value) {
				m_cullFaceDisabled = false;
				glEnable(GL_CULL_FACE);
			} else {
				m_cullFaceDisabled = true;
				glDisable(GL_CULL_FACE);
			}
		}
	}
	inline void OpenGLRenderer::SetLineWidth(float32 width) {
		if (m_lineWidth != width) {
			m_lineWidth = width;
			glLineWidth(width);
		}
	}
	inline void OpenGLRenderer::SetScissor(float32 x, float32 y, float32 width, float32 height) {
		glScissor(x, y, width, height);
	}
	inline void OpenGLRenderer::SetStencilFunction(CullFace cullFace, StencilFunction function, int32 referenceValue, uint32 mask) {
		if (m_stencilFunction != function || m_stencilReferenceValue != referenceValue || m_stencilMask != mask) {
			m_stencilFunction = function;
			m_stencilReferenceValue = referenceValue;
			m_stencilMask = mask;
			glStencilFuncSeparate(static_cast<GLenum>(cullFace), static_cast<GLenum>(function), referenceValue, mask);
		}
	}
	inline void OpenGLRenderer::SetStencilFunction(StencilFunction function, int32 referenceValue, uint32 mask) {
		if (m_stencilFunction != function || m_stencilReferenceValue != referenceValue || m_stencilMask != mask) {
			m_stencilFunction = function;
			m_stencilReferenceValue = referenceValue;
			m_stencilMask = mask;
			glStencilFunc(static_cast<GLenum>(function), referenceValue, mask);
		}
	}
}

#endif