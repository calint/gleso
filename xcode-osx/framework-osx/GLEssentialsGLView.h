#define ESSENTIAL_GL_PRACTICES_SUPPORT_GL3 1
#import <OpenGL/gl3.h>
@interface GLEssentialsGLView:NSOpenGLView{
	CVDisplayLinkRef displayLink;
}
@end
