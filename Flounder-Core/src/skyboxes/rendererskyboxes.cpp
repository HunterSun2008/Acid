#include "rendererskyboxes.h"

namespace flounder
{
	rendererskyboxes::rendererskyboxes() :
		irenderer()
	{
		m_shader = shader::newShader()->addName("skybox")
		                              ->addType(shadertype(GL_VERTEX_SHADER, "res/shaders/skybox/skyboxVertex.glsl", loadtype::FILE))
		                              ->addType(shadertype(GL_FRAGMENT_SHADER, "res/shaders/skybox/skyboxFragment.glsl", loadtype::FILE))
		                              ->create();
	}

	rendererskyboxes::~rendererskyboxes()
	{
		delete m_shader;
	}

	void rendererskyboxes::render(const vector4 &clipPlane, const icamera &camera)
	{
		prepareRendering(clipPlane, camera);
		renderSkybox(skyboxes::get());
		endRendering();
	}

	void rendererskyboxes::prepareRendering(const vector4 &clipPlane, const icamera &camera)
	{
		// Starts the shader.
		m_shader->start();

		// Loads the uniforms.
		m_shader->loadUniform("projectionMatrix", *camera.getProjectionMatrix());
		m_shader->loadUniform("viewMatrix", *camera.getViewMatrix());
		m_shader->loadUniform("clipPlane", clipPlane);
		m_shader->loadUniform("polygonMode", renderer::get()->isInWireframe());

		// Sets the GPU for rendering this object.
		renderer::get()->antialias(display::get()->isAntialiasing());
		renderer::get()->enableDepthTesting();
		renderer::get()->depthMask(false);
		renderer::get()->cullBackFaces(false);
		renderer::get()->disableBlending();
	}

	void rendererskyboxes::renderSkybox(skyboxes *object)
	{
		// Binds the layouts.
		renderer::get()->bindVAO(skyboxes::get()->getModel()->getVaoID(), 1, 0);
		renderer::get()->bindTexture(skyboxes::get()->getTexture(), 0);

		// Loads the uniforms.
		m_shader->loadUniform("modelMatrix", *skyboxes::get()->getModelMatrix());
		m_shader->loadUniform("skyColour", *skyboxes::get()->getFog()->m_colour);
		m_shader->loadUniform("blendFactor", skyboxes::get()->getBlend());

		// Tells the GPU to render this object.
		renderer::get()->renderElements(GL_TRIANGLES, GL_UNSIGNED_INT, skyboxes::get()->getModel()->getVaoLength());

		// Unbinds the layouts.
		renderer::get()->unbindVAO(1, 0);
	}

	void rendererskyboxes::endRendering()
	{
		// Unbinds the layouts.
		renderer::get()->depthMask(true);

		// Stops the shader.
		m_shader->stop();
	}
}
