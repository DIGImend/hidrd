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

#include <jni.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include "hidrd/util/str.h"
#include "hidrd/util/fd.h"
#include "hidrd/fmt.h"
#include "hidrd/adr/adr.h"

static int process(const char *input_name, const char *input_fmt_name, const char *input_options, const char *output_name, const char *output_fmt_name, const char *output_options) {
    int result = 1;

    int input_fd = -1;
    void *input_buf = NULL;
    size_t input_size = 0;
    const hidrd_fmt *input_fmt = NULL;
    hidrd_src *input = NULL;

    int output_fd = -1;
    void *output_buf = NULL;
    size_t output_size = 0;
    const hidrd_fmt *output_fmt = NULL;
    hidrd_snk *output = NULL;

    const hidrd_item *item;

    char *err = NULL;
    size_t pos;
    char *posstr = NULL;

    assert(input_name != NULL);
    assert(*input_name != '\0');
    assert(input_fmt_name != NULL);
    assert(*input_fmt_name != '\0');
    assert(input_options != NULL);

    assert(output_name != NULL);
    assert(*output_name != '\0');
    assert(output_fmt_name != NULL);
    assert(*output_fmt_name != '\0');
    assert(output_options != NULL);

    /*
     * Lookup and initialize input and output formats
     */
    input_fmt = hidrd_fmt_list_lkp(input_fmt_name);


    if (input_fmt == NULL) {
	fprintf(stderr, "Unknown input format \"%s\".\n\n", input_fmt_name);
	goto cleanup;
    }
    if (!hidrd_fmt_readable(input_fmt)) {
	fprintf(stderr, "Reading of %s format is not supported.\n\n", input_fmt->desc);
	goto cleanup;
    }
    if (!hidrd_fmt_init(input_fmt)) {
	goto cleanup;
    }

    output_fmt = hidrd_fmt_list_lkp(output_fmt_name);


    if (output_fmt == NULL) {
	fprintf(stderr, "Unknown output format \"%s\".\n\n", output_fmt_name);
	goto cleanup;
    }
    if (!hidrd_fmt_writable(output_fmt)) {
	fprintf(stderr, "Writing to %s format is not supported.\n\n", output_fmt->desc);
	goto cleanup;
    }
    if (!hidrd_fmt_init(output_fmt)) {
	fprintf(stderr, "Failed to initialize %s format library\n", output_fmt->desc);
	goto cleanup;
    }


    /*
     * Open input and output files
     */
    if (input_name[0] == '-' && input_name[1] == '\0')
	input_fd = STDIN_FILENO;
    else {
	input_fd = open(input_name, O_RDONLY);
	if (input_fd < 0) {
	    fprintf(stderr, "Failed to open input: %s\n", strerror(errno));
	    goto cleanup;
	}
    }
    if (output_name[0] == '-' && output_name[1] == '\0')
	output_fd = STDOUT_FILENO;
    else {
	output_fd = open(output_name,
		O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR |
		S_IRGRP | S_IWGRP |
		S_IROTH | S_IWOTH);
	if (output_fd < 0) {
	    fprintf(stderr, "Failed to open output: %s\n", strerror(errno));
	    goto cleanup;
	}
    }

    /*
     * Read the whole input file
     */
    if (!hidrd_fd_read_whole(input_fd, &input_buf, &input_size)) {

	fprintf(stderr, "Failed to read input:  \"hidrd_fd_read_whole\"    %s\n", strerror(errno));

	/* test for native method "fopen"  opening file*/
	FILE* file = fopen(input_name, "w+");

	if (file != NULL) {
	    fprintf(NULL, "Read  input:  \"hidrd_fd_read_whole\"  External Storage Path =  %s\n", input_name);
	    fflush(file);
	    fclose(file);
	} else {
	    fprintf(stderr, "Failed to open input: \"hidrd_fd_read_whole\" External Storage Path =  %s\n", input_name);
	}
	goto cleanup;
    }

    /*
     * Open input and output streams
     */
    input = hidrd_src_new_opts(input_fmt->src, &err, input_buf, input_size, input_options);
    if (input == NULL) {
	fprintf(stderr, "Failed to open input stream:\n%s\n", err);
	goto cleanup;
    }
    free(err);
    err = NULL;

    output = hidrd_snk_new_opts(output_fmt->snk, &err, &output_buf, &output_size, output_options);
    if (output == NULL) {
	fprintf(stderr, "Failed to open output stream:\n%s\n", err);
	goto cleanup;
    }
    free(err);
    err = NULL;

    /*
     * Transfer the stream
     */
    while (pos = hidrd_src_getpos(input), ((item = hidrd_src_get(input)) != NULL))
	if (!hidrd_snk_put(output, item)) {
	    fprintf(stderr, "Failed to write output stream:\n%s\n", (err = hidrd_snk_errmsg(output)));
	    goto cleanup;
	}

    if (hidrd_src_error(input)) {
	fprintf(stderr, "Failed to read input item at %s:\n%s\n", (posstr = hidrd_src_fmtpos(input, pos)), (err = hidrd_src_errmsg(input)));
	goto cleanup;
    }

    /*
     * Close input and output streams
     */
    hidrd_src_delete(input);
    input = NULL;
    if (!hidrd_snk_close(output)) {
	fprintf(stderr, "Failed to close output stream:\n%s\n", (err = hidrd_snk_errmsg(output)));
	goto cleanup;
    }
    output = NULL;

    /*
     * Write the output file
     */
    if (!hidrd_fd_write_whole(output_fd, output_buf, output_size)) {
	fprintf(stderr, "Failed to write output stream: %s\n", strerror(errno));
	goto cleanup;
    }

    /* Success! */
    result = 0;

cleanup:

    free(posstr);
    free(err);

    hidrd_src_delete(input);
    hidrd_snk_delete(output);

    free(output_buf);
    free(input_buf);

    if (input_fd >= 0 && input_fd != STDIN_FILENO)
	close(input_fd);
    if (output_fd >= 0 && output_fd != STDOUT_FILENO)
	close(output_fd);

    if (output_fmt != NULL)
	hidrd_fmt_clnp(output_fmt);
    if (input_fmt != NULL)
	hidrd_fmt_clnp(input_fmt);

    return result;
}

static int stop = 1;
static int check = 0;

JNIEXPORT jstring JNICALL Java_com_claydonkey_hidrd_FilePicker_convertXMLtoCode
(JNIEnv * env, jobject obj, jstring jinFile, jstring joutFile) {

    const char *input_fmt_name = "xml";
    const char *output_fmt_name = "code";

    char resbuffer [25];
    const char *inFile = (*env)->GetStringUTFChars(env, jinFile, 0);
    const char *outFile = (*env)->GetStringUTFChars(env, joutFile, 0);

    /* Test Storage Path is the same as that passed into function*/
    jclass cls_File = (jclass) (*env)->FindClass(env, "java/io/File");
    jclass cls_Env = (jclass) (*env)->FindClass(env, "android/app/NativeActivity");
    jmethodID mid_getExtStorage = (*env)->GetMethodID(env, cls_Env, "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;");
    jobject obj_File = (*env)->CallObjectMethod(env, obj, mid_getExtStorage, NULL);
    jmethodID mid_getPath = (*env)->GetMethodID(env, cls_File, "getPath", "()Ljava/lang/String;");
    jobject obj_Path = (jstring) (*env)->CallObjectMethod(env, obj_File, mid_getPath);
    const char* path = (*env)->GetStringUTFChars(env, obj_Path, NULL);
    fprintf(NULL, "External Storage Path from JNI %s\n", path);
    (*env)->ReleaseStringUTFChars(env, obj_Path, path);
    while (stop) {
	usleep(1000);
	check++;
    }
    int result = process(inFile, input_fmt_name, "", outFile, output_fmt_name, "");
    (*env)->ReleaseStringUTFChars(env, jinFile, inFile);
    (*env)->ReleaseStringUTFChars(env, joutFile, outFile);
    sprintf(resbuffer, "%i returned from hidrd", result);

    return (*env)->NewStringUTF(env, resbuffer);


}