/*!
\brief OpenGL ES implementation of the PVRApi Default Fbo (Frame Buffer Object).
\file PVRApi/OGLES/FboGles.h
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/
#pragma once
#include "PVRApi/ApiObjects/Fbo.h"
#include "PVRNativeApi/OGLES/NativeObjectsGles.h"
namespace pvr {
namespace api {
namespace gles {

class FboGles_ : public impl::Fbo_, public  native::HFbo_
{
public:
	FboGles_(const GraphicsContext& context);
	virtual void bind(IGraphicsContext& _context, types::FboBindingTarget types)const;
	void destroy();
	bool init(const FboCreateParam& desc);
	bool checkFboStatus(GraphicsContext& context);
	const RenderPass& getRenderPass()const { return _desc.renderPass; }
	RenderPass& getRenderPass() { return _desc.renderPass; }

	virtual ~FboGles_() {}

	mutable types::FboBindingTarget _target;
	std::vector<TextureView> _colorAttachments;
	std::vector<TextureView> _depthStencilAttachment;
};

/// <summary>OpenGL ES Default FBO (FBO pointing to the Back Buffer). This object is necessary for rendering anything
/// to the screen. Should be used through the Fbo object. If a GLES direct manipulation is required, use through
/// the DefaultFboGles Reference counted Framework object.</summary>
class DefaultFboGles_ : public FboGles_
{
public:
	/// <summary>Constructor. Construct a new FBO on the provided context.</summary>
	DefaultFboGles_(const GraphicsContext& context);

	/// <summary>INTERNAL OGLES: Initialize this fbo with provided parameters.</summary>
	/// <returns>pvr::Result::Success on success</returns>
	bool init(const FboCreateParam& desc)
	{
		_desc = desc;
		handle = 0;
		return true;
	}

	//\brief INTERNAL OGLES: Return true if this is a default fbo (overload).
	bool isDefault()const { return true; }

	//\brief INTERNAL OGLES: Bind this fbo.
	//\param context Bind on this context
	//\param target Bind on this target
	void bind(IGraphicsContext& context, types::FboBindingTarget target)const;

	//\brief INTERNALCheck the status of this fbo.
	//\return return true on success
	bool checkFboStatus(GraphicsContext& context);
};
//OpenGL ES Default FBO (FBO pointing to the Back Buffer). This object is necessary for rendering anything to the screen. Reference counted.
typedef RefCountedResource<DefaultFboGles_> DefaultFboGles;
typedef RefCountedResource<FboGles_> FboGles;
}
}
}
