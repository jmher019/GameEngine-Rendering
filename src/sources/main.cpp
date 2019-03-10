#include <SceneGraph.hpp>



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

        ZIndexComponentAllocator::deallocate();
        Transform2DComponentAllocator::init();
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