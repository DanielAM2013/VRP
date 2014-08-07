package com.vrp.started;

import android.app.Activity;
import android.os.Bundle;

import android.content.Intent;

public class Development extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
    }
    public void sendMessage(View view) {
 	Intent intent = new Intent(this, DisplayMessageActivity.class);
	EditText editText = (EditText) findViewById(R.id.edit_message);
	String message = editText.getText().toString();
	intent.putExtra(EXTRA_MESSAGE, message);
        startActivity(intent);
    }
}
