#include <SceneGraph.hpp>
#include <SceneObjectUtilities.hpp>
#include <UIObject.hpp>


int main() {
    try {
        AllocationSystem::init(AllocationSystem::THREE_GIGABYTE);
        TransformComponentAllocator::init();
        BoundingBoxComponentAllocator::init();
        BoundingCapsuleComponentAllocator::init();
        BoundingSphereComponentAllocator::init();
        PointLightComponentAllocator::init();
        DirectionalLightComponentAllocator::init();
        SpotLightComponentAllocator::init();
        PhysicsComponentAllocator::init();
        MeshComponentAllocator::init();
        ColorComponentAllocator::init();
        SizeComponentAllocator::init();
        TextComponentAllocator::init();
        Transform2DComponentAllocator::init();
        ZIndexComponentAllocator::init();

        // All scene objects should be created in this scope only
        // The reason is that Scene objects should go out of scope before the component allocators
        // are deallocated
        {
            SceneObject a;
            if (a.getTransformComponent() == nullptr) {
                cout << "transform is a nullptr" << endl;
            }

            SceneObject rigidBody = SceneObjectUtilities::createRigidbodySphere(1.f, 1.f, vec3(0.f, 0.f, 0.f));
            if (rigidBody.getTransformComponent() == nullptr) {
                cout << "transform is a nullptr" << endl;
            }
            if (rigidBody.getBoundingSphereComponent() == nullptr) {
                cout << "bounding sphere is a nullptr" << endl;
            }
            if (rigidBody.getPhysicsComponent() == nullptr) {
                cout << "physics is a nullptr" << endl;
            }

            UIObject ui;
            if (ui.getColorComponent() == nullptr) {
                cout << "color is a nullptr" << endl;
            }
            if (ui.getSizeComponent() == nullptr) {
                cout << "size is a nullptr" << endl;
            }
            if (ui.getTextComponent() == nullptr) {
                cout << "text is a nullptr" << endl;
            }
            if (ui.getTransform2DComponent() == nullptr) {
                cout << "transform 2D is a nullptr" << endl;
            }
            if (ui.getZIndexComponent() == nullptr) {
                cout << "z index is a nullptr" << endl;
            }
        }

        ZIndexComponentAllocator::deallocate();
        Transform2DComponentAllocator::deallocate();
        TextComponentAllocator::deallocate();
        SizeComponentAllocator::deallocate();
        ColorComponentAllocator::deallocate();
        MeshComponentAllocator::deallocate();
        PhysicsComponentAllocator::deallocate();
        SpotLightComponentAllocator::deallocate();
        DirectionalLightComponentAllocator::deallocate();
        PointLightComponentAllocator::deallocate();
        BoundingSphereComponentAllocator::deallocate();
        BoundingCapsuleComponentAllocator::deallocate();
        BoundingBoxComponentAllocator::deallocate();
        TransformComponentAllocator::deallocate();
    }
    catch (exception e) {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}