#ifndef PUGGO_SCENE_GRAPH_HPP
#define PUGGO_SCENE_GRAPH_HPP

#include <SceneObject.hpp>
#include <GPUMeshComponentInterface.hpp>

namespace puggo {
    class SceneNode {
    public:
        SceneNode(const SceneObject& sceneObject);
        SceneNode(SceneObject&& sceneObject = SceneObject());
        SceneNode(const SceneNode& sceneNode);
        SceneNode(SceneNode&& sceneNode);

        SceneNode& operator=(const SceneNode& sceneNode);
        SceneNode& operator=(SceneNode&& sceneNode);

        SceneObject& getSceneObject(void) noexcept;
        vector<SceneNode>& getChildren(void) noexcept;

        void setSceneObject(const SceneObject& sceneObject) noexcept;
        void setSceneObject(SceneObject&& sceneObject) noexcept;
        
        void startFrame(void);
        void renderMesh(void);

    private:
        SceneObject sceneObject;
        vector<SceneNode> children;
    };

    class SceneGraph {
    public:
        SceneGraph(const SceneNode& root);
        SceneGraph(SceneNode&& root = SceneNode());
        SceneGraph(const SceneGraph& sceneGraph);
        SceneGraph(SceneGraph&& sceneGraph);
        
        SceneGraph& operator=(const SceneGraph& sceneGraph);
        SceneGraph& operator=(SceneGraph&& sceneGraph);

        SceneNode& getRoot(void);
        void setRoot(const SceneNode& root);
        void setRoot(SceneNode&& root);

        void startFrame(void);
        void renderMeshes(void);
        void runPhysics(const float& duration);

    private:
        SceneNode root;
    };
}

#endif // !PUGGO_SCENE_GRAPH_HPP
