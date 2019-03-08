#include <UIObject.hpp>

using namespace puggo;

UIObject::UIObject(void) {
    colorCompHandle = ColorComponentAllocator::create();
    sizeCompHandle = SizeComponentAllocator::create();
    textCompHandle = TextComponentAllocator::create();
    transform2DCompHandle = Transform2DComponentAllocator::create();
    zIndexCompHandle = ZIndexComponentAllocator::create();
}

UIObject::UIObject(const UIObject& uiObject) {
    colorCompHandle = ColorComponentAllocator::create();
    ColorComponentAllocator::get(colorCompHandle) = ColorComponentAllocator::get(uiObject.getColorCompHandle());

    sizeCompHandle = SizeComponentAllocator::create();
    SizeComponentAllocator::get(sizeCompHandle) = SizeComponentAllocator::get(uiObject.getSizeCompHandle());

    textCompHandle = TextComponentAllocator::create();
    TextComponentAllocator::get(textCompHandle) = TextComponentAllocator::get(uiObject.getTextCompHandle());

    transform2DCompHandle = Transform2DComponentAllocator::create();
    Transform2DComponentAllocator::get(transform2DCompHandle) = Transform2DComponentAllocator::get(uiObject.getTransform2DCompHandle());

    zIndexCompHandle = ZIndexComponentAllocator::create();
    ZIndexComponentAllocator::get(zIndexCompHandle) = ZIndexComponentAllocator::get(uiObject.getZIndexCompHandle());

    meshCompHandle = uiObject.getMeshCompHandle();
}

UIObject::UIObject(UIObject&& uiObject) noexcept {
    swap(colorCompHandle, uiObject.colorCompHandle);
    swap(sizeCompHandle, uiObject.sizeCompHandle);
    swap(textCompHandle, uiObject.textCompHandle);
    swap(transform2DCompHandle, uiObject.transform2DCompHandle);
    swap(zIndexCompHandle, uiObject.zIndexCompHandle);
    
    meshCompHandle = uiObject.getMeshCompHandle();
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
    ColorComponentAllocator::get(colorCompHandle) = ColorComponentAllocator::get(uiObject.getColorCompHandle());
    SizeComponentAllocator::get(sizeCompHandle) = SizeComponentAllocator::get(uiObject.getSizeCompHandle());
    TextComponentAllocator::get(textCompHandle) = TextComponentAllocator::get(uiObject.getTextCompHandle());
    Transform2DComponentAllocator::get(transform2DCompHandle) = Transform2DComponentAllocator::get(uiObject.getTransform2DCompHandle());
    ZIndexComponentAllocator::get(zIndexCompHandle) = ZIndexComponentAllocator::get(uiObject.getZIndexCompHandle());
    meshCompHandle = uiObject.getMeshCompHandle();

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

void UIObject::setColorCompHandle(const ColorComponentHandle& colorCompHandle) noexcept {
    if (ColorComponentAllocator::isValidHandle(this->colorCompHandle)) {
        ColorComponentAllocator::destroy(this->colorCompHandle);
    }

    this->colorCompHandle = colorCompHandle;
}

void UIObject::setSizeCompHandle(const SizeComponentHandle& sizeCompHandle) noexcept {
    if (SizeComponentAllocator::isValidHandle(this->sizeCompHandle)) {
        SizeComponentAllocator::destroy(this->sizeCompHandle);
    }

    this->sizeCompHandle = sizeCompHandle;
}

void UIObject::setTextCompHandle(const TextComponentHandle& textCompHandle) noexcept {
    if (TextComponentAllocator::isValidHandle(this->textCompHandle)) {
        TextComponentAllocator::destroy(this->textCompHandle);
    }

    this->textCompHandle = textCompHandle;
}

void UIObject::setTransform2DCompHandle(const Transform2DComponentHandle& transform2DCompHandle) noexcept {
    if (Transform2DComponentAllocator::isValidHandle(this->transform2DCompHandle)) {
        Transform2DComponentAllocator::destroy(this->transform2DCompHandle);
    }

    this->transform2DCompHandle = transform2DCompHandle;
}

void UIObject::setZIndexCompHandle(const ZIndexComponentHandle& zIndexCompHandle) noexcept {
    if (ZIndexComponentAllocator::isValidHandle(this->zIndexCompHandle)) {
        ZIndexComponentAllocator::destroy(this->zIndexCompHandle);
    }

    this->zIndexCompHandle = zIndexCompHandle;
}

void UIObject::setMeshCompHandle(const MeshComponentHandle& meshCompHandle) noexcept {
    this->meshCompHandle = meshCompHandle;
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