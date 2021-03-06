from django.contrib import admin
from inmoov.models import *



class ControlerAdmin(admin.ModelAdmin):
    list_display = ('title','code','controlerType','powerLine')
    list_display_links = ('title','code')
    

class FunctionAdmin(admin.ModelAdmin):
    list_display = ('title','code')
    ordering =('title',)
    
class PowerLineAdmin(admin.ModelAdmin):
    list_display = ('title','code','maxCurrent')
    ordering =('title',)
    
class PartAdmin(admin.ModelAdmin):
    ordering =('title',)
    
class ServoAdmin(admin.ModelAdmin):
    list_display = ('title','code','pinNum','prefix','index','orderType','servoType','rev','toggle','min','max')

class CommandAdmin(admin.ModelAdmin):
    list_display = ('title','function','value','speedFactor')
    
class RelayAdmin(admin.ModelAdmin):
    list_display = ('title','controler','pinNum','prefix','orderType','closeLevel')
    
admin.site.register(Part,PartAdmin)
admin.site.register(Controler, ControlerAdmin)
admin.site.register(Function,FunctionAdmin)
admin.site.register(PowerLine,PowerLineAdmin)
admin.site.register(ControlerType)
admin.site.register(Servo,ServoAdmin)
admin.site.register(ServoType)
admin.site.register(SpeedClass)
admin.site.register(OrderType)
admin.site.register(Command,CommandAdmin)
admin.site.register(Relay,RelayAdmin)
admin.site.register(Serial)
admin.site.register(TcpIp)