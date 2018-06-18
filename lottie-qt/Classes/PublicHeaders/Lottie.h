//
//  Lottie.h
//  Pods
//
//  Created by brandon_withrow on 1/27/17.
//
//  Dream Big.

#if __has_feature(modules)
@import Foundation;
#else
#include <Foundation/Foundation.h>
#endif

#ifndef Lottie_h
#define Lottie_h

//! Project version number for Lottie.
FOUNDATION_EXPORT double LottieVersionNumber;

//! Project version string for Lottie.
FOUNDATION_EXPORT const unsigned char LottieVersionString[];

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
#include "LOTAnimationTransitionController.h"
#include "LOTAnimatedSwitch.h"
#include "LOTAnimatedControl.h"
#endif

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
#include "LOTCacheProvider.h"
#endif

#include "LOTAnimationView.h"
#include "LOTAnimationCache.h"
#include "LOTComposition.h"
#include "LOTBlockCallback.h"
#include "LOTInterpolatorCallback.h"
#include "LOTValueCallback.h"
#include "LOTValueDelegate.h"

#endif /* Lottie_h */
