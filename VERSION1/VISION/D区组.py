import sensor, image, time,pyb
from pyb import UART
from pyb import LED


red_zu=[(37, 49, 53, 127, -128, 127),(35, 57, 45, 127, -128, 127)]
green_zu=[((47, 76, -57, -9, -128, 127)),(61, 88, -48, -11, -128, 127)]
blue_zu=[(21, 48, 6, 37, -72, -24),(44, 68, 10, 38, -42, -19)]


red=(37, 49, 53, 127, -128, 127)
green =(47, 76, -57, -9, -128, 127)
blue = (21, 48, 6, 37, -72, -24)
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()
uart = UART(3, 115200)
a=0
cx=0
cy=0
k_x=0
k_y=0
ch=6

def find_max(blobs):
   max_size=0
   for blob in blobs:
       if blob.pixels() > max_size:
           max_blob=blob
           max_size = blob.pixels()
   return max_blob
while(True):
     clock.tick()
     img = sensor.snapshot()

     #红组
     blobs  =img.find_blobs(red_zu, pixels_threshold=800, area_threshold=600)
     if blobs:

        max_b = find_max(blobs)
        a=1
        if max_b.code() == 1:
            img.draw_rectangle(max_b.rect(),color=(255,0,0))
            img.draw_cross(max_b.cx(), max_b.cy())
            cx=max_b.cx()
            cy=max_b.cy()
        if max_b.code() == 2:

            img.draw_rectangle(max_b.rect(),color=(0,255,0))
            img.draw_cross(max_b.cx(),max_b.cy())
            cx=max_b.cx()
            cy=max_b.cy()

     #绿组
     blobs  =img.find_blobs(green_zu, pixels_threshold=800, area_threshold=600)
     if blobs:

        max_b = find_max(blobs)
        a=2
        if max_b.code() == 1:
            img.draw_rectangle(max_b.rect(),color=(0,255,0))
            img.draw_cross(max_b.cx(), max_b.cy())
            cx=max_b.cx()
            cy=max_b.cy()
        if max_b.code() == 2:
            img.draw_rectangle(max_b.rect(),color=(0,255,0))
            img.draw_cross(max_b.cx(),max_b.cy())
            cx=max_b.cx()
            cy=max_b.cy()

     #蓝组
     blobs  =img.find_blobs(blue_zu, pixels_threshold=800, area_threshold=600)
     if blobs:

        max_b = find_max(blobs)
        a=4
        if max_b.code() == 1:
            img.draw_rectangle(max_b.rect(),color=(0,0,255))
            img.draw_cross(max_b.cx(), max_b.cy())
            cx=max_b.cx()
            cy=max_b.cy()
        if max_b.code() == 2:
            img.draw_rectangle(max_b.rect(),color=(0,255,0))
            img.draw_cross(max_b.cx(),max_b.cy())
            cx=max_b.cx()
            cy=max_b.cy()

     FH = bytearray([0x2C,0x2D,a,cx,cy,ch,0x5B,0x5A])
     uart.write(FH)
     print(FH)
