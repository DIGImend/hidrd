#!/bin/sh

SDIR=$(dirname $0)
cp $SDIR/../lib/adr/.libs/*.so $SDIR/../android/libs/arm64-v8a
cp $SDIR/../lib/fmt/.libs/*.so $SDIR/../android/libs/arm64-v8a
cp $SDIR/../lib/strm/.libs/*.so $SDIR/../android/libs/arm64-v8a
cp $SDIR/../lib/opt/.libs/*.so $SDIR/../android/libs/arm64-v8a
cp $SDIR/../lib/item/.libs/*.so $SDIR/../android/libs/arm64-v8a
cp $SDIR/../lib/usage/.libs/*.so $SDIR/../android/libs/arm64-v8a
cp $SDIR/../lib/util/.libs/*.so $SDIR/../android/libs/arm64-v8a
