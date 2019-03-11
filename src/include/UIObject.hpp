#ifndef PUGGO_UI_OBJECT_HPP
#define PUGGO_UI_OBJECT_HPP

#include <ComponentAllocators.hpp>

#include <Vertex.hpp>

namespace puggo {
    class UIObject {
    public:
        UIObject(void);
        UIObject(const UIObject& uiObject);
        UIObject(UIObject&& uiObject) noexcept;
        ~UIObject(void);

        UIObject& operator=(const UIObject& uiObject);
        UIObject& operator=(UIObject&& uiObject) noexcept;

        const ColorComponentHandle& getColorCompHandle(void) const noexcept;
        const SizeComponentHandle& getSizeCompHandle(void) const noexcept;
        const TextComponentHandle& getTextCompHandle(void) const noexcept;
        const Transform2DComponentHandle& getTransform2DCompHandle(void) const noexcept;
        const ZIndexComponentHandle& getZIndexCompHandle(void) const noexcept;
        const MeshComponentHandle& getMeshCompHandle(void) const noexcept;

        void setMeshCompHandle(const MeshComponentHandle& meshCompHandle) noexcept;

        ColorComponent* getColorComponent(void) const noexcept;
        SizeComponent* getSizeComponent(void) const noexcept;
        TextComponent* getTextComponent(void) const noexcept;
        Transform2DComponent* getTransform2DComponent(void) const noexcept;
        ZIndexComponent* getZIndexComponent(void) const noexcept;
        MeshComponent* getMeshComponent(void) const noexcept;

        void setColorComponent(const ColorComponent& colorComponent) noexcept;
        void setSizeComponent(const SizeComponent& sizeComponent) noexcept;
        void setTextComponent(const TextComponent& textComponent) noexcept;
        void setTransform2DComponent(const Transform2DComponent& transform2DComponent) noexcept;
        void setZIndexComponent(const ZIndexComponent& zIndexComponent) noexcept;

    private:
        // Every UIObject has unique color, text, size, transform2D, and zindex components
        // Mesh components are the exception since they can be shared
        ColorComponentHandle colorCompHandle = { 262143, 16383 };
        SizeComponentHandle sizeCompHandle = { 262143, 16383 };
        TextComponentHandle textCompHandle = { 262143, 16383 };
        Transform2DComponentHandle transform2DCompHandle = { 262143, 16383 };
        ZIndexComponentHandle zIndexCompHandle = { 262143, 16383 };

        MeshComponentHandle meshCompHandle = { 1023, 4194303 };
    };

    vector<Vertex> computeVertices(const UIObject& uiObject) noexcept;
}

#endif // !PUGGO_UI_OBJECT_HPP
