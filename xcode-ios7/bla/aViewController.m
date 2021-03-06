#import"aViewController.h"
@interface aViewController(){}
    @property(strong,nonatomic)EAGLContext*context;
    @property(strong,nonatomic)GLKBaseEffect*effect;
    -(void)setupGL;
    -(void)tearDownGL;
@end

@implementation aViewController
-(void)viewDidLoad{
    [super viewDidLoad];
    self.context=[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!self.context)NSLog(@"Failed to create ES context");
    GLKView*view=(GLKView*)self.view;
    view.context = self.context;
    view.drawableDepthFormat=GLKViewDrawableDepthFormat24;
    [self setupGL];
}

-(void)dealloc{
    [self tearDownGL];
    if([EAGLContext currentContext]==self.context){
        [EAGLContext setCurrentContext:nil];
    }
}

-(void)didReceiveMemoryWarning{
    [super didReceiveMemoryWarning];
    if ([self isViewLoaded]&&([[self view] window]==nil)){
        self.view=nil;
        [self tearDownGL];
        if([EAGLContext currentContext]==self.context){
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}
#include "gleso.h"
-(void)setupGL{[EAGLContext setCurrentContext:self.context];if(gleso_init())NSLog(@"gleso init failed");}
-(void)tearDownGL{[EAGLContext setCurrentContext:self.context];}
#pragma mark - GLKView and GLKViewController delegate methods
-(void)update{}
-(void)glkView:(GLKView*)view drawInRect:(CGRect)rect{gleso_step();}
#pragma mark -  OpenGL ES 2 shader compilation
@end
