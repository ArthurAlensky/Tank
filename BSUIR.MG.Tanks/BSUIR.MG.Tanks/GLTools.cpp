#include "GLTools.h"

void *gltGetExtensionPointer(const char *szExtensionName)
{
#ifdef WIN32
	// Well, this one is simple. An OpenGL context must be
	// current first. Returns NULL if extension not supported
	return (void *)wglGetProcAddress(szExtensionName);
#endif

#ifdef __APPLE__
	// Mac is a bit more tricky.
	// First we need the bundle
	CFBundleRef openGL = 0;
	SInt16      fwVersion = 0;
	SInt32      fwDir = 0;

	if(FindFolder(kSystemDomain, kFrameworksFolderType, kDontCreateFolder, &fwVersion, &fwDir) != noErr)
		return NULL;

	FSSpec fSpec;
	FSRef  fRef;
	if(FSMakeFSSpec(fwVersion, fwDir, "\pOpenGL.framework", &fSpec) != noErr)
		return NULL;

	FSpMakeFSRef(&fSpec, &fRef);
	CFURLRef url = CFURLCreateFromFSRef(kCFAllocatorDefault, &fRef);
	if(!url)
		return NULL;

	openGL = CFBundleCreate(kCFAllocatorDefault, url);
	CFRelease(url);

	// Then load the function pointer from the bundle
	CFStringRef string = CFStringCreateWithCString(kCFAllocatorDefault, szExtensionName, kCFStringEncodingMacRoman);
	void *pFunc = CFBundleGetFunctionPointerForName(openGL, string);

	// Release the bundle and string
	CFRelease(string);
	CFRelease(openGL);

	// Return the function ponter
	return pFunc;
#endif    
}
