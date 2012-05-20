//Wimport android.util.Log;
import java.io.*;
import org.haxe.nme.*;

import android.os.Bundle;
import android.speech.RecognizerIntent;
//import java.util.*;
import java.util.ArrayList;
import java.util.List;
import android.content.pm.PackageManager;
import android.content.Intent;
import android.widget.*;
import android.view.*;
import android.*;
import android.util.Log;
import android.graphics.Bitmap;

import android.content.Intent;


public class NativeCall {


    //static String _state;
    public static void openInputSpeech(){

        //if ( GameActivity.speechintent == null){
        Intent speechintent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        PackageManager pm = GameActivity.getInstance().getPackageManager();
        List activities = pm.queryIntentActivities(speechintent, 0);
        if (activities.size() != 0) {
            //Log.i("trace",  "startActivityForResult");
            GameActivity.getInstance().startActivityForResult(speechintent, 1234);
        } else {
            Log.i("trace",  "Recognizer not present");
        }
        //}

    }
    static public void openEmbedBrowser(String inURL){

        if ( inURL == null){
            Log.i("trace",  "launchEmbedBrowser, null address!"  );
            inURL = "http://winterfell.sinaapp.com";
        }else{
            Log.i("trace",  "launchEmbedBrowser, address: " +inURL  );
        }
        String url=inURL;
        Intent intent = new Intent(GameActivity.getContext(), org.haxe.nme.WebViewActivity.class);
        Log.i("trace",  "launchEmbedBrowser, new intent"  );
        Bundle b=new Bundle();
        b.putString("url", url);
        intent.putExtras(b);
        Log.i("trace",  "launchEmbedBrowser, before startActivity"  );
        try{
            GameActivity.getInstance().startActivity(intent);
        }catch( Exception e){
            Log.i("trace", "launchEmbedBrowser: " + e.toString());
            return;
        }
        Log.i("trace",  "launchEmbedBrowser, after startActivity"  );
    }
    public static void openBrowser ( String address) { GameActivity.launchBrowser(address); }
    public static Bitmap getBitmap() {
        Bitmap res = GameActivity.bm;
        GameActivity.bm = null;
        return res;
    }
    public static void openPictureSelect () {
        GameActivity.openPictureSelect();
    }

    public static String getResult () {

        //String inputdata  = new String(GameActivity.inputdata);
        //GameActivity.inputdata = null;
        String res = GameActivity.inputdata;
        GameActivity.inputdata = null;
        return res;
    }

    private static 	LinearLayout group ;
    private static 	TextView panel;
    private static  EditText input;
    private static 	Button ok;
    private static 	Button cancel ;

    //public static void openInputView(){
    //Intent inputIntent = new Intent(GameActivity.getContext(), org.haxe.nme.InputActivity.class);
    //GameActivity.getInstance().startActivityForResult(inputIntent, 2345);
    //}
    public static void openUIView(){}
    public static void openInputView(){
        if ( group == null ){
            GameActivity.inputdata = null;
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
                    GameActivity.inputdata= NativeCall.input.getText().toString();
                    Log.i("trace",GameActivity.inputdata);
                    GameActivity.popView();
                    //GameActivity.getInstance().mHandler.post(new Runnable() {
                    //@Override public void run() {
                    ////GameActivity.popView();
                    //GameActivity.getInstance().setContentView(GameActivity.getInstance().mView );
                    //} });
                }
            });
            cancel.setOnClickListener(new View.OnClickListener() {
                public void onClick(View v) {
                    Log.i("trace","==========cancel================");
                    GameActivity.popView();
                    GameActivity.inputdata = "__FAILED__";
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
        //GameActivity.getInstance().setContentView(group);
    }
}

