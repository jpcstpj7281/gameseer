package org.haxe.nme;

import ::APP_PACKAGE::.*;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.util.Log;

import java.util.regex.*;
import android.webkit.*;
import android.webkit.WebSettings.*;
import android.view.MotionEvent;
import  android.view.KeyEvent;

class JavaScriptInterface  
{  
    public void getHTML(String html)  
    {  
        String pin= getPin(html);

        if (pin != null && pin.length() >0){
            GameActivity.inputdata = pin;
            //这个pin码就是oauth_verifier值,用来进一步获取Access Token和Access Secret用
            //Log.i("trace",  "webview, pin:" +pin );
        }
    }

    public String getPin(String html)
    {
        String ret="";
        String regEx="[0-9]{6}";
        Pattern p=Pattern.compile(regEx);
        Matcher m=p.matcher(html);
        boolean result=m.find();
        if(result)
        {
            ret= m.group(0);
        }
        return ret;
    }
}

public class WebViewActivity extends Activity {

    /** Called when the activity is first created. */
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Log.i("trace",  "webview, oncreate!" );

        setContentView(R.layout.webview);
        WebView wv =(WebView) findViewById(R.id.web);
        Intent i=this.getIntent();
        if(!i.equals(null)){
            Bundle b=i.getExtras();
            if(b!=null){
                if(b.containsKey("url")){
                    String url = b.getString("url");

                    //这行很重要一点要有，不然网页的认证按钮会无效  
                    wv.getSettings().setJavaScriptEnabled(true);
                    wv.getSettings().setSupportZoom(true);
                    //wv.getSettings().setDefaultZoom(WebSettings.ZoomDensity.FAR);
                    wv.getSettings().setBuiltInZoomControls(true);

                    //wv.getSettings().setPluginsEnabled(true);
                    //wv.getSettings().setPluginState(PluginState.ON);

                    wv.requestFocus(View.FOCUS_DOWN);
                    wv.setOnTouchListener(new View.OnTouchListener() {
                        @Override
                        public boolean onTouch(View v, MotionEvent event) {
                            switch (event.getAction()) {
                                case MotionEvent.ACTION_DOWN:
                                case MotionEvent.ACTION_UP:
                                    if (!v.hasFocus()) {
                                        v.requestFocus();
                                    }
                                    break;
                            }
                            return false;
                        }
                    });

                    wv.addJavascriptInterface(new JavaScriptInterface(), "getWeiboPin");
                    WebViewClient wvc=new WebViewClient() {
                        @Override
                            public void onPageFinished(WebView view,String url) {
                                if(url.equals("http://api.t.sina.com.cn/oauth/authorize")){
                                    view.loadUrl("javascript:window.getWeiboPin.getHTML('<head>'+document.getElementsByTagName('html')[0].innerHTML+'</head>');");
                                    finish();
                                }else{
                                    view.loadUrl("javascript:window.getWeiboPin.getHTML('<head>'+document.getElementsByTagName('html')[0].innerHTML+'</head>');");
                                }
                                super.onPageFinished(view, url);
                                //Log.i("trace",  "webview, page finished!" );
                            }
                    };
                    wv.setWebViewClient(wvc);

                    //Log.i("trace",  "webview, loadurl: "+url  );
                    wv.loadUrl(url);
                }
            }
        }
    }

    @Override 
        public boolean onKeyDown(int i, KeyEvent event){
            if (i == KeyEvent.KEYCODE_BACK){
                Log.i("trace",  "onKeyDown, KEYCODE_BACK");
                if ( GameActivity.inputdata == null ) {
                    GameActivity.inputdata = "__failed__";
                }
                finish();
            }
            return true;
        }






}
