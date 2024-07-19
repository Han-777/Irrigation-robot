import sensor, image, time
from pyb import LED, Servo, UART

uart = UART(3, 115200)
times = 0
total = 6
area = 200
pixels = 200
i = 0
l = 0
w = 70
h = 25
x1 = 15
x2 = 125
x3 = 255
color = 0
y10 = 12
y11 = 52
y12 = 95
y13 = 135
y14 = 180
y15 = 215
y16 = 200
y20 = 5
y21 = 40
y22 = 80
y23 = 125
y24 = 175
y25 = 210
y26 = 210
y30 = 0
y31 = 40
y32 = 80
y33 = 125
y34 = 165
y35 = 210
y36 = 200
Left_1 = 38;
Left_2 = 14;
s1 = Servo(1)
s2 = Servo(2)
s1.angle(Left_1, 1000)
s2.angle(Left_2, 1000)
time.sleep_ms(2000)
region = []
begin = 0

green_threshold = (41, 74, -29, 23, -18, 127)
blue_threshold = (11, 48, -3, 25, -128, -6)
# blue_threshold=(0, 100, -128, 127, -128, 127)
red_threshold = (40, 55, 29, 127, -128, 127)

color = ["green", "blue", "red"]
result = []
color_threshold = [green_threshold, blue_threshold, red_threshold]
Left_ROI = [(x1, 0, w, h + 5), (x1 - 5, 45, w, h), (x1 - 2, 95, w, h), (x1 - 5, 135, w, h), (x1, 180, w, h),
            (x1, 215, w, h)]
Mid_ROI = [(x2, 7, w, h - 5), (x2, 40, w, h), (x2, 80, w, h), (x2, 125, w, h), (x2, 175, w, h), (x2 - 5, 220, w, h)]
Right_ROI = [(x3 - 5, 10, w, h), (x3, 48, w, h), (x3, 90, w, h), (x3 - 2, 131, w, h), (x3 - 2, 175, w, h),
             (x3 - 5, 220, w, h)]
red = LED(1)
green = LED(2)
blue = LED(3)
green.on()
sensor.reset()
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(6)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
time.sleep_ms(1000)


def find_max(blobs):
    max_size = 0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob = blob
            max_size = blob.pixels()
    return max_blob


a = 0
while (True):
    img = sensor.snapshot()
    for i in range(0, 6):
        img.draw_rectangle(Left_ROI[i], color=(255, 0, 0))
        img.draw_rectangle(Mid_ROI[i], color=(255, 0, 0))
        img.draw_rectangle(Right_ROI[i], color=(255, 0, 0))
    if (begin == 0):
        if (len(region) == 0):

            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Left_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y11):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 1
        if (len(region) == 1):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Left_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y12):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 2
        if (len(region) == 2):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Left_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y13):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 3
        if (len(region) == 3):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Left_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y14):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 4
        if (len(region) == 4):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Left_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y15):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 5
        if (len(region) == 5):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Left_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() >= y15):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
        if (len(region) == 6):
            begin = 1
    if (begin == 1):
        l = 0
        if (len(region) == 6):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Mid_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y21):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 1
        if (len(region) == 7):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Mid_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y22):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 2
        if (len(region) == 8):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Mid_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y23):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 3
        if (len(region) == 9):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Mid_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y24):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 4
        if (len(region) == 10):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Mid_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y15):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 5
        if (len(region) == 11):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Mid_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() >= y15):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
        if (len(region) == 12):
            begin = 2
    if (begin == 2):
        l = 0
        if (len(region) == 12):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Right_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y31):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 1
        if (len(region) == 13):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Right_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y32):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 2
        if (len(region) == 14):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Right_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y33):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 3
        if (len(region) == 15):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Right_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y34):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 4
        if (len(region) == 16):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Right_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() <= y35):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
                            l = 5
        if (len(region) == 17):
            for colorthreshold in color_threshold:
                blobs = img.find_blobs([colorthreshold], roi=Right_ROI[l], area_threshold=area, pixels_threshold=pixels,
                                       merge=False)
                if blobs:
                    for b in blobs:
                        if (b.cy() >= y35):
                            img.draw_rectangle(b.rect(), color=(255, 255, 255), thickness=1, merge=False)
                            img.draw_cross(b.cx(), b.cy())
                            region.append({'color': color[color_threshold.index(colorthreshold)]})
        if (len(region) == 18):
            begin = 3
            print("len(region)", len(region))

    if (begin == 3):
        green.off()
        red.on()
        for one in range(0, 18):
            if region[one]['color'] == 'green':
                color = 0x01
            elif region[one]['color'] == 'blue':
                color = 0x02
            elif region[one]['color'] == 'red':
                color = 0x03
            time.sleep_ms(50)
            FH = bytearray([0x2C, 0x12, color, 0x5B])
            uart.write(FH)
            uart.write(FH)
        time.sleep_ms(500)
        for one in range(0, 18):
            if region[one]['color'] == 'green':
                color = 0x01
            elif region[one]['color'] == 'blue':
                color = 0x02
            elif region[one]['color'] == 'red':
                color = 0x03
            time.sleep_ms(50)
            FH = bytearray([0x2C, 0x12, color, 0x5B])
            uart.write(FH)
            uart.write(FH)
            print(FH)

        time.sleep_ms(500)
        red.off()
        blue.on()
        time.sleep_ms(100)
        blue.off()
        begin = 4
