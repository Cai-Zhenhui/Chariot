import cv2
import numpy as np
import time
import serial

def nothing(x):
    pass

#main
camera=cv2.VideoCapture(1)
frame_width=640
MidAxis=frame_width//2

#ser=serial.Serial("COM5",38400,timeout=0.5)
#print(ser)

print(camera)
cv2.namedWindow('Image')
cv2.createTrackbar('Hmin','Image',0,180,nothing)
cv2.createTrackbar('Hmax','Image',0,180,nothing)
cv2.setTrackbarPos('Hmin','Image',0)
cv2.setTrackbarPos('Hmax','Image',10)

cv2.createTrackbar('Smin','Image',0,255,nothing)
cv2.createTrackbar('Smax','Image',0,255,nothing)
cv2.setTrackbarPos('Smin','Image',80)
cv2.setTrackbarPos('Smax','Image',255)

cv2.createTrackbar('Vmin','Image',0,255,nothing)
cv2.createTrackbar('Vmax','Image',0,255,nothing)
cv2.setTrackbarPos('Vmin','Image',120)
cv2.setTrackbarPos('Vmax','Image',255)

#cv2.createTrackbar('S','Image',0,1,nothing)

kernel=np.ones((10,10),np.uint8)#卷积核

while True:
    ret,frame=camera.read()
    #print(frame.rows)
    if ret:
        Hmin=cv2.getTrackbarPos('Hmin','Image')
        Hmax=cv2.getTrackbarPos('Hmax','Image')
        Smin=cv2.getTrackbarPos('Smin','Image')
        Smax=cv2.getTrackbarPos('Smax','Image')
        Vmin=cv2.getTrackbarPos('Vmin','Image')
        Vmax=cv2.getTrackbarPos('Vmax','Image')
        
        HSV=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

        Lower=np.array([Hmin,Smin,Vmin])#红色范围1
        Upper=np.array([Hmax,Smax,Vmax])#上
        mask=cv2.inRange(HSV,Lower,Upper)#将图中Lower-Upper范围内的像素设置为255，其余为0
        
        Lower=np.array([150,Smin,Vmin])#红色范围2
        Upper=np.array([180,Smax,Vmax])#上
        mask2=cv2.inRange(HSV,Lower,Upper)#将图中Lower-Upper范围内的像素设置为255，其余为0
        
        mask=cv2.add(mask,mask2)#合并结果
        cv2.imshow('mask',mask)
        
        #滤波
        erosion=cv2.erode(mask,kernel,iterations=1)
        erosion=cv2.erode(erosion,kernel,iterations=1)
        dilation=cv2.dilate(erosion,kernel,iterations=1)
        dilation=cv2.dilate(dilation,kernel,iterations=1)
        #target是目标颜色区域
        #target=cv2.bitwise_and(frame,frame,mask=dilation)
        #将滤波后的图像二值化存入binary
        ret_t,binary=cv2.threshold(dilation,127,255,cv2.THRESH_BINARY)
        #print(binary.shape[1])
        #在binary中寻找轮廓 参数1 
        #contours,hierarchy=cv2.findContours(binary,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        contours,hierarchy=cv2.findContours(binary,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
        
        p=0
        Max_area=0
        Max_index=0
        for i in contours:#遍历所有轮廓
            area=int(cv2.contourArea(i))
            if area>Max_area:
                Max_index=p
                Max_area=area
            p+=1
        if p!=0:
            x,y,w,h=cv2.boundingRect(contours[Max_index])#将轮廓分解为 左上角坐标和长宽
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),3)#在面积最大图像上识别到的区域上画上矩形
            
            #推块装置只需要左右移动 因此不需要分析y轴
            distance=63*(MidAxis-(x+w//2))//MidAxis #缩放到0-63
            print("move:",distance,end='')
            if distance>0:
                distance |=0x80 #将最高为至1 表示需要向右移动
            else:
                distance =-distance
            print(" hexdata:",hex(distance)," intdata:",distance," chardata:",chr(distance),end='')
            '''
            if ser.isOpen():
                #发送数据
                print(" Send:",ser.write(bytes([distance])))
            '''
        cv2.imshow('mask_filter',dilation)
        #cv2.imshow('binary',binary)
        cv2.imshow('Image',frame)
        k=cv2.waitKey(300)&0xFF
        if k==27:
            break
    else:
        print("Error! At ret,frame=camera.read()")
        time.sleep(3)
camera.release()
cv2.destroyAllWindows()


