#pragma once

#include <vector>
#include <list>
#include <functional>
#include "Camera.hh"
#include "Mesh.hh"
#include "shader.hh"
//#include "fileWatcher.hh"

#include <iostream>

class DrawBuffer {
    public:
	std::vector<FrameBuffer> _fb;
	std::vector<Mesh> _meshes;
	std::vector<Camera> _cameras;
	std::list<Shader> _shaders;
	unsigned int _activeCamera;
	DrawBuffer();
	void update(unsigned int currentFrame = 0);
	void render();
	void bindGBuffer(unsigned int camera_);
	void reset(std::string&);
	void addAllUniformsToShaders() { addMeshUniformsToShaders(); addCameraUniformsToShaders(); }
	void addMeshUniformsToShaders();
	void addCameraUniformsToShaders();
};
