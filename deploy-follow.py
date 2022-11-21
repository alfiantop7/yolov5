### importing required libraries
import torch
import cv2
import time
import imutils
import numpy as np
from imutils.video import FPS



### -------------------------------------- function to run detection ---------------------------------------------------------
def detectx (frame, model):
    frame = [frame]
    # print(f"[INFO] Detecting. . . ")
    results = model(frame)
    labels, cordinates = results.xyxyn[0][:, -1], results.xyxyn[0][:, :-1]
    # print(f'--- ini results | {results}')

    return labels, cordinates

### ------------------------------------ to plot the BBox and results --------------------------------------------------------
def plot_boxes(results, frame, classes):
    kotak = 0, 0, 0, 0
    """
    --> This function takes results, frame and classes
    --> results: contains labels and coordinates predicted by model on the given frame
    --> classes: contains the strting labels

    """
    labels, cord = results
    n = len(labels)
    x_shape, y_shape = frame.shape[1], frame.shape[0]

    # print(f"[INFO] Total {n} detections. . . ")
    # print(f"[INFO] Looping through all detections. . . ")
    # print(f'--- ini labels {labels}')

    ### looping through the detections
    for i in range(n):
        row = cord[i]
        if row[4] >= 0.55: ### threshold value for detection. We are discarding everything below this value
            #print(f"[INFO] Extracting BBox coordinates. . . ")
            w1, h1, w2, h2 = float(row[0]*x_shape), float(row[1]*y_shape), float(row[2]*x_shape), float(row[3]*y_shape)
            x1, y1, x2, y2 = int(row[0]*x_shape), int(row[1]*y_shape), int(row[2]*x_shape), int(row[3]*y_shape) ## BBOx coordniates
            
            kotak = x1, y1, x2, y2
            # print(kotak)
            
            text_d = classes[int(labels[i])]
            # print(f'--- ini text_d {text_d}')
            # print(f'--- ini classes {classes}')

            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 200, 100), 2) ## BBox
            cv2.rectangle(frame, (x1, y1-20), (x2, y1), (0, 200,100), -1) ## for text label background

                
            cv2.putText(frame, 'Human' + f" {round(float(row[4]),2)}", (x1, y1), cv2.FONT_HERSHEY_SIMPLEX, 0.7,(255,255,255), 2)

    return frame, kotak



### ---------------------------------------------- Follow -----------------------------------------------------------
def follow(xcen, startX, endX):

    if xcen < 150:
        #eh.motor.two.forward(speed)
        #sleep(t)
        #eh.motor.two.stop()
        print("Left: xcen = ",xcen)
        
    elif xcen > 250:
        #eh.motor.one.forward(speed)
        #sleep(t)
        print("Right: xcen = ",xcen)
        #eh.motor.one.stop()
        
    elif startX < 50 and endX > 320:
        stop()
        print("Object chase complete!!")
    elif xcen == 0:
        stop()
        
    else:
        #eh.motor.forwards(sf)
        #sleep(tf)
        #eh.motor.stop()
        print("Forward: xcen = ",xcen)

def stop():
    pass

### ---------------------------------------------- Main function -----------------------------------------------------

def main(img_path=None, vid_path=None,vid_out = None):

    print(f"[INFO] Loading model... ")
    ## loading the custom trained model
    # model =  torch.hub.load('ultralytics/yolov5', 'custom', path='last.pt',force_reload=True) ## if you want to download the git repo and then run the detection
    model =  torch.hub.load('yolov5', 'custom', source ='local', path='best2.pt',force_reload=True) ### The repo is stored locally
    fps = FPS().start()
    classes = model.names ### class names in string format


    if img_path != None:
        # print(f"[INFO] Working with image: {img_path}")
        frame = cv2.imread(img_path)
        frame = cv2.cvtColor(frame,cv2.COLOR_BGR2RGB)
        frame = imutils.resize(frame, width=500)
        
        results = detectx(frame, model = model) ### DETECTION HAPPENING HERE    

        frame = cv2.cvtColor(frame,cv2.COLOR_RGB2BGR)
        frame = plot_boxes(results, frame, classes = classes)

        cv2.namedWindow("img_only", cv2.WINDOW_NORMAL) ## creating a free windown to show the result

        while True:
            # frame = cv2.cvtColor(frame,cv2.COLOR_RGB2BGR)

            cv2.imshow("img_only", frame)

            if cv2.waitKey(5) & 0xFF == ord('q'):
                print(f"[INFO] Exiting. . . ")
                # cv2.imwrite("final_output.jpg",frame) ## if you want to save he output result.

                break

    elif vid_path !=None:
        print(f"[INFO] Working with video: {vid_path}")

        ## reading the video
        cap = cv2.VideoCapture(vid_path)


        # if vid_out: ### creating the video writer if video output path is given

        #     # by default VideoCapture returns float instead of int
        #     width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
        #     height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
        #     fps = int(cap.get(cv2.CAP_PROP_FPS))

            
            # codec = cv2.VideoWriter_fourcc(*'mp4v') ##(*'XVID')
            # out = cv2.VideoWriter(vid_out, codec, fps, (width, height))

        # assert cap.isOpened()
        frame_no = 1

        cv2.namedWindow("vid_out", cv2.WINDOW_NORMAL)
        while True:
            # start_time = time.time()
            ret, frame = cap.read()
            if ret :
                # print(f"[INFO] Working with frame {frame_no} ")

                frame = cv2.cvtColor(frame,cv2.COLOR_BGR2RGB)
                width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
                height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

                results = detectx(frame, model = model)
                frame = cv2.cvtColor(frame,cv2.COLOR_RGB2BGR)
                frame, box = plot_boxes(results, frame,classes = classes)

                box = np.array(box)
                (startX, startY, endX, endY) = box.astype("int")
                xcen = (endX + startX)/2
                ycen = (endY + startY)/2

                follow(xcen, startX, endX)
                
                cv2.imshow("vid_out", frame)

                # if vid_out:
                #     print(f"[INFO] Saving output video. . . ")
                #     out.write(frame)

                if cv2.waitKey(5) & 0xFF == ord('q'):
                    break
                frame_no += 1

                fps.update()
        
        print(f"[INFO] Clening up. . . ")
        fps.stop()
        print("[INFO] elapsed time: {:.2f}".format(fps.elapsed()))
        print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))
        ### releaseing the writer
        # out.release()
        
        ## closing all windows
        cv2.destroyAllWindows()



### -------------------  calling the main function-------------------------------


# main(vid_path="facemask.mp4",vid_out="facemask_result.mp4") ### for custom video
main(vid_path=0) #### for webcam
# main(img_path="test_images/crowd_mask181.jpg") ## for image