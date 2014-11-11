//#ifndef OPENGL_H
//#define OPENGL_H
//
//#define WIN32_LEAN_AND_MEAN 1
//#include <windows.h>
//
//#include <GL/gl.h>
//#include "GL/glext.h"
//#include "GL/wglext.h"
//
//#include "common.h"
//
//// ���������� ��������� ��� �������� ������ OpenGL
//extern GLenum g_OpenGLError;
//
//// ������� ����� ������� �� ��������
//#define OPENGL_GET_PROC(p,n) \
//	n = (p)wglGetProcAddress(#n); \
//	if (NULL == n) \
//	{ \
//		LOG_ERROR("Loading extension '%s' fail (%d)\n", #n, GetLastError()); \
//		return false; \
//	}
//
//// �������� �� ������ OpenGL
//#define OPENGL_CHECK_FOR_ERRORS() \
//	if ((g_OpenGLError = glGetError()) != GL_NO_ERROR) \
//		LOG_ERROR("OpenGL error 0x%X\n", (unsigned)g_OpenGLError);
//
//// ������������� ����������� ���������� OpenGL
//bool OpenGLInitExtensions();
//
//// ����� � ��� ��������� ���������� �� OpenGL, ������, ��������� � �.�.
//void OpenGLPrintDebugInfo();
//
//// ���������� OpenGL
//// Texture
//extern PFNGLACTIVETEXTUREPROC glActiveTexture;
//// VAO
//extern PFNGLGENVERTEXARRAYSPROC    glGenVertexArrays;
//extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
//extern PFNGLBINDVERTEXARRAYPROC    glBindVertexArray;
//// VBO
//extern PFNGLGENBUFFERSPROC    glGenBuffers;
//extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
//extern PFNGLBINDBUFFERPROC    glBindBuffer;
//extern PFNGLBUFFERDATAPROC    glBufferData;
//extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
//extern PFNGLMAPBUFFERPROC     glMapBuffer;
//extern PFNGLUNMAPBUFFERPROC   glUnmapBuffer;
//// Shaders
//extern PFNGLCREATEPROGRAMPROC     glCreateProgram;
//extern PFNGLDELETEPROGRAMPROC     glDeleteProgram;
//extern PFNGLLINKPROGRAMPROC       glLinkProgram;
//extern PFNGLVALIDATEPROGRAMPROC   glValidateProgram;
//extern PFNGLUSEPROGRAMPROC        glUseProgram;
//extern PFNGLGETPROGRAMIVPROC      glGetProgramiv;
//extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
//extern PFNGLCREATESHADERPROC      glCreateShader;
//extern PFNGLDELETESHADERPROC      glDeleteShader;
//extern PFNGLSHADERSOURCEPROC      glShaderSource;
//extern PFNGLCOMPILESHADERPROC     glCompileShader;
//extern PFNGLATTACHSHADERPROC      glAttachShader;
//extern PFNGLDETACHSHADERPROC      glDetachShader;
//extern PFNGLGETSHADERIVPROC       glGetShaderiv;
//extern PFNGLGETSHADERINFOLOGPROC  glGetShaderInfoLog;
//// Attributes
//extern PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation;
//extern PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer;
//extern PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray;
//extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
//// Uniforms
//extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
//extern PFNGLUNIFORMMATRIX3FVPROC   glUniformMatrix3fv;
//extern PFNGLUNIFORMMATRIX4FVPROC   glUniformMatrix4fv;
//extern PFNGLUNIFORM1IPROC          glUniform1i;
//extern PFNGLUNIFORM1FVPROC         glUniform1fv;
//extern PFNGLUNIFORM3FVPROC         glUniform3fv;
//extern PFNGLUNIFORM4FVPROC         glUniform4fv;
//// FBO
//extern PFNGLBINDFRAMEBUFFERPROC        glBindFramebuffer;
//extern PFNGLDELETEFRAMEBUFFERSPROC     glDeleteFramebuffers;
//extern PFNGLGENFRAMEBUFFERSPROC        glGenFramebuffers;
//extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
//extern PFNGLFRAMEBUFFERTEXTUREPROC     glFramebufferTexture;
//
//#endif /* OPENGL_H */
