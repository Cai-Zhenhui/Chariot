'''
Color Range(HSV)
R1 (  0, 80,120)-( 10,255,255)
R2 (150, 80,120)-(180,255,255)
'''
import time
import numpy as np 
import cv2
import serial

def nothing():
    pass

#main
#some const
Tiltle="Image"
frame_width=640
MidAxis=frame_width//2

camera=cv2.VideoCapture(2)
print(camera)

#Create Window and its content
cv2.namedWindow(Tiltle)
cv2.createTrackbar("Hmin",Tiltle,0,180,nothing)
cv2.createTrackbar("Hmax",Tiltle,0,180,nothing)
cv2.setTrackbarPos("Hmin",Tiltle,0)
cv2.setTrackbarPos("Hmax",Tiltle,10)

cv2.createTrackbar("Smin",Tiltle,0,255,nothing)
cv2.createTrackbar("Smax",Tiltle,0,255,nothing)
cv2.setTrackbarPos("Smin",Tiltle,80)
cv2.setTrackbarPos("Smax",Tiltle,255)

cv2.createTrackbar("Vmin",Tiltle,0,255,nothing)
cv2.createTrackbar("Vmax",Tiltle,0,255,nothing)
cv2.setTrackbarPos("Vmin",Tiltle,120)
cv2.setTrackbarPos("Vmax",Tiltle,255)

kernel=np.ones((10,10),np.uint8)

while True:
    ret,frame=camera.read()

    if ret:
        Hmin=cv2.getTrackbarPos("Hmin",Tiltle)
        Hmax=cv2.getTrackbarPos("Hmax",Tiltle)
        Smin=cv2.getTrackbarPos("Smin",Tiltle)
        Smax=cv2.getTrackbarPos("Smax",Tiltle)
        Vmin=cv2.getTrackbarPos("Vmin",Tiltle)
        Vmax=cv2.getTrackbarPos("Vmax",Tiltle)

        HSV=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

        Lower=np.array([Hmin,Smin,Vmin])
        Upper=np.array([Hmax,Smax,Vmax])
        mask=cv2.inRange(HSV,Lower,Upper)
        #cv2.imshow('mask1',mask)

        Lower=np.array([150,Smin,Vmin])
        Upper=np.array([180,Smax,Vmax])
        mask2=cv2.inRange(HSV,Lower,Upper)
        #cv2.imshow('mask2',mask2)

        mask=cv2.add(mask,mask2)
        cv2.imshow('mask',mask)

        #filter
        erosion=cv2.erode(mask,kernel,iterations=1)
        erosion=cv2.erode(erosion,kernel,iterations=1)
        dilation=cv2.dilate(erosion,kernel,iterations=1)
        dilation=cv2.dilate(dilation,kernel,iterations=1)

        #target=cv2.bitwise_and(frame,frame,mask=dilation)

        ret_t,binary=cv2.threshold(dilation,127,255,cv2.THRESH_BINARY)
        #contours,hierarchy=cv2.findContours(binary,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        contours,hierarchy=cv2.findContours(binary,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)

        p=0
        Max_area=0
        Max_index=0
        for i in contours:#trave all contours to find the max
            area=cv2.contourArea(i)
            if area>Max_area:
                Max_index=p
                Max_area=area
            p+=1
        if p!=0:
            x,y,w,h=cv2.boundingRect(contours[Max_index])
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),3)#draw rectangle on the max target

            #analze pos and send data of pos
            print("move:",(MidAxis-(x+w//2)))
        
        cv2.imshow('mask_filter',dilation)
        cv2.imshow('Image',frame)

        k=cv2.waitKey(1)&0xFF
        if k==27:
            break
    else:
        print("Error! At ret,frame=camera.read()")
        time.sleep(3)
camera.release()
cv2.destroyAllWindos()
