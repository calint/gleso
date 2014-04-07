#include"gleso.h"
#include<stdlib.h>
#include<string.h>

static const char vertex_shader_source[]="#version 100\nuniform mat4 umvp;attribute vec4 apos;void main(){gl_Position=umvp*apos;}";
static const char fragment_shader_source[]="#version 100\nvoid main(){gl_FragColor=vec4(0.0,1.0,0.0,1.0);}";
//static const char vertex_shader_source[]="attribute vec4 apos;void main(){gl_Position=apos;}";
//static const char fragment_shader_source[]="precision mediump float;void main(){gl_FragColor=vec4(0.0,1.0,0.0,1.0);}";

class shader;
namespace gl{
	shader*shdr;
	GLuint apos;// vec4 position x,y,z,w
    GLuint umvp;// mat4 model-world-view-projection matrix
}

class shader{
	GLuint glid_program;
	GLuint apos,umvp;
public:
	~shader(){
		if(glid_program){
			glDeleteProgram(glid_program);
            //			LOGI("program deleted %d\n",glid_program);
			glid_program=0;
		}
	}
	static void printGLString(const char *name,const GLenum s){
		const char*v=(const char*)glGetString(s);
		p("GL %s = %s\n",name,v);
	}
    
	static bool checkGlError(const char*op){
		bool err=false;
        for (GLint error=glGetError();error;error=glGetError()){
			p("at %s() glError (0x%x):  %s\n",op,error,"");
            err=true;
        }
        return err;
	}
    
    
    static inline const char * GetGLErrorString(GLenum error)
    {
        const char *str;
        switch( error )
        {
            case GL_NO_ERROR:
                str = "GL_NO_ERROR";
                break;
            case GL_INVALID_ENUM:
                str = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                str = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                str = "GL_INVALID_OPERATION";
                break;
#if defined __gl_h_ || defined __gl3_h_
            case GL_OUT_OF_MEMORY:
                str = "GL_OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                str = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
#endif
#if defined __gl_h_
            case GL_STACK_OVERFLOW:
                str = "GL_STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                str = "GL_STACK_UNDERFLOW";
                break;
            case GL_TABLE_TOO_LARGE:
                str = "GL_TABLE_TOO_LARGE";
                break;
#endif
            default:
                str = "(ERROR: Unknown Error Enum)";
                break;
        }
        return str;
    }
    

	static GLuint loadShader(const GLenum shader_type,const char*source){
		//throw "error";
 		const GLuint shader=glCreateShader(shader_type);
 		if(!shader)return 0;
		glShaderSource(shader,1,&source,NULL);
		glCompileShader(shader);
		GLint compiled=0;
		glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
//		LOGE("compiled: %d\n",compiled);
		if(compiled)return shader;
		GLint infolen=0;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infolen);
//		LOGE("info log len: %d\n",infolen);
		if(!infolen)return 0;
		char*buf=(char*)malloc(infolen);
		if(!buf)return 0;
		glGetShaderInfoLog(shader,infolen,NULL,buf);
		p("Could not compile shader %d:\n%s\n",shader_type, buf);
		free(buf);
		glDeleteShader(shader);
		return 0;
	}
    
	bool load(){
        checkGlError("load call");
	    printGLString("GL_VERSION",GL_VERSION);
	    printGLString("GL_VENDOR",GL_VENDOR);
	    printGLString("GL_RENDERER",GL_RENDERER);
        //	    printGLString("Extensions",GL_EXTENSIONS);
	    printGLString("GL_SHADING_LANGUAGE_VERSION",GL_SHADING_LANGUAGE_VERSION);
        checkGlError("");
        
//        if(glid_program){
//        	glDeleteProgram(glid_program);
//            checkGlError("delete program");
//        	LOGI("deleted opengl program %d\n",glid_program);
//        }
	    createProgram(vertex_shader_source,fragment_shader_source);
        checkGlError("program");
	    apos=glGetAttribLocation(glid_program,"apos");
//		LOGE("apos: %d\n",apos);
	    checkGlError("glGetAttribLocation");
	    if(apos==-1)return false;
        
        umvp=glGetUniformLocation(glid_program,"umvp");
//        LOGE("umvp: %d\n",umvp);
	    checkGlError("glGetUniformLocation umvp");
	    if(umvp==-1)return false;

	    return true;
        //	    LOGI("glGetAttribLocation(\"apos\")=%d\n",apos);
	}
	void on_viewport_change(const int wi,const int hi){
        //	    LOGI("on_viewport_change  %d x %d",wi,hi);
	    glViewport(0,0,wi,hi);
        //	    checkGlError("glViewport");
	}
	void use_program(){
		glUseProgram(glid_program);
		gl::apos=apos;
        gl::umvp=umvp;
	}
//	void step(){
////	    static float grey;
////	    grey += 0.01f;
////	    if (grey > 1.0f) {
////	        grey = 0.0f;
////	    }
//        //		LOGI("frame %d\n",frameno++);
//	    glClearColor(0,0,0,1);
////        checkGlError("glClearColor");
//	    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
////        checkGlError("glClear");
//	    use_program();
////        checkGlError("glUseProgram");
//	}
    
protected:
	bool createProgram(const char*vertex_shader_source,const char*fragment_shader_source){
		GLuint glid_vertex_shader=loadShader(GL_VERTEX_SHADER,vertex_shader_source);
		if(!glid_vertex_shader)return false;
        
		GLuint glid_pixel_shader=loadShader(GL_FRAGMENT_SHADER,fragment_shader_source);
		if(!glid_pixel_shader)return false;
        
		glid_program=glCreateProgram();
		if(!glid_program)return false;
//        LOGE("program %d  shaders %d %d\n",glid_program,glid_vertex_shader,glid_pixel_shader);
        
		glAttachShader(glid_program,glid_vertex_shader);
		checkGlError("glAttachShader vertex");
		glAttachShader(glid_program,glid_pixel_shader);
		checkGlError("glAttachShader fragment");
		glLinkProgram(glid_program);
		GLint linkStatus=GL_FALSE;
		glGetProgramiv(glid_program,GL_LINK_STATUS,&linkStatus);
		if(linkStatus)return true;
        
		GLint bufLength=0;
		glGetProgramiv(glid_program,GL_INFO_LOG_LENGTH,&bufLength);
		if(bufLength){
			char*buf=(char*)malloc(bufLength);
			if(buf){
				glGetProgramInfoLog(glid_program,bufLength,NULL,buf);
				p("Could not link program:\n%s\n",buf);
				free(buf);
			}
		}
		glDeleteProgram(glid_program);
		glid_program=0;
		return false;
	}
};

////////////////////////////////////////////////
#include<vector>
class glo{
#ifdef GLESO_EMBEDDED
    std::vector<GLfloat>vertices;
#else
    GLuint glid_vao;
    GLuint glid_buffer_vertices;
#endif
public:
	virtual~glo(){p("~glo(%p)\n",this);}
	int load(){
//		p("glo load\n");
#ifdef GLESO_EMBEDDED
        vertices=make_vertices();
#else
        glGenVertexArrays(1,&glid_vao);
        glBindVertexArray(glid_vao);
        glGenBuffers(1,&glid_buffer_vertices);
        glBindBuffer(GL_ARRAY_BUFFER,glid_buffer_vertices);
        const std::vector<GLfloat>vec=verties();
        glBufferData(GL_ARRAY_BUFFER,vec.size()*sizeof(GLfloat),vec.data(),GL_STATIC_DRAW);
        if(shader::checkGlError("load"))return 1;
#endif
		return 0;
	}
	void render()const{
#ifdef GLESO_EMBEDDED
        shader::checkGlError("enter rend");
	    glVertexAttribPointer(gl::apos,2,GL_FLOAT,GL_FALSE,0,vertices.data());
        shader::checkGlError("vertexattrib");
	    glEnableVertexAttribArray(gl::apos);
        shader::checkGlError("enable");
#else
        shader::checkGlError("enter rend");
        glBindVertexArray(glid_vao);
        shader::checkGlError("bind 1");
        glBindBuffer(GL_ARRAY_BUFFER,glid_buffer_vertices);
        shader::checkGlError("bind");
        glEnableVertexAttribArray(gl::apos);
        shader::checkGlError("enable");
        glVertexAttribPointer(gl::apos,2,GL_FLOAT,GL_FALSE,0,0);
        shader::checkGlError("vertexattrib");
#endif
        gldraw();
        shader::checkGlError("draw");
    }
protected:
    inline virtual std::vector<GLfloat>make_vertices(){
        const GLfloat verts[]={0,.5f, -.5f,-.5f, .5f,-.5f};
        return std::vector<GLfloat>(std::begin(verts),std::end(verts));
    }
    inline virtual void gldraw()const{
        glDrawArrays(GL_TRIANGLES,0,3);
    }
};

class glo_square:public glo{
    inline virtual std::vector<GLfloat>make_vertices(){
        const GLfloat verts[]={-1,1, -1,-1, 1,-1, 1,1};
        return std::vector<GLfloat>(std::begin(verts),std::end(verts));
    }
    inline virtual void gldraw()const{
        glDrawArrays(GL_TRIANGLE_FAN,0,4);
    }
    
};

class p3{
public:
    inline p3():x_(0),y_(0),z_(0){}
    inline p3(const floato x):x_(x),y_(0),z_(0){}
    inline p3(const floato x,const floato y):x_(x),y_(y),z_(0){}
    inline p3(const p3&p):x_(p.x_),y_(p.y_),z_(p.z_){}
    inline p3&x(const floato f){x_=f;return*this;}inline const floato x()const{return x_;}
    inline p3&y(const floato f){y_=f;return*this;}inline const floato y()const{return y_;}
    inline p3&z(const floato f){z_=f;return*this;}inline const floato z()const{return z_;}
    inline p3&add(const p3&p,const floato dt){x_+=p.x_*dt;y_+=p.y_*dt;z_+=p.z_*dt;return*this;}//? simd
private:
    floato x_,y_,z_;
};

#include<list>
class grid;
namespace gleso{
    floato dt;
    inline floato d(const floato unit_over_second){return unit_over_second*dt;}
    unsigned int tick;//?? rollover issues when used in comparisons
    std::vector<glo*>glos;
    grid*grd;
    const floato rnd(){return floato(rand())/RAND_MAX;}
}

class physics{
public:
    void update(){
        dp.add(ddp,gleso::dt);
        p.add(dp,gleso::dt);
        da.add(dda,gleso::dt);
        a.add(da,gleso::dt);
    }
    inline p3&pos(){return p;}
    inline p3&position(){return p;}inline p3&dpos(){return dp;}
    inline p3&angle(){return a;}inline p3&dagl(){return da;}
    inline p3&scale(){return s;}
private:
    p3 p,dp,ddp;//position
    p3 a,da,dda;//angle
    p3 s;//scale
    //? list of forces/velocities applied
};

class render_info{
public:
    inline const p3&position()const{return p;}
    inline render_info&position(const p3&p){this->p=p;return*this;}
    inline const p3&angle()const{return a;}
    inline render_info&angle(const p3&a){this->a=a;return*this;}
    inline const p3&scale()const{return s;}
    inline render_info&scale(const p3&s){this->s=s;return*this;}
private:
    p3 p,a,s;
};

////
// lifted from apple examples
static void mtxLoadTranslate(floato*mtx,const floato xTrans,const floato yTrans,const floato zTrans){
	// [ 0 4  8  x ]
	// [ 1 5  9  y ]
	// [ 2 6 10  z ]
	// [ 3 7 11 15 ]
	mtx[ 0] = mtx[ 5] = mtx[10] = mtx[15] = 1;
	
	mtx[ 1] = mtx[ 2] = mtx[ 3] = mtx[ 4] =
	mtx[ 6] = mtx[ 7] = mtx[ 8] = mtx[ 9] =
	mtx[11] = 0.0;
	
	mtx[12] = xTrans;
	mtx[13] = yTrans;
	mtx[14] = zTrans;
}
#include<math.h>
static void mtxRotateZApply(floato* mtx, floato deg)
{
	// [ 0 4  8 12 ]   [ cos -sin 0  0 ]
	// [ 1 5  9 13 ] x [ sin cos  0  0 ]
	// [ 2 6 10 14 ]   [ 0   0    1  0 ]
	// [ 3 7 11 15 ]   [ 0   0    0  1 ]

	float rad = deg * (M_PI/180.0f);

	float cosrad = cosf(rad);
	float sinrad = sinf(rad);

	float mtx00 = mtx[0];
	float mtx01 = mtx[1];
	float mtx02 = mtx[2];
	float mtx03 = mtx[3];

	mtx[ 0] = mtx[ 4]*sinrad + mtx00*cosrad;
	mtx[ 4] = mtx[ 4]*cosrad - mtx00*sinrad;

	mtx[ 1] = mtx[ 5]*sinrad + mtx01*cosrad;
	mtx[ 5] = mtx[ 5]*cosrad - mtx01*sinrad;

	mtx[ 2] = mtx[ 6]*sinrad + mtx02*cosrad;
	mtx[ 6] = mtx[ 6]*cosrad - mtx02*sinrad;

	mtx[ 3] = mtx[ 7]*sinrad + mtx03*cosrad;
	mtx[ 7] = mtx[ 7]*cosrad - mtx03*sinrad;
}
void mtxScaleApply(floato* mtx, floato xScale, floato yScale, floato zScale)
{
    // [ 0 4  8 12 ]   [ x 0 0 0 ]
    // [ 1 5  9 13 ] x [ 0 y 0 0 ]
    // [ 2 6 10 14 ]   [ 0 0 z 0 ]
    // [ 3 7 11 15 ]   [ 0 0 0 1 ]
	
	mtx[ 0] *= xScale;
	mtx[ 4] *= yScale;
	mtx[ 8] *= zScale;
	
	mtx[ 1] *= xScale;
	mtx[ 5] *= yScale;
	mtx[ 9] *= zScale;
	
	mtx[ 2] *= xScale;
	mtx[ 6] *= yScale;
	mtx[10] *= zScale;
	
	mtx[ 3] *= xScale;
	mtx[ 7] *= yScale;
	mtx[11] *= xScale;
}
class m4{
    floato c[16];
public:
    m4():c{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }{}
    inline m4&load_translate(const p3&p){mtxLoadTranslate(c,p.x(),p.y(),p.z());return*this;}
    inline m4&append_rotation_about_z_axis(const floato degrees){mtxRotateZApply(c,degrees);return*this;}
    inline m4&append_scaling(const p3&scale){mtxScaleApply(c,scale.x(),scale.y(),scale.z());return*this;}
    inline const floato*array()const{return c;}
};
namespace metrics{
    unsigned int fps;
    unsigned int nglobs;
    void log(){p("/ metrics fps:%03d – globs:%05d\n",fps,nglobs);}
};
//class linked_list{
//	linked_list*nxt;
//	linked_list*prv;
//};
//class glob:public linked_list{
class glob{
	const class glo*glo;
    class physics phys;// current physics state
    class physics phys_prv;// previous physics state
    class physics phys_nxt;// next physics state, computed during update
    m4 matrix_model_world;
    class render_info render_info;// info for opengl rendering
    class render_info render_info_next;// next renderinfo, updated during render
    p3 scal;
public:
	glob():glo(0){metrics::nglobs++;}
	virtual ~glob(){}
	inline glob&glo_ref(const class glo*g){glo=g;return*this;}
    inline class physics&physics(){return phys;}
    inline const p3&scale()const{return scal;}
    inline glob&scale(const p3&scale){scal=scale;return*this;}
	void render(){
		if(!glo)return;
        render_info=render_info_next;
        matrix_model_world.load_translate(render_info.position());
        matrix_model_world.append_rotation_about_z_axis(render_info.angle().z());
        matrix_model_world.append_scaling(render_info.scale());
//        LOGI("scale x %f\n",render_info.scale().x());
        glUniformMatrix4fv(gl::umvp,1,false,matrix_model_world.array());
        glo->render();
	}
    void update(){
        phys_prv=phys;
        phys.scale()=scal;
        phys.update();
        on_update();
        render_info_next.position(phys.position());
        render_info_next.angle(phys.angle());
        render_info_next.scale(phys.scale());
    }
    virtual void on_update(){
        if(phys.pos().x()>1)phys.dpos().x(-phys.dpos().x());
        else if(phys.pos().x()<-1)phys.dpos().x(-phys.dpos().x());
    }
};


   /////  ///\   ///// ///// /////////
   ///   ///\\\  ///   ///  // /// //
  ///   ///  \\\///   ///     ///
///// /////   \\\/  /////   /////


//#ifndef GLESO_EMBEDDED
//const int nsprites=1024*16;
//#else
//const int nsprites=1024;
//#endif
const int nsprites=32;
static void gleso_impl_add_glos(std::vector<glo*>&glos){
    glos.push_back(/*gives*/new glo());//? leak? push_pack does not /*take*/ ownership of object.
    glos.push_back(/*gives*/new glo_square());//? leak? push_pack does not /*take*/ ownership of object.
}
static/*gives*/glob*gleso_impl_create_root(){
    glob*g=new glob();
    g->scale(p3{.1,.1}).glo_ref(gleso::glos[1]);
    physics&p=g->physics();
    p.pos().x(2*gleso::rnd()-1);
    p.pos().y(2*gleso::rnd()-1);
    p.dpos().x(.01);
    p.dagl().z(360/60);
    return g;
}
// ascii sprite kit
//
//             ____
//            |O  O|
//            |_  _|         <- "medusa"
//             /||\
//
// _______________
//   |____|     <- stuff to slide under
//  //||\|\\
//
//
// _______________     <- floor and roof
//
//
//
//
//     _\|/_
// _____/ \_______   <- stuff to jump over
//
//
//
//       stuff to scores -->   . o O *     <-- stuff to avoid getting hit by
//
//
#include<algorithm>
#define foreach(c,f)std::for_each(c.begin(),c.end(),f)
class grid{
	std::list<glob*>globs;//                        _
public://                                          (:)
	grid(){}//                                    __|__         <- "long neck"
    void add(glob*g){globs.push_back(g);}        //(.)\\          //
    void update(){foreach(globs,[](glob*g){g->update();});}//? multicore?
    void render(){foreach(globs,[](glob*g){g->render();});}// single thread opengl rendering
    void rem(glob*g){globs.remove(g);}//? multicore?||
    void clr(){globs.clear();}
    //    void refresh(){}// refreshes the grid, globs dont change grid often, globs totallyinside (often) remain in grid, if maximum glob size less than grid size then    <-- procedurally generated text for vegetation
};

#include<sys/time.h>
//static void log_metrics();
namespace fps{
	float fps;
    struct timeval t0;
	static int frameno;
	static int last_frameno;
	static inline void reset(){
        gettimeofday(&t0,NULL);
    }
	static inline float dt(){
        struct timeval tv;
        gettimeofday(&tv,NULL);
        const time_t diff_s=tv.tv_sec-t0.tv_sec;
        const int diff_us=tv.tv_usec-t0.tv_usec;
        //        t0=tv;
        return (float)diff_s+diff_us/1000000.f;
    }
	inline void before_render(){
        frameno++;
    }
	void after_render(){
		const float d=dt();
        //        LOGI("dt: %f\n",d);
		if(d>3){
			const int dframe=frameno-last_frameno;
			last_frameno=frameno;
            metrics::fps=fps=dframe/d;
			reset();
            metrics::log();
		}
	}
}

//////
////
// gleso interface
int gleso_init(){
	p("/// gleso init\n");
	p("%16s %4lu B\n","int",sizeof(int));
	p("%16s %4lu B\n","float",sizeof(floato));
	p("%16s %4lu B\n","p3",sizeof(p3));
	p("%16s %4lu B\n","m4",sizeof(m4));
	p("%16s %4lu B\n","glo",sizeof(glo));
	p("%16s %4lu B\n","glob",sizeof(glob));
	p("%16s %4lu B\n","grid",sizeof(grid));
//	LOGI("%s %lu B\n","physics",sizeof(physics));
    srand(1);// generate same random numbers in different instances

	if(!gl::shdr)gl::shdr=new shader();
    if(!gl::shdr->load())return 1;
    
    if(gleso::glos.empty()){
        gleso_impl_add_glos(gleso::glos);
        
        foreach(gleso::glos,[](glo*g){g->load();});
    }
    if(!gleso::grd){
    	gleso::grd=new grid();
        for(int i=0;i<nsprites;i++)
            gleso::grd->add(/*gives*/gleso_impl_create_root());//? leak? grd->add does not take
    }
    fps::reset();
    return 0;
}
void gleso_on_viewport_change(int width,int height){
	p("/// gleso_on_viewport_change %d x %d\n",width,height);
	if(gl::shdr)gl::shdr->on_viewport_change(width,height);
}
void gleso_step(){
	fps::before_render();
    gleso::tick++;
    gleso::dt=1./60;
    glClearColor(0,0,.2,1);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	gl::shdr->use_program();
    gleso::grd->update();//? thread
    gleso::grd->render();//? thread
	fps::after_render();
}
void gleso_on_context_destroyed(){
	if(gl::shdr)delete gl::shdr;
	std::for_each(gleso::glos.begin(),gleso::glos.end(),[](glo*g){delete g;});
	if(gleso::grd)delete gleso::grd;
}

