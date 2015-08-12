/*

Author: Stoica Alexandru ( Al3xDev )
Contact al3xdev@gmail.com
License: GPL v2.0, see LICENSE file

*/

#ifndef SHADER_H
#define SHADER_H
class Shader
{
 public:
        GLint Program;
        std::vector<GLint> shaders;
        void Create()
        {
        	Program=glCreateProgram();
        	if(!Program)
        	{
        		std::cerr<<"Error creating program shader!\n";
        		return;
        	}
        }
        bool LoadShaderFromFile(std::string name_shader,GLint type)
        {
            //Read from files
            std::string source="";
            std::ifstream file(&name_shader[0]);
            if(file.fail())
            {
            	std::cerr<<"File "<<name_shader<<" doesn't exist!\n";
            	return false;
            }
            std::string ram;
            while(std::getline(file,ram))
            {
                ram.append("\n");
                source.append(ram);
            }
            const GLchar *v=source.c_str();
            shaders.push_back(glCreateShader(type));
            GLint nr_shader=shaders.size()-1;
            if(!shaders[nr_shader])
            {
            	std::cerr<<"Error creating shader nr. "<<nr_shader<<"!\n";
            	return false;
            }
            glShaderSource(shaders[nr_shader
            ], 1, &v, NULL);
            glCompileShader(shaders[nr_shader]);
            GLint result;
            glGetShaderiv(shaders[nr_shader],GL_COMPILE_STATUS,&result);
            if(!result)
           	{
           		std::cerr<<"Nr. "<<nr_shader<<" shader compilation failed!\n";
           		GLint logLen;
           		glGetShaderiv(shaders[nr_shader],GL_INFO_LOG_LENGTH,&logLen);
           		if(logLen>0)
           		{
           			char *log=new char[logLen];
           			GLsizei written;
           			glGetShaderInfoLog(shaders[nr_shader],logLen,&written,log);
           			std::cerr<<"Shader log:\n"<<log<<"\n\n";
           			delete[] log;
           		}
           	}
           	glAttachShader(this->Program,shaders[nr_shader]);
           	return true;
        }
        bool LoadFromString(std::string &shader_source,GLint type)
        {
        	const GLchar *source=shader_source.c_str();
        	shaders.push_back(glCreateShader(type));
        	GLint nr_shader=shaders.size()-1;
        	if(!shaders[nr_shader])
        	{
        		std::cerr<<"Error creating shader nr. "<<nr_shader<<"!\n";
        		return false;
        	}
        	glShaderSource(shaders[nr_shader],1,&source,NULL);
        	glCompileShader(shaders[nr_shader]);
        	  GLint result;
            glGetShaderiv(shaders[nr_shader],GL_COMPILE_STATUS,&result);
            if(!result)
           	{
           		std::cerr<<"Nr. "<<nr_shader<<" shader compilation failed!\n";
           		GLint logLen;
           		glGetShaderiv(shaders[nr_shader],GL_INFO_LOG_LENGTH,&logLen);
           		if(logLen>0)
           		{
           			char *log=new char[logLen];
           			GLsizei written;
           			glGetShaderInfoLog(this->shaders[nr_shader],logLen,&written,log);
           			std::cerr<<"Shader log:\n"<<log<<"\n\n";
           			delete[] log;
           		}
           	}
           	glAttachShader(this->Program,shaders[nr_shader]);
           	return true;
        }
        void Link()
        {
        	glLinkProgram(this->Program);
        	GLint status;
        	glGetProgramiv(Program,GL_LINK_STATUS,&status);
        	if(!status)
        	{
        		std::cerr<<"Failed to link shader program!\n";
        		GLint logLen;
        		glGetProgramiv(Program,GL_INFO_LOG_LENGTH,&logLen);
        		if(logLen>0)
        		{
        			char *log=new char[logLen];
        			GLsizei written;
        			glGetProgramInfoLog(Program,logLen,&written,log);
        			std::cerr<<"Program log:"<<log<<"\n";
        			delete[] log;
        		}
        	}
            for(uint8_t i=0;i<shaders.size()-1;++i)
        	{
        		glDeleteShader(shaders[i]);
        	}
        }
        void Use()
        {
        	glUseProgram(this->Program);
        }
        ~Shader()
        {
        	glDeleteProgram(this->Program);
        }
        void SetFloat(const char* name,GLfloat x)
        {
        	glUniform1f(glGetUniformLocation(this->Program,name),x);
        }
        void SetVector2f(const char* name,glm::vec2 xy)
        {
        	glUniform2f(glGetUniformLocation(this->Program,name),xy.x,xy.y);
        }
        void SetVector2f(const char* name,GLfloat x,GLfloat y)
        {
        	glUniform2f(glGetUniformLocation(this->Program,name),x,y);
        }
        void SetVector3f(const char* name,glm::vec3 xyz)
        {
        	glUniform3f(glGetUniformLocation(this->Program,name),xyz.x,xyz.y,xyz.z);
        }
        void SetVector3f(const char* name,GLfloat x,GLfloat y,GLfloat z)
        {
        	glUniform3f(glGetUniformLocation(this->Program,name),x,y,z);
        }
        void SetVector4f(const char* name,GLfloat x,GLfloat y,GLfloat z,GLfloat w)
        {
        	glUniform4f(glGetUniformLocation(this->Program,name),x,y,z,w);
        }
        void SetVector4f(const char* name,glm::vec4 _vector)
        {
        	glUniform4f(glGetUniformLocation(this->Program,name),_vector.x,_vector.y,_vector.z,_vector.w);
        }
        void SetMatrix4(const char* name,glm::mat4 matrix)
        {
            glUniformMatrix4fv(glGetUniformLocation(this->Program, name), 1, GL_FALSE, glm::value_ptr(matrix));
        }
};

#endif // SHADER_H
