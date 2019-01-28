from django.shortcuts import render,redirect
from inmoov.models import Part
from datetime import datetime


def dashboard(request):
    return render(request,'dashboard.html')