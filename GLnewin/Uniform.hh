#pragma once
#include <iostream>
#include <vector>
#include "glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.hh"

class Uniform {
    private:
	unsigned int _frameUpdated = 0;
	void setValueType(__attribute__((unused)) int i_) { _valueType = tInt; }
	void setValueType(__attribute__((unused)) unsigned int i_) { _valueType = tUnsignedInt; }
	void setValueType(__attribute__((unused)) float i_) { _valueType = tFloat; }
	void setValueType(__attribute__((unused)) glm::vec2 const & i_) { _valueType = tVec2; }
	void setValueType(__attribute__((unused)) glm::vec3 const & i_) { _valueType = tVec3; }
	void setValueType(__attribute__((unused)) glm::vec4 const & i_) { _valueType = tVec4; }
	void setValueType(__attribute__((unused)) glm::mat2 const & i_) { _valueType = tMat2; }
	void setValueType(__attribute__((unused)) glm::mat3 const & i_) { _valueType = tMat3; }
	void setValueType(__attribute__((unused)) glm::mat4 const & i_) { _valueType = tMat4; }
    public:
	GLint _location;
	enum tType {
	    tInt,
	    tUnsignedInt,
	    tFloat,
	    tVec2,
	    tVec3,
	    tVec4,
	    tMat2,
	    tMat3,
	    tMat4
	} _valueType;
	union toto {
		int i; unsigned int ui; float f; glm::vec2 v2; glm::vec3 v3; glm::vec4 v4; glm::mat2 m2; glm::mat3 m3; glm::mat4 m4;
	    operator int() {return i;}
	    operator unsigned int() {return ui;}
	    operator float() {return f;}
	    operator glm::vec2() {return v2;}
	    operator glm::vec3() {return v3;}
	    operator glm::vec4() {return v4;}
	    operator glm::mat2() {return m2;}
	    operator glm::mat3() {return m3;}
	    operator glm::mat4() {return m4;}
	    toto(int i_) : i(i_) { }
	    toto(unsigned int i_) : ui(i_) { }
	    toto(float i_) : f(i_) { }
	    toto(glm::vec2 const & i_) : v2(i_) { }
	    toto(glm::vec3 const & i_) : v3(i_) { }
	    toto(glm::vec4 const & i_) : v4(i_) { }
	    toto(glm::mat2 const & i_) : m2(i_) { }
	    toto(glm::mat3 const & i_) : m3(i_) { }
	    toto(glm::mat4 const & i_) : m4(i_) { }
	} _value;
	std::string name;
    	explicit Uniform(int i, std::string const & name_) : _valueType(tInt), _value(i), name(name_) { }
    	explicit Uniform(unsigned int i, std::string const & name_) : _valueType(tUnsignedInt), _value(i), name(name_) { }
    	explicit Uniform(float i, std::string const & name_) : _valueType(tFloat), _value(i), name(name_) { }
    	explicit Uniform(glm::vec2 const & i, std::string const & name_) : _valueType(tVec2), _value(i), name(name_) { }
    	explicit Uniform(glm::vec3 const & i, std::string const & name_) : _valueType(tVec3), _value(i), name(name_) { }
    	explicit Uniform(glm::vec4 const & i, std::string const & name_) : _valueType(tVec4), _value(i), name(name_) { }
    	explicit Uniform(glm::mat2 const & i, std::string const & name_) : _valueType(tMat2), _value(i), name(name_) { }
    	explicit Uniform(glm::mat3 const & i, std::string const & name_) : _valueType(tMat3), _value(i), name(name_) { }
    	explicit Uniform(glm::mat4 const & i, std::string const & name_) : _valueType(tMat4), _value(i), name(name_) { }
    	explicit Uniform(GLint l_, int i, std::string const & name_) : _location(l_), _valueType(tInt), _value(i), name(name_) {}
    	explicit Uniform(GLint l_, unsigned int i, std::string const & name_) : _location(l_), _valueType(tUnsignedInt), _value(i), name(name_) {}
    	explicit Uniform(GLint l_, float i, std::string const & name_) : _location(l_), _valueType(tFloat), _value(i), name(name_) {}
    	explicit Uniform(GLint l_, glm::vec2 const & i, std::string const & name_) : _location(l_), _valueType(tVec2), _value(i), name(name_) {}
    	explicit Uniform(GLint l_, glm::vec3 const & i, std::string const & name_) : _location(l_), _valueType(tVec3), _value(i), name(name_) {}
    	explicit Uniform(GLint l_, glm::vec4 const & i, std::string const & name_) : _location(l_), _valueType(tVec4), _value(i), name(name_) {}
    	explicit Uniform(GLint l_, glm::mat2 const & i, std::string const & name_) : _location(l_), _valueType(tMat2), _value(i), name(name_) {}
    	explicit Uniform(GLint l_, glm::mat3 const & i, std::string const & name_) : _location(l_), _valueType(tMat3), _value(i), name(name_) {}
    	explicit Uniform(GLint l_, glm::mat4 const & i, std::string const & name_) : _location(l_), _valueType(tMat4), _value(i), name(name_) {}
	template<typename T>
	operator T() { return _value; }
	template<typename T>
	void operator=(T v_) { _value = v_; setValueType(v_); }
	template <typename T>
	void updateValue(T v_, unsigned int frame) { _value = v_; _frameUpdated = frame; setValueType(v_); }
	unsigned int getFrameUpdated() const { return _frameUpdated; }
	void upload() const;
	void addItselfToShaders(std::vector<Shader> & shaderList);
	void _resetLocation(const char* name_) {
		GLint programId;
		glGetIntegerv(GL_CURRENT_PROGRAM, &programId);
		_location = glGetUniformLocation(programId, name_);
		std::cout << "uniform: " << name_ << " " << _location << std::endl;
	}
#define autoRelocate(var) var._resetLocation(#var);
};

