#include <UIObject.hpp>

using namespace puggo;

UIObject::UIObject(void) {
    setColorComponent({});
    setSizeComponent({});
    setTextComponent({});
    setTransform2DComponent({});
    setZIndexComponent({});
}

UIObject::UIObject(const UIObject& uiObject) {
    setColorComponent(*uiObject.getColorComponent());
    setSizeComponent(*uiObject.getSizeComponent());
    setTextComponent(*uiObject.getTextComponent());
    setTransform2DComponent(*uiObject.getTransform2DComponent());
    setZIndexComponent(*uiObject.getZIndexComponent());
    setMeshCompHandle(uiObject.getMeshCompHandle());
}

UIObject::UIObject(UIObject&& uiObject) noexcept {
    swap(colorCompHandle, uiObject.colorCompHandle);
    swap(sizeCompHandle, uiObject.sizeCompHandle);
    swap(textCompHandle, uiObject.textCompHandle);
    swap(transform2DCompHandle, uiObject.transform2DCompHandle);
    swap(zIndexCompHandle, uiObject.zIndexCompHandle);
    
    setMeshCompHandle(uiObject.getMeshCompHandle());
}

UIObject::~UIObject(void) {
    if (ColorComponentAllocator::isValidHandle(colorCompHandle)) {
        ColorComponentAllocator::destroy(colorCompHandle);
    }

    if (SizeComponentAllocator::isValidHandle(sizeCompHandle)) {
        SizeComponentAllocator::destroy(sizeCompHandle);
    }

    if (TextComponentAllocator::isValidHandle(textCompHandle)) {
        TextComponentAllocator::destroy(textCompHandle);
    }

    if (Transform2DComponentAllocator::isValidHandle(transform2DCompHandle)) {
        Transform2DComponentAllocator::destroy(transform2DCompHandle);
    }

    if (ZIndexComponentAllocator::isValidHandle(zIndexCompHandle)) {
        ZIndexComponentAllocator::destroy(zIndexCompHandle);
    }

    // Mesh Component Handle is destroyed elsewhere
}

UIObject& UIObject::operator=(const UIObject& uiObject) {
    setColorComponent(*uiObject.getColorComponent());
    setSizeComponent(*uiObject.getSizeComponent());
    setTextComponent(*uiObject.getTextComponent());
    setTransform2DComponent(*uiObject.getTransform2DComponent());
    setZIndexComponent(*uiObject.getZIndexComponent());
    setMeshCompHandle(uiObject.getMeshCompHandle());

    return *this;
}

UIObject& UIObject::operator=(UIObject&& uiObject) noexcept {
    swap(colorCompHandle, uiObject.colorCompHandle);
    swap(sizeCompHandle, uiObject.sizeCompHandle);
    swap(textCompHandle, uiObject.textCompHandle);
    swap(transform2DCompHandle, uiObject.transform2DCompHandle);
    swap(zIndexCompHandle, uiObject.zIndexCompHandle);
    swap(meshCompHandle, uiObject.meshCompHandle);

    return *this;
}

const ColorComponentHandle& UIObject::getColorCompHandle(void) const noexcept {
    return colorCompHandle;
}

const SizeComponentHandle& UIObject::getSizeCompHandle(void) const noexcept {
    return sizeCompHandle;
}

const TextComponentHandle& UIObject::getTextCompHandle(void) const noexcept {
    return textCompHandle;
}

const Transform2DComponentHandle& UIObject::getTransform2DCompHandle(void) const noexcept {
    return transform2DCompHandle;
}

const ZIndexComponentHandle& UIObject::getZIndexCompHandle(void) const noexcept {
    return zIndexCompHandle;
}

const MeshComponentHandle& UIObject::getMeshCompHandle(void) const noexcept {
    return meshCompHandle;
}

void UIObject::setMeshCompHandle(const MeshComponentHandle& meshCompHandle) noexcept {
    this->meshCompHandle = meshCompHandle;
}

ColorComponent* UIObject::getColorComponent(void) const noexcept {
    if (ColorComponentAllocator::isValidHandle(colorCompHandle)) {
        return &ColorComponentAllocator::get(colorCompHandle);
    }

    return nullptr;
}

SizeComponent* UIObject::getSizeComponent(void) const noexcept {
    if (SizeComponentAllocator::isValidHandle(sizeCompHandle)) {
        return &SizeComponentAllocator::get(sizeCompHandle);
    }

    return nullptr;
}

TextComponent* UIObject::getTextComponent(void) const noexcept {
    if (TextComponentAllocator::isValidHandle(textCompHandle)) {
        return &TextComponentAllocator::get(textCompHandle);
    }

    return nullptr;
}

Transform2DComponent* UIObject::getTransform2DComponent(void) const noexcept {
    if (Transform2DComponentAllocator::isValidHandle(transform2DCompHandle)) {
        return &Transform2DComponentAllocator::get(transform2DCompHandle);
    }

    return nullptr;
}

ZIndexComponent* UIObject::getZIndexComponent(void) const noexcept {
    if (ZIndexComponentAllocator::isValidHandle(zIndexCompHandle)) {
        return &ZIndexComponentAllocator::get(zIndexCompHandle);
    }

    return nullptr;
}

MeshComponent* UIObject::getMeshComponent(void) const noexcept {
    if (MeshComponentAllocator::isValidHandle(meshCompHandle)) {
        return &MeshComponentAllocator::get(meshCompHandle);
    }

    return nullptr;
}

void UIObject::setColorComponent(const ColorComponent& colorComponent) noexcept {
    if (!ColorComponentAllocator::isValidHandle(colorCompHandle)) {
        colorCompHandle = ColorComponentAllocator::create();
    }

    ColorComponentAllocator::get(colorCompHandle) = colorComponent;
}

void UIObject::setSizeComponent(const SizeComponent& sizeComponent) noexcept {
    if (!SizeComponentAllocator::isValidHandle(sizeCompHandle)) {
        sizeCompHandle = SizeComponentAllocator::create();
    }

    SizeComponentAllocator::get(sizeCompHandle) = sizeComponent;
}

void UIObject::setTextComponent(const TextComponent& textComponent) noexcept {
    if (!TextComponentAllocator::isValidHandle(textCompHandle)) {
        textCompHandle = TextComponentAllocator::create();
    }

    TextComponentAllocator::get(textCompHandle) = textComponent;
}

void UIObject::setTransform2DComponent(const Transform2DComponent& transform2DComponent) noexcept {
    if (!Transform2DComponentAllocator::isValidHandle(transform2DCompHandle)) {
        transform2DCompHandle = Transform2DComponentAllocator::create();
    }

    Transform2DComponentAllocator::get(transform2DCompHandle) = transform2DComponent;
}

void UIObject::setZIndexComponent(const ZIndexComponent& zIndexComponent) noexcept {
    if (!ZIndexComponentAllocator::isValidHandle(zIndexCompHandle)) {
        zIndexCompHandle = ZIndexComponentAllocator::create();
    }

    ZIndexComponentAllocator::get(zIndexCompHandle) = zIndexComponent;
}

vector<Vertex> puggo::computeVertices(const UIObject& uiObject) noexcept {
    const float z = computeActualZIndex(ZIndexComponentAllocator::get(uiObject.getZIndexCompHandle()));
    const SizeComponent& size = SizeComponentAllocator::get(uiObject.getSizeCompHandle());
    const Vertex ul = {
        vec3(0.f, 0.f, z),
        vec3(0.f, 0.f, 1.f),
        vec3(0.f, 0.f, 0.f),
        vec2(0.f, 0.f)
    };
    const Vertex ur = {
        vec3(size.width, 0.f, z),
        vec3(0.f, 0.f, 1.f),
        vec3(0.f, 0.f, 0.f),
        vec2(0.f, 0.f)
    };
    const Vertex lr = {
        vec3(size.width, size.height, z),
        vec3(0.f, 0.f, 1.f),
        vec3(0.f, 0.f, 0.f),
        vec2(0.f, 0.f)
    };
    const Vertex ll = {
        vec3(0.f, size.height, z),
        vec3(0.f, 0.f, 1.f),
        vec3(0.f, 0.f, 0.f),
        vec2(0.f, 0.f)
    };
    return {
        ul,
        ll,
        ur,
        ur,
        lr,
        ll
    };
}