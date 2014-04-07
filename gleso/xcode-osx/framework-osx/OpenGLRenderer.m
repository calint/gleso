#import "OpenGLRenderer.h"
@implementation OpenGLRenderer
#include "gleso.h"
-(id)init{NSLog(@"init");if(gleso_init()){NSLog(@"could not init");return -1;}return self;}
-(void)resizeWithWidth:(GLuint)w AndHeight:(GLuint)h{NSLog(@"resize %dx%d",w,h);gleso_on_viewport_change(w,h);}
-(void)render{gleso_step();return;}
@end
