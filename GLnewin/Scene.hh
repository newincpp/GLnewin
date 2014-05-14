#ifndef SCENEMANAGER_H_
# define SCENEMANAGER_H_

#include <functional>
#include <utility>
#include <future>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "RenderSystem.hh"
#include "Camera.hh"
#include "Mesh.hh"

namespace GLnewin {
    template <typename T>
    class Scene : public IRenderable {
	private:
	    typedef T __Internal_;
	    std::vector<const __Internal_*> _objects;
	    GLnewin::Shader _shader;
	    GLnewin::Camera* _cam;
	    inline void _setTrivialShader() noexcept {
		std::string trivVertex = "#version 330 \n layout(location = 0) in vec3 vertex; \n uniform mat4 projection; \n uniform mat4 view; \n uniform mat4 model; \n void main(void) { \n gl_Position = projection * view * model * vec4(vertex, 1.0); \n }";
		std::string trivFrag = "#version 330 \n out vec4 outColor; \n uniform float color; \n void main(void) { \n outColor = vec4(0.0,0.3, color, 1.0); \n }";
		_shader.setVertex(trivVertex);
		_shader.setFragment(trivFrag);
		_shader.link();
	    }
	public:
	    Scene();
	    Scene(const Shader&);
	    ~Scene();
	    template <unsigned int RENDERTYPE = GL_TRIANGLES, bool DEBUG = false>
		Mesh<RENDERTYPE>* genMesh(const std::string& file);
	    void setShader(const Shader&);
	    const Shader& getShader() const { return _shader; }
	    inline Camera& getCamera() noexcept { return *_cam; }
	    inline Camera genCamera() noexcept { return Camera(_shader); }
	    virtual void draw() const noexcept;
	    virtual void draw() noexcept;
	    void render()const;
	    std::vector<const __Internal_*>& getObjectList() const noexcept;
	    void pushRenderCandidate(const IRenderable*) noexcept;
	    template<unsigned int RENDERTYPE = GL_TRIANGLES>
		void bindMatrix(Mesh<RENDERTYPE>&) const noexcept;
    };
}

#include "Scene.inl"

#endif /* !SCENEMANAGER_H_ */
