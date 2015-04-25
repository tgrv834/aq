#ifndef AQ_SHADERPROGRAM_HPP
#define AQ_SHADERPROGRAM_HPP

#include <aq/common.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace AQ
{

	enum class ShaderType
	{
		Vertex,
		Fragment,
	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		bool attachShaderFromFile(ShaderType type, const std::string& filename);
		bool attachShaderFromMemory(ShaderType type, const std::string& source);

		void use() const;
		bool isInUse() const;
		void stopUsing() const;

		bool link();
		bool isLinked() const;

		void bindAttributeLocation(GLuint location, const GLchar* name);
		GLint getUniformLocation(const GLchar* name);
		GLint getAttributeLocation(const GLchar* name);

		void setUniform(const GLchar* name, float x, float y, float z, float w);
		void setUniform(const GLchar* name, float x, float y, float z);
		void setUniform(const GLchar* name, float x, float y);
		void setUniform(const GLchar* name, float x);
		void setUniform(const GLchar* name, int x);
		void setUniform(const GLchar* name, unsigned int x);
		void setUniform(const GLchar* name, bool x);

		inline GLuint  object() const { return m_object; }
		inline const std::string& errorlog() const { return m_errorLog; }

	private:
		GLuint m_object;
		bool m_linked;
		std::string m_errorLog;


	};


}
#endif