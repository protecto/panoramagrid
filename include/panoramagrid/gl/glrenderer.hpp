#ifndef PANORAMAGRID_GlRenderer_HPP
#define PANORAMAGRID_GlRenderer_HPP


#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_LEFT_HANDED

#include <map>
#include <panoramagrid/gl/shader.hpp>
#include <panoramagrid/renderer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace panoramagrid::gl {

    class GlRenderer : public Renderer {
    public:
        GlRenderer(int width, int height);

        void render(std::shared_ptr<Node> node) override;

        void loadTexture(std::shared_ptr<Material> material) override;

        cv::Mat getMat() override;

    private:
        GLuint boundVao = 0;
        std::shared_ptr<Shader> usedShader = nullptr;
        std::map<std::shared_ptr<Mesh>, GLuint> vaos;
        std::map<std::shared_ptr<Material>, std::shared_ptr<Shader>> shaders;
        std::map<std::shared_ptr<Material>, GLenum> textureUnits;
        std::map<std::shared_ptr<Material>, GLenum> textures;

        static glm::vec3 toGlm(std::array<float, 3> vector);

        void bindVao(std::shared_ptr<Mesh> mesh);

        void useShader(std::shared_ptr<Material> material);

        void bindTextureUnit(std::shared_ptr<Material> material);

        std::map<GLenum, std::pair<int, int>> getCubemapSides();

        GLenum getDrawMethod(Mesh::DrawMethod method);
    };

}


#endif //PANORAMAGRID_GlRenderer_HPP
