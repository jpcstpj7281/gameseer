package org.haxe.nme;

//import com.blueseer.main.*;
import ::APP_PACKAGE::.*;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.util.Log;

public class InputActivity extends Activity {

    /** Called when the activity is first created. */
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.inputview);

        Button next = (Button) findViewById(R.id.Button02);
        next.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {
				EditText text = (EditText) findViewById(R.id.edit_text);
                Intent intent = new Intent();
				intent.setAction(text.getText().toString());
                setResult(RESULT_OK, intent);
                finish();
            }
        });
    }
}
