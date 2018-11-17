from django.db import models

# Create your models here.
class Attendance(models.Model):
	samyak = models.BooleanField(default = 0)
	shreyanshi = models.BooleanField(default = 0)
	apurva = models.BooleanField(default = 0)
	daman = models.BooleanField(default = 0)
	date = models.DateTimeField(auto_now_add=True)