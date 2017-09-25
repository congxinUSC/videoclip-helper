#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <infile> <outfile>" << endl;
        return -1;
    }
    // the video capture object to capture frames form a video stream (e.g. mp4 file)
    VideoCapture capture(argv[1]);
    if(!capture.isOpened()){
        cerr << "Failed to open the input file." << endl;
        return -1;
    }

    double fps = capture.get(CAP_PROP_FPS);
    auto width= static_cast<int>(capture.get(CAP_PROP_FRAME_WIDTH));
    auto height = static_cast<int>(capture.get(CAP_PROP_FRAME_WIDTH));
    Size sz(width, height);

    // the video writer object to write frames in to a file.
    VideoWriter writer(argv[2], CAP_FFMPEG, fps, sz);
    if(!writer.isOpened()){
        cerr << "Failed to open the output file." << endl;
        return -1;
    }

    // the current frame
    Mat frame;
    int key=0;
    bool rec=false;
    while(true){
        capture >> frame;
        if(frame.empty()) break;
        imshow("Videoclip helper", frame);
        key = waitKey();            /* s for start recording
                                    *  e for end recording
                                    *  others just steps to the next frame
                                    */
        if(key == 's'){
            rec = true;
        }else if(key == 'e'){
            rec = false;
        }

        if(rec){
            writer << frame;
        }
    }
    capture.release();
    writer.release();
    return 0;
}