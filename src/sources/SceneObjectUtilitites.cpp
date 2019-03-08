#include <SceneObjectUtilities.hpp>

using namespace puggo;

SceneObject SceneObjectUtilities::createSphere(const float& radius) {
    SceneObject sphereObject = SceneObject();
    addSphereCollision(sphereObject, radius);
    return sphereObject;
}

SceneObject SceneObjectUtilities::createCapsule(const float& radius, const float& capsuleCylinderLength) {
    SceneObject capsuleObject = SceneObject();
    addCapsuleCollision(capsuleObject, radius, capsuleCylinderLength);
    return capsuleObject;
}

SceneObject SceneObjectUtilities::createBox(const vec3& halfExtents) {
    SceneObject boxObject = SceneObject();
    addBoxCollision(boxObject, halfExtents);
    return boxObject;
}

SceneObject SceneObjectUtilities::createStaticMesh(const MeshComponentHandle& handle) {
    SceneObject staticMeshObject = SceneObject();
    addMesh(staticMeshObject, handle);
    return staticMeshObject;
}

SceneObject SceneObjectUtilities::createRigidbodySphere(
    const float& radius,
    const float& mass,
    const vec3& initialVelocity
) {
    SceneObject rigidBody = createSphere(radius);
    addPhysics(rigidBody, mass, initialVelocity);
    return rigidBody;
}

SceneObject SceneObjectUtilities::createRigidbodyCapsule(
    const float& radius,
    const float& capsuleCylinderLength,
    const float& mass,
    const vec3& initialVelocity
) {
    SceneObject rigidBody = createCapsule(radius, capsuleCylinderLength);
    addPhysics(rigidBody, mass, initialVelocity);
    return rigidBody;
}

SceneObject SceneObjectUtilities::createRigidbodyBox(
    const vec3& halfExtents,
    const float& mass,
    const vec3& initialVelocity
) {
    SceneObject rigidBody = createBox(halfExtents);
    addPhysics(rigidBody, mass, initialVelocity);
    return rigidBody;
}

SceneObject SceneObjectUtilities::createPointLight(
    const vec3& ambient,
    const vec3& diffuse,
    const vec3& specular,
    const float& constant,
    const float& linear,
    const float& quadratic
) {
    SceneObject pointLightObject = SceneObject();
    addPointLight(pointLightObject, ambient, diffuse, specular, constant, linear, quadratic);
    return pointLightObject;
}

SceneObject SceneObjectUtilities::createDirectionalLight(
    const vec3& ambient,
    const vec3& diffuse,
    const vec3& specular,
    const vec3& direction
) {
    SceneObject directionalLightObject = SceneObject();
    addDirectionalLight(directionalLightObject, ambient, diffuse, specular, direction);
    return directionalLightObject;
}

SceneObject SceneObjectUtilities::createSpotLight(
    const vec3& ambient,
    const vec3& diffuse,
    const vec3& specular,
    const vec3& direction,
    const float& cutOff
) {
    SceneObject spotLightObject = SceneObject();
    addSpotLight(spotLightObject, ambient, diffuse, specular, direction, cutOff);
    return spotLightObject;
}

void SceneObjectUtilities::addSphereCollision(
    SceneObject& sceneObject,
    const float& radius
) {
    sceneObject.setBoundingSphereComponent(BoundingSphereComponent(radius));
}

void SceneObjectUtilities::addCapsuleCollision(
    SceneObject& sceneObject,
    const float& radius,
    const float& capsuleCylinderLength
) {
    sceneObject.setBoundingCapsuleComponent(BoundingCapsuleComponent(radius, capsuleCylinderLength));
}

void SceneObjectUtilities::addBoxCollision(
    SceneObject& sceneObject,
    const vec3& halfExtents
) {
    sceneObject.setBoundingBoxComponent(BoundingBoxComponent(halfExtents));
}

void SceneObjectUtilities::addMesh(
    SceneObject& sceneObject,
    const MeshComponentHandle& meshComponentHandle
) {
    sceneObject.setMeshCompHandle(meshComponentHandle);
}

void SceneObjectUtilities::addPointLight(
    SceneObject& sceneObject,
    const vec3& ambient,
    const vec3& diffuse,
    const vec3& specular,
    const float& constant,
    const float& linear,
    const float& quadratic
) {
    PointLightComponent pointLightComponent = PointLightComponent();
    pointLightComponent.setAmbient(ambient);
    pointLightComponent.setDiffuse(diffuse);
    pointLightComponent.setSpecular(specular);
    pointLightComponent.setConstant(constant);
    pointLightComponent.setLinear(linear);
    pointLightComponent.setQuadratic(quadratic);

    sceneObject.setPointLightComponent(pointLightComponent);
}

void SceneObjectUtilities::addDirectionalLight(
    SceneObject& sceneObject,
    const vec3& ambient,
    const vec3& diffuse,
    const vec3& specular,
    const vec3& direction
) {
    DirectionalLightComponent directionalLightComponent = DirectionalLightComponent();
    directionalLightComponent.setAmbient(ambient);
    directionalLightComponent.setDiffuse(diffuse);
    directionalLightComponent.setSpecular(specular);
    directionalLightComponent.setDirection(direction);

    sceneObject.setDirectionalLightComponent(directionalLightComponent);

}

void SceneObjectUtilities::addSpotLight(
    SceneObject& sceneObject,
    const vec3& ambient,
    const vec3& diffuse,
    const vec3& specular,
    const vec3& direction,
    const float& cutOff
) {
    SpotLightComponent spotLightComponent = SpotLightComponent();
    spotLightComponent.setAmbient(ambient);
    spotLightComponent.setDiffuse(diffuse);
    spotLightComponent.setSpecular(specular);
    spotLightComponent.setDirection(direction);
    spotLightComponent.setCutOff(cutOff);

    sceneObject.setSpotLightComponent(spotLightComponent);
}

void SceneObjectUtilities::addPhysics(
    SceneObject& sceneObject,
    const float& mass,
    const vec3& initialVelocity
) {
    PhysicsComponent physicsComponent = PhysicsComponent();
    physicsComponent.setMass(mass);
    physicsComponent.setVelocity(initialVelocity);
    physicsComponent.setAccumulatedForces(vec3(0.f, 0.f, 0.f));

    sceneObject.setPhysicsComponent(physicsComponent);
}