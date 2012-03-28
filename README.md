CvCamView
============

A library to use opencv capture methods in QML applications, it emits a signal
every time a new frame is queryed from the camera and it provides the frame
as a native IplImage*

Features
--------
You can change camera and resolution at runtime. The widget can be easily resized
or expanded independently of the resolution
You can access every frame as an IplImage* or as a QImage
You can change camera state to one of the following: UnloadedState, LoadedState, ActiveState

UseCase
------
Here is an example of CvCamView in action (note that consumer is not provided):

    import opencv.components 1.0

    CvCamView {
        id: camView
        width: 800
        height: 600
        camera: 0
        cameraState: CvCamView.ActiveState //unneeded because this is the default state
        resolution: CvCamResolution {
                        width: 800
                        height: 600
                    }
        onNewFrame: {
            console.log("new frame recived");
            consumer.detectSomething(camView.iplImage);
        }

