//Wimport android.util.Log;
import java.io.*;
import org.haxe.nme.*;


import android.content.Intent;
import android.widget.*;
import android.view.*;
import android.*;
import android.util.Log;
import android.graphics.Bitmap;



public class NativeCall {

	// private static 	LinearLayout group ;
	// private static 	TextView panel;
    // private static  EditText input;
	// private static 	Button ok;
	// private static 	Button cancel ;
	
	//static String _state;
	public static void openInputView () {
		// if (_state != null && _state.equals("input") ){
			GameActivity.openInputView();
		// }else if (_state != null && _state.equals("speech") ){
			// openInputSpeech();
		// }
		
		// Log.i("trace",  "openInputView state: " +_state);
	}
	
	public static void openBrowser ( String address) { GameActivity.launchBrowser(address); }
	public static void openEmbedBrowser ( String address) { GameActivity.launchEmbedBrowser(address); }
	
	
	public static void openInputSpeech () {
		GameActivity.openInputSpeech();
	}
	
	// public static void setStatus ( String state) {
		// Log.i("trace",  "setStatus: " +state);
		// _state = state;
	// }
	public static Bitmap getBitmap() {
		Bitmap res = GameActivity.bm;
		GameActivity.bm = null;
        return res;
	}
	
	public static void openPictureSelect () {
			GameActivity.openPictureSelect();
	}

    public static String getResult () {

		/*
		if ( group == null ){
			inputstr = "";
			group = new LinearLayout(GameActivity.getContext());
			panel = new TextView(GameActivity.getContext());
			input = new EditText( GameActivity.getContext());
			ok = new Button( GameActivity.getContext());
			cancel = new Button( GameActivity.getContext());
			
			panel.setText("输入新名字:");
			ok.setText("OK");
			ok.setWidth( 400);
			
			cancel.setText("CANCEL");
			cancel.setWidth( 400);
			
			ok.setOnClickListener(new View.OnClickListener() {
             public void onClick(View v) {
					Log.i("trace","==========ok================");
					//GameActivity.getInstance().setContentView(cancel );
					inputstr = NativeCall.input.getText().toString();
					Log.i("trace",inputstr);
					
					
					// GameActivity.getInstance().mHandler.post(new Runnable() {
						 // @Override public void run() {
								GameActivity.popView();
								
								// } });
								
					
				 }
			 });
			cancel.setOnClickListener(new View.OnClickListener() {
				 public void onClick(View v) {
					Log.i("trace","==========cancel================");
					GameActivity.popView();
					
				 }
			 });

			//GameActivity.getInstance().setContentView(input );
			input.setHeight( 100);
			input.setWidth( 400);
			group.addView(panel);
			group.addView(input);
			group.addView(ok);
			group.addView(cancel);
			group.setOrientation(LinearLayout.VERTICAL);
			

		}
		GameActivity.pushView(group );
		*/

		//String inputdata  = new String(GameActivity.inputdata);
		//GameActivity.inputdata = null;
		String res = GameActivity.inputdata;
		GameActivity.inputdata = null;
        return res;

    }


    public static int twoPlusTwo () {

        return 2 + 2;

    }



}

