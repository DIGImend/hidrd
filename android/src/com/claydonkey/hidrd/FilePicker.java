/*
 * The MIT License
 *
 * Copyright 2016 Anthony Campbell.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
package com.claydonkey.hidrd;

import java.io.File;
import java.io.FilenameFilter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import java.io.*;
import java.util.Arrays;

public class FilePicker extends ListActivity {

    public final static String EXTRA_FILE_PATH = "file_path";
    public final static String EXTRA_SHOW_HIDDEN_FILES = "show_hidden_files";
    public final static String EXTRA_ACCEPTED_FILE_EXTENSIONS = "accepted_file_extensions";
    //private final   String DEFAULT_INITIAL_DIRECTORY =);

    protected File Directory;
    protected ArrayList<File> Files = new ArrayList<File>();
    protected FilePickerListAdapter Adapter;
    protected boolean ShowHiddenFiles = false;
    protected String[] acceptedFileExtensions;

    public void copyAssetFile(String assetFilePath, String destinationFilePath) throws IOException {
	InputStream in = getApplicationContext().getAssets().open(assetFilePath);
	OutputStream out = new FileOutputStream(destinationFilePath);

	byte[] buf = new byte[5024];
	int len;
	while ((len = in.read(buf)) > 0) {
	    out.write(buf, 0, len);
	}
	in.close();
	out.close();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);

	LayoutInflater inflator = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);

	View emptyView = inflator.inflate(R.layout.empty_view, null);
	((ViewGroup) getListView().getParent()).addView(emptyView);
	getListView().setEmptyView(emptyView);

	AssetManager assetManager = getAssets();

	Directory = getExternalFilesDir(null);
	if (!Arrays.asList(Directory.listFiles()).contains("mouse_descriptor.xml")) {
	    try {
		copyAssetFile("mouse_descriptor.xml", Directory.getCanonicalPath() + "/mouse_descriptor.xml");
	    } catch (IOException ex) {

	    }
	}
	Adapter = new FilePickerListAdapter(this, Files);
	setListAdapter(Adapter);
	// Initialize the extensions array to allow any file extensions
	acceptedFileExtensions = new String[]{".xml", ".txt", "xml", "txt"};
	// Get intent extras
	if (getIntent().hasExtra(EXTRA_FILE_PATH)) {
	    Directory = new File(getIntent().getStringExtra(EXTRA_FILE_PATH));
	}

	if (getIntent().hasExtra(EXTRA_SHOW_HIDDEN_FILES)) {
	    ShowHiddenFiles = getIntent().getBooleanExtra(EXTRA_SHOW_HIDDEN_FILES, false);
	}

	if (getIntent().hasExtra(EXTRA_ACCEPTED_FILE_EXTENSIONS)) {

	    ArrayList<String> collection = getIntent().getStringArrayListExtra(EXTRA_ACCEPTED_FILE_EXTENSIONS);
	    acceptedFileExtensions = (String[]) collection.toArray(new String[collection.size()]);
	}
    }

    @Override
    protected void onResume() {
	refreshFilesList();
	super.onResume();
    }

    protected void refreshFilesList() {

	Files.clear();
	ExtensionFilenameFilter filter = new ExtensionFilenameFilter(acceptedFileExtensions);

	File[] files = Directory.listFiles(filter);
	if (files != null && files.length > 0) {
	    for (File f : files) {
		if (f.isHidden() && !ShowHiddenFiles) {
		    continue;
		}
		Files.add(f);
	    }
	    Collections.sort(Files, new FileComparator());
	}
	Adapter.notifyDataSetChanged();
    }

    @Override
    public void onBackPressed() {

	if (Directory.getParentFile() != null) {
	    Directory = Directory.getParentFile();
	    refreshFilesList();
	    return;
	}
	super.onBackPressed();
    }

    @Override
    protected void onListItemClick(ListView listView, View view, int position, long id) {

	File newFile = (File) listView.getItemAtPosition(position);

	if (newFile.isFile()) {
	    Intent extra = new Intent();
	    extra.putExtra(EXTRA_FILE_PATH, newFile.getAbsolutePath());
	    String result = convertXMLtoCode(newFile.getAbsolutePath(),newFile.getParent() +"/test.txt");
	    setResult(RESULT_OK, extra);
	    finish();
	} else {
	    Directory = newFile;
	    refreshFilesList();
	}
	super.onListItemClick(listView, view, position, id);

    }

    private class FilePickerListAdapter extends ArrayAdapter<File> {

	private List<File> mObjects;

	public FilePickerListAdapter(Context context, List<File> objects) {

	    super(context, R.layout.list_item, android.R.id.text1, objects);
	    mObjects = objects;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {

	    View row = null;

	    if (convertView == null) {
		LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		row = inflater.inflate(R.layout.list_item, parent, false);
	    } else {
		row = convertView;
	    }

	    File object = mObjects.get(position);

	    ImageView imageView = (ImageView) row.findViewById(R.id.file_picker_image);
	    TextView textView = (TextView) row.findViewById(R.id.file_picker_text);
	    textView.setSingleLine(true);
	    textView.setText(object.getName());

	    if (object.isFile()) {
		imageView.setImageResource(R.mipmap.file);
	    } else {
		imageView.setImageResource(R.mipmap.folder);
	    }

	    return row;
	}
    }

    private class FileComparator implements Comparator<File> {

	public int compare(File f1, File f2) {

	    if (f1 == f2) {
		return 0;
	    }

	    if (f1.isDirectory() && f2.isFile()) // Show directories above files
	    {
		return -1;
	    }

	    if (f1.isFile() && f2.isDirectory()) // Show files below directories
	    {
		return 1;
	    }
	    return f1.getName().compareToIgnoreCase(f2.getName());
	}
    }

    private class ExtensionFilenameFilter implements FilenameFilter {

	private String[] Extensions;

	public ExtensionFilenameFilter(String[] extensions) {

	    super();
	    Extensions = extensions;
	}

	public boolean accept(File dir, String filename) {

	    if (new File(dir, filename).isDirectory()) {
		return true;
	    }

	    if (Extensions != null && Extensions.length > 0) {

		for (int i = 0; i < Extensions.length; i++) {

		    if (filename.endsWith(Extensions[i])) {

			// The filename ends with the extension
			return true;
		    }
		}
		// The filename did not match any of the extensions
		return false;
	    }
	    // No extensions has been set. Accept all file extensions.
	    return true;
	}

    }

    public native String convertXMLtoCode(String inFile , String outFile);

    /* this is used to load the library on application
     * startup. The library has already been unpacked into
     * /data/data/com.claydonkey.algorithms/lib/libhello-jni.so at
     * installation time by the package manager.
     */
    static {
	System.loadLibrary("hidrd_adr");
    }
}
