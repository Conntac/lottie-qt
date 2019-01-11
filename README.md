# Lottie QtQuick 

This is Lottie for Qt. It was not invented by us and most of the code was directly ported from the iOS Objective-C code.

This version has known bugs and does not work (especially masks are missing). Expect asserts, unfinished parts of the code might have them commented out.

Tested with Qt 5.10.1 on Android/iOS/macOS. Built once with 5.12.0 :)

## Examples

Viewer: ![Viewer](_Screenshots/viewer.png)

Typewriter: ![Viewer](_Screenshots/typewriter.png)

## Why this exists

### Porting try #1
Lottie has a javascript renderer. QtQuick can execute javascript. Let's draw into a canvas!

After a few hours of coding I was at the point where I could just run the renderer of *lottie-web* on a QML Canvas. It looked really great on my laptop. I was pretty happe worked really fast and straight forward - until I tried to execute it on a mobile phone. The same animation that was running on my laptop with 60fps got ~0.5fps on an iPhone 6s.

Ok but there's QtQuickCompiler, let it run. Performance was almost the same.

But Qt 5.11 is faster! At that time it was not released but I built it from source aaaand: It was at about the same speed.

After having no solution, I used the phone and navigated to [lottiefiles.com](https://www.lottiefiles.com) and noticed: The javascript renderer seems to have a low performance. Since I'm not a javascript guy and thought the rendering should not be done on Qt's js engine anyway I gave up this try.

### Porting try #2
Don't port but wrap the Java and Objective-C implementations. While this would be the easiest way, there are a few downsides:

- Native implementations will only work as overlays. This means we have the same limitations as with QtWebView. Scrolling will appear strange and we can't render with QML over the view. We will also not be able to handle mouse events.
- I want my application to work on all platforms!

### Porting try #3
Porting the objective-c code to Qt.
