#include <SceneGraph.hpp>

using namespace puggo;

SceneNode::SceneNode(const SceneObject& sceneObject):
    sceneObject(sceneObject) {
}

SceneNode::SceneNode(SceneObject&& sceneObject):
    sceneObject(move(sceneObject)) {
}

SceneNode::SceneNode(const SceneNode& sceneNode):
    sceneObject(sceneNode.sceneObject),
    children(sceneNode.children) {
}

SceneNode::SceneNode(SceneNode&& sceneNode):
    sceneObject(move(sceneNode.sceneObject)),
    children(move(sceneNode.children)) {
}

SceneNode& SceneNode::operator=(const SceneNode& sceneNode) {
    sceneObject = sceneNode.sceneObject;
    children = sceneNode.children;

    return *this;
}

SceneNode& SceneNode::operator=(SceneNode&& sceneNode) {
    sceneObject = move(sceneNode.sceneObject);
    children = move(sceneNode.children);

    return *this;
}

SceneObject& SceneNode::getSceneObject(void) noexcept {
    return sceneObject;
}

vector<SceneNode>& SceneNode::getChildren(void) noexcept {
    return children;
}

void SceneNode::setSceneObject(const SceneObject& sceneObject) noexcept {
    this->sceneObject = sceneObject;
}

void SceneNode::setSceneObject(SceneObject&& sceneObject) noexcept {
    this->sceneObject = move(sceneObject);
}

void SceneNode::startFrame(void) {
    if (PhysicsComponentAllocator::isValidHandle(sceneObject.getPhysicsCompHandle())) {
        PhysicsComponentAllocator::get(sceneObject.getPhysicsCompHandle()).setAccumulatedForces(vec3(0.f, 0.f, 0.f));
    }

    for_each(children.begin(), children.end(), [](SceneNode& sceneNode) { sceneNode.startFrame(); });
}

void SceneNode::renderMesh(void) {
    if (MeshComponentAllocator::isValidHandle(sceneObject.getMeshCompHandle())) {
        GPUMeshComponentInterface::draw(sceneObject.getMeshCompHandle(), GL_TRIANGLES);
    }

    for_each(children.begin(), children.end(), [](SceneNode& sceneNode) { sceneNode.renderMesh(); });
}

SceneGraph::SceneGraph(const SceneNode& root):
    root(root) {
}

SceneGraph::SceneGraph(SceneNode&& root):
    root(move(root)) {
}

SceneGraph::SceneGraph(const SceneGraph& sceneGraph):
    root(sceneGraph.root) {
}

SceneGraph::SceneGraph(SceneGraph&& sceneGraph):
    root(move(sceneGraph.root)) {
}

SceneGraph& SceneGraph::operator=(const SceneGraph& sceneGraph) {
    root = sceneGraph.root;
    return *this;
}

SceneGraph& SceneGraph::operator=(SceneGraph&& sceneGraph) {
    root = move(sceneGraph.root);
    return *this;
}

SceneNode& SceneGraph::getRoot(void) {
    return root;
}

void SceneGraph::setRoot(const SceneNode& root) {
    this->root = root;
}

void SceneGraph::setRoot(SceneNode&& root) {
    this->root = move(root);
}

void SceneGraph::startFrame(void) {
    root.startFrame();
}

void SceneGraph::renderMeshes(void) {
    root.renderMesh();
}

void SceneGraph::runPhysics(const float& duration) {
    // update forces

    // integrate
}