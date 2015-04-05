package a.gleso;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
final public class activity extends Activity{
    private view view;
    @Override protected void onCreate(final Bundle b){
        Log.i("gleso","oncreate "+b);
        super.onCreate(b);
        view=new view(getApplication());
        setContentView(view);
    }
    @Override protected void onPause(){
        Log.i("gleso","onpause");
        super.onPause();
        view.onPause();
    }
    @Override protected void onResume(){
        Log.i("gleso","onresume");
        super.onResume();
        view.onResume();
    }
    @Override protected void onRestoreInstanceState(final Bundle b){
        Log.i("gleso","onRestoreInstanceState "+b);
    	super.onRestoreInstanceState(b);
    }
    @Override protected void onDestroy(){
        Log.i("gleso","ondestroy");
    	super.onDestroy();
    }
	@Override public boolean dispatchTouchEvent(final MotionEvent e){
		Log.i("gleso","touch   x,y="+e.getX()+","+e.getY()+"  action="+e.getAction());
		int action=0;
		if(e.getAction()==MotionEvent.ACTION_DOWN){
			action=1;
		}else if(e.getAction()==MotionEvent.ACTION_UP){
			action=2;
		}
		final float x=e.getX();
		final float y=e.getY();
		jni.glesotouch(x,y,action);
		return true;
	}
}
