#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

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
        cerr << "Failed to open the input file: " << argv[1] << endl;
        return -1;
    }

    ofstream fout(argv[2]);
    if(!fout.is_open()){
        cerr << "Failed to open the output file: " << argv[2] << endl;
        return -1;
    }
    double fps = capture.get(CAP_PROP_FPS);
    auto width= static_cast<int>(capture.get(CAP_PROP_FRAME_WIDTH));
    auto height = static_cast<int>(capture.get(CAP_PROP_FRAME_WIDTH));
    auto ex = static_cast<int>(capture.get(CAP_PROP_FOURCC));

    cout << "codec type: " << (char)(ex & 0xFF) << (char)((ex & 0xFF00) >> 8) << (char)((ex & 0xFF0000) >> 16) << (char)((ex & 0xFF000000) >> 24) << endl;
    cout << "resolution: " << width << '*' << height << endl;
    cout << "fps: " << fps << endl;

    Mat frame;
    int key=0;
    auto frame_count = static_cast<long>(capture.get(CAP_PROP_FRAME_COUNT));
    fout << "record_id, start, end" << endl;
    int record_id = 1;
    bool recording = false;
    for(int i = 0; i < frame_count; ++i){
        capture >> frame;
        if(frame.empty()) break;
        imshow("Videoclip helper", frame);
        key = waitKey();            /* s for start of a record
                                    *  e for end of record
                                    *  q for quit
                                    *  others just steps to the next frame
                                    */
        if(key == 's') {
            if (recording) {
                fout << i << endl;
            } else {
                recording = true;
            }
            fout << record_id << ',' << i << ',';
        } else if(key == 'e') {
            if (recording) {
                recording = false;
                fout << i << endl;
            }
        } else if(key == 'q') {
            if (recording) {
                fout << i << endl;
            }
            break;
        }
    }

    capture.release();
    fout.close();
    return 0;
}