from Tkinter import *
from threading import *
from copy import *
import numpy as np
import commands
from mpmath import *
import svm

POINT_RADIO = 5
POINT_POLI_RADIO = 2
WIDTH = 800
HEIGHT = 600

DESPL_X = 31.7
DESPL_Y = 18.7
ORIGEN = (17,521)
TOP = 64

red_points = []
blue_points = []
g = []

canvas = 0
plano = 0
master = 0

ans = 'help'
mem = 'help'



def plotLine(x1,y1,x2,y2,color):
	global canvas;
	global ORIGEN
	global DESPL_X
	global DESPL_Y
	pointX1 = x1 * DESPL_X + ORIGEN[0]
	pointY1 = ORIGEN[1] -  (y1 * DESPL_Y)
	pointX2 = x2 * DESPL_X + ORIGEN[0]
	pointY2 = ORIGEN[1] -  (y2 * DESPL_Y)
	if(pointY1 < ORIGEN[1] and pointY1 > TOP and pointY2 < ORIGEN[1] and pointY2 > TOP):
		canvas.create_line(pointX1,pointY1,pointX2,pointY2,fill=color)

def plotFunLine(x,y,color):
	for i in range(0,len(x) - 1):
		plotLine(x[i],y[i],x[i+1],y[i+1],color)
	#for i in range(0,len(x)):
	#	plotPoint(x,y,color,POINT_POLI_RADIO)

def plotPoints():
	global red_points
	global blue_points
	for e in red_points:
		plotPoint(e[0],e[1],'red',POINT_RADIO)
	for e in blue_points:
		plotPoint(e[0],e[1],'blue',POINT_RADIO)

def plotSVM(w,b,S):
	tx = np.arange(0.0,24.5,0.1)
	ty = (-w[0] * tx - b) / w[1]
	tx1 = tx
	ty1 = (-w[0]/w[1]) * (tx - S[0][0]) + S[0][1]
	tx2 = tx
	ty2 = (-w[0]/w[1]) * (tx - S[len(S) - 1][0]) + S[len(S) - 1][1]
	
	plotFunLine(tx,ty,"blue")
	plotFunLine(tx1,ty1,"green")
	plotFunLine(tx2,ty2,"green")


def resetCanvas():
	global canvas;
	global master;
	global plano;
	global red_points;
	global blue_points;
	canvas.delete("all")
	red_points = []
	blue_points = []

	tracking_function_left = track_to_list_left(red_points)
	tracking_function_right = track_to_list_right(blue_points)
	tracking_function_medium = track_to_list_medium(g)
	canvas.bind('<Button-1>', lambda event: tracking_function_left(event))
	canvas.bind('<Button-2>', lambda event: tracking_function_medium(event))
	canvas.bind('<Button-3>', lambda event: tracking_function_right(event))
	canvas.pack()	


def svmAction():
	tempRed = deepcopy(red_points)
	tempBlue = deepcopy(blue_points)
	resetCanvas()
	copyPoints(tempRed,tempBlue)				
	plotPoints()
	x,y = svm.concatPoints(red_points,blue_points)
	alfa,w,b,S = svm.SVM(x,y)
	plotSVM(w,b,S)	

def track_to_list_left(lts):
    def left_mouse_click(event):
    	if(event.y >= TOP and event.y <= ORIGEN[1] and event.x >= ORIGEN[0]):
        	canvas = event.widget
        	canvas.create_oval(event.x-POINT_RADIO,event.y-POINT_RADIO,event.x+POINT_RADIO,event.y+POINT_RADIO,fill='red',width=1)
        	pointX = float(event.x - ORIGEN[0]) / DESPL_X
        	pointY = float(ORIGEN[1] - event.y) / DESPL_Y
        	lts.append((pointX, pointY))
    return left_mouse_click

def track_to_list_right(lts):
    def right_mouse_click(event):
    	if(event.y >= TOP and event.y <= ORIGEN[1] and event.x >= ORIGEN[0]):
        	canvas = event.widget
        	canvas.create_oval(event.x-POINT_RADIO,event.y-POINT_RADIO,event.x+POINT_RADIO,event.y+POINT_RADIO,fill='blue',width=1)
        	pointX = float(event.x - ORIGEN[0]) / DESPL_X
        	pointY = float(ORIGEN[1] - event.y) / DESPL_Y
        	lts.append((pointX, pointY))
    return right_mouse_click

def track_to_list_medium(lts):
	global red_points;
	global blue_points;
	def medium_mouse_click(event):
		if(event.y >= TOP and event.y <= ORIGEN[1] and event.x >= ORIGEN[0]):
			canvas = event.widget
			color = ''
			flag = False
			pointX = float(event.x - ORIGEN[0]) / DESPL_X
			pointY = float(ORIGEN[1] - event.y) / DESPL_Y
			xx,yy = svm.concatPoints(red_points,blue_points)
			alfa,w,b,S = svm.SVM(xx,yy)
			e = svm.verifyPoint(xx,yy,alfa,b,[pointX,pointY])
			if(e <= 0.0):
				color = "red"
				if(e >= -1.0):
					flag = True
			else:
				color = "blue"
				if(e <= 1.0):
					flag = True			
			canvas.create_oval(event.x-POINT_RADIO,event.y-POINT_RADIO,event.x+POINT_RADIO,event.y+POINT_RADIO,fill=color,width=1)
			if(color == "red"):
				red_points.append((pointX,pointY))
			elif(color == "blue"):
				blue_points.append((pointX,pointY))
			if(flag == True):
				svmAction()
	return medium_mouse_click


def Interfaz():

	global master
	global plano
	global canvas
	master = Tk()

	canvas = Canvas(master, width=WIDTH, height=HEIGHT)
	canvas.pack()

	tracking_function_left = track_to_list_left(red_points)
	tracking_function_right = track_to_list_right(blue_points)
	tracking_function_medium = track_to_list_medium(g)
	canvas.bind('<Button-1>', lambda event: tracking_function_left(event))
	canvas.bind('<Button-2>', lambda event: tracking_function_medium(event))
	canvas.bind('<Button-3>', lambda event: tracking_function_right(event))


	mainloop()


def copyPoints(red,blue):
	for e in red:
		red_points.append(e)
	for e in blue:
		blue_points.append(e)

def plotPoint(x,y,color,radio):
	global canvas;
	global ORIGEN
	global DESPL_X
	global DESPL_Y
	pointX = mpf(x) * mpf(DESPL_X) + mpf(ORIGEN[0])
	pointY = mpf(ORIGEN[1]) -  (mpf(y) * mpf(DESPL_Y))
	canvas.create_oval(pointX-radio,pointY-radio,pointX+radio,pointY+radio,fill=color,width=1)



while(True):
	
	svmAction()

master.quit()

