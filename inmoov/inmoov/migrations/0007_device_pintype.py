# Generated by Django 2.1.4 on 2019-03-17 13:32

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('inmoov', '0006_auto_20190317_0953'),
    ]

    operations = [
        migrations.AddField(
            model_name='device',
            name='pinType',
            field=models.CharField(choices=[('dig', 'Digitale'), ('ana', 'Analogique'), ('unk', 'indéterminé')], default='unk', max_length=3, null=True),
        ),
    ]
