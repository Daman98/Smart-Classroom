from django.shortcuts import render
from django.http import HttpResponse
import paho.mqtt.client as mqtt
import time

a = ["success","danger","danger","danger"]
p = 1

# Create your views here.
def index(request):

	global a
	context = {
		"a":a,
	}
	return render(request, 'main/index.html',context)

h = "0"

def presence(request):
	ad = []
	resp = request.GET.get("resp",-1)
	if resp !=-1:
		for v in resp.split(" "):
			if v=="n":
				ad.append("danger")
			elif v=="y":
				ad.append("success")
		global a
		a = ad
		return HttpResponse("SUCCESS")
	else:
		return HttpResponse("ERROR")


def get(request):

	# Callback Function on Connection with MQTT Server
	def on_connect( client, userdata, flags, rc):
		print ("Connected with Code :" +str(rc))
		# Subscribe Topic from here
		client.subscribe("dev/test")

	# Callback Function on Receiving the Subscribed Topic/Message
	def on_message( client, userdata, msg):
		# print the message received from the subscribed topic
		global h
		h = msg.payload.decode()
		client.loop_stop()

	client = mqtt.Client()
	client.on_connect = on_connect
	client.on_message = on_message

	client.username_pw_set("username", "1234")
	client.connect("0.0.0.0", 1883, 60)

	client.loop_start()		
	return HttpResponse(h)

def get_seating(request):
	return HttpResponse('["' + '","'.join(a) + '"]')

names = ["","","",""]

def get_names(request):
	global names
	return HttpResponse('["'+'","'.join(names)+'"]')

from django.views.decorators.csrf import csrf_exempt

import re

from .models import *

@csrf_exempt 	
def set_names(request):
	if request.method=="POST":
		global names
		x = request.POST.get('file')
		if len(re.split("\r\n|\n",x))==1:
			return HttpResponse("Done")
		model = Attendance()
		for y in re.split("\r\n|\n",x):
			if y!="":
				z = y.split(" - ")
				if len(z)>1:
					names[int(z[0])-1] = z[1]
					if z[1]=="Apurva":
						model.apurva = 1
					if z[1]=="Daman":
						model.daman = 1
					if z[1]=="Samyak":
						model.samyak = 1
					if z[1]=="Shreyanshi":
						model.shreyanshi = 1
			model.save()

		return HttpResponse("Success")
	return HttpResponse("Use Post")

def index2(request):
	return render(request, 'main/index2.html',{"att":Attendance.objects.all()})