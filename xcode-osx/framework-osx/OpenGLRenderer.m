#import "OpenGLRenderer.h"
@implementation OpenGLRenderer
#include "gleso.h"
-(id)init{
    NSLog(@"init");
    gleso_init();
    return self;
}
-(void)resizeWithWidth:(GLuint)w AndHeight:(GLuint)h{NSLog(@"resize %dx%d",w,h);gleso_viewport(w,h);}
-(void)render{gleso_step();return;}
@end
