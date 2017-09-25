# Videoclip helper
This is a simple tool I'm using for an assignment form professor Johnathan Gratch's Affective Computing class.

Usage `\./videoclip_helper <input video> <output \.csv file>`

You will see a window showing the frames of the video, starting from the first one.

Typing on the keyboard to operate and step to the next frame, currently support operations:
* s: start a record
* e: end a record
* q: quit the program
* (other keys): only step to next frame

The result will be a csv file with the logical structure like this:
| record_id | start | end   |
|:---------:|:-----:|:-----:|
| 1         | 23    | 49    |
| 2         | 77    | 163   |
| ...       | ...   | ...   |

Note that the _start_ and _end_ column indicates the frame number of the starting and ending frame of one clip and they start from 0.