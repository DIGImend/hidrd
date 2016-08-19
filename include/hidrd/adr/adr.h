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
/* Header for class com_claydonkey_hidrd_FilePicker */

#ifndef _Included_com_claydonkey_hidrd_FilePicker
#define _Included_com_claydonkey_hidrd_FilePicker
#ifdef __cplusplus
extern "C" {
#endif
#undef com_claydonkey_hidrd_FilePicker_BIND_ABOVE_CLIENT
#define com_claydonkey_hidrd_FilePicker_BIND_ABOVE_CLIENT 8L
#undef com_claydonkey_hidrd_FilePicker_BIND_ADJUST_WITH_ACTIVITY
#define com_claydonkey_hidrd_FilePicker_BIND_ADJUST_WITH_ACTIVITY 128L
#undef com_claydonkey_hidrd_FilePicker_BIND_ALLOW_OOM_MANAGEMENT
#define com_claydonkey_hidrd_FilePicker_BIND_ALLOW_OOM_MANAGEMENT 16L
#undef com_claydonkey_hidrd_FilePicker_BIND_AUTO_CREATE
#define com_claydonkey_hidrd_FilePicker_BIND_AUTO_CREATE 1L
#undef com_claydonkey_hidrd_FilePicker_BIND_DEBUG_UNBIND
#define com_claydonkey_hidrd_FilePicker_BIND_DEBUG_UNBIND 2L
#undef com_claydonkey_hidrd_FilePicker_BIND_IMPORTANT
#define com_claydonkey_hidrd_FilePicker_BIND_IMPORTANT 64L
#undef com_claydonkey_hidrd_FilePicker_BIND_NOT_FOREGROUND
#define com_claydonkey_hidrd_FilePicker_BIND_NOT_FOREGROUND 4L
#undef com_claydonkey_hidrd_FilePicker_BIND_WAIVE_PRIORITY
#define com_claydonkey_hidrd_FilePicker_BIND_WAIVE_PRIORITY 32L
#undef com_claydonkey_hidrd_FilePicker_CONTEXT_IGNORE_SECURITY
#define com_claydonkey_hidrd_FilePicker_CONTEXT_IGNORE_SECURITY 2L
#undef com_claydonkey_hidrd_FilePicker_CONTEXT_INCLUDE_CODE
#define com_claydonkey_hidrd_FilePicker_CONTEXT_INCLUDE_CODE 1L
#undef com_claydonkey_hidrd_FilePicker_CONTEXT_RESTRICTED
#define com_claydonkey_hidrd_FilePicker_CONTEXT_RESTRICTED 4L
#undef com_claydonkey_hidrd_FilePicker_MODE_APPEND
#define com_claydonkey_hidrd_FilePicker_MODE_APPEND 32768L
#undef com_claydonkey_hidrd_FilePicker_MODE_ENABLE_WRITE_AHEAD_LOGGING
#define com_claydonkey_hidrd_FilePicker_MODE_ENABLE_WRITE_AHEAD_LOGGING 8L
#undef com_claydonkey_hidrd_FilePicker_MODE_MULTI_PROCESS
#define com_claydonkey_hidrd_FilePicker_MODE_MULTI_PROCESS 4L
#undef com_claydonkey_hidrd_FilePicker_MODE_PRIVATE
#define com_claydonkey_hidrd_FilePicker_MODE_PRIVATE 0L
#undef com_claydonkey_hidrd_FilePicker_MODE_WORLD_READABLE
#define com_claydonkey_hidrd_FilePicker_MODE_WORLD_READABLE 1L
#undef com_claydonkey_hidrd_FilePicker_MODE_WORLD_WRITEABLE
#define com_claydonkey_hidrd_FilePicker_MODE_WORLD_WRITEABLE 2L
#undef com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_DIALER
#define com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_DIALER 1L
#undef com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_DISABLE
#define com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_DISABLE 0L
#undef com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_SEARCH_GLOBAL
#define com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_SEARCH_GLOBAL 4L
#undef com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_SEARCH_LOCAL
#define com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_SEARCH_LOCAL 3L
#undef com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_SHORTCUT
#define com_claydonkey_hidrd_FilePicker_DEFAULT_KEYS_SHORTCUT 2L
#undef com_claydonkey_hidrd_FilePicker_RESULT_CANCELED
#define com_claydonkey_hidrd_FilePicker_RESULT_CANCELED 0L
#undef com_claydonkey_hidrd_FilePicker_RESULT_FIRST_USER
#define com_claydonkey_hidrd_FilePicker_RESULT_FIRST_USER 1L
#undef com_claydonkey_hidrd_FilePicker_RESULT_OK
#define com_claydonkey_hidrd_FilePicker_RESULT_OK -1L
    /*
     * Class:     com_claydonkey_hidrd_FilePicker
     * Method:    convertXMLtoCode
     * Signature: (Ljava/lang/String;)V
     */



    JNIEXPORT jstring JNICALL Java_com_claydonkey_hidrd_FilePicker_convertXMLtoCode
    (JNIEnv *, jobject, jstring, jstring);


#include <android/log.h>

#define  LOG_TAG    "com.claydonkey.hidrd"

//#define  LOGD(FILE, ...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  fprintf(FILE, ...)  if(FILE==NULL) \
			__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__); \
			else  \
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);

 #ifdef __cplusplus
}
#endif

#endif

