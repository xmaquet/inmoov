# Generated by Django 2.1.4 on 2019-03-17 14:33

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('inmoov', '0009_auto_20190317_1524'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='command',
            name='device',
        ),
        migrations.AddField(
            model_name='function',
            name='device',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.Device'),
        ),
    ]
