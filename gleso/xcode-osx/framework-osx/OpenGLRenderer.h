@interface OpenGLRenderer:NSObject{}
-(id)init;
-(void)resizeWithWidth:(GLuint)width AndHeight:(GLuint)height;
-(void)render;
@end
