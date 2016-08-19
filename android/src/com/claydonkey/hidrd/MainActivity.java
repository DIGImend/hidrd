package com.claydonkey.hidrd;

import java.io.File;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
 

public class MainActivity extends Activity implements OnClickListener {

    private static final int REQUEST_PICK_FILE = 1;

    private TextView filePath;
    private Button Browse;
    private File selectedFile;

    @Override
    public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
	setContentView(R.layout.main);

	filePath = (TextView) findViewById(R.id.file_path);
	Browse = (Button) findViewById(R.id.browse);
	Browse.setOnClickListener(this);
    }

    public void onClick(View v) {

	switch (v.getId()) {

	    case R.id.browse:
		Intent intent = new Intent(this, FilePicker.class);
		startActivityForResult(intent, REQUEST_PICK_FILE);
		break;
	}
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

	if (resultCode == RESULT_OK) {
	    switch (requestCode) {
		case REQUEST_PICK_FILE:
		    if (data.hasExtra(FilePicker.EXTRA_FILE_PATH)) {
			selectedFile = new File(data.getStringExtra(FilePicker.EXTRA_FILE_PATH));
			filePath.setText(selectedFile.getPath());
		    }
		    break;
	    }
	}
    }
}
