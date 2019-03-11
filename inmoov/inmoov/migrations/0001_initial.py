# Generated by Django 2.1.4 on 2019-03-10 15:55

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Command',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, verbose_name='intitulé')),
            ],
            options={
                'verbose_name': 'commande',
            },
        ),
        migrations.CreateModel(
            name='Controler',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, verbose_name='intitulé')),
                ('code', models.CharField(max_length=20)),
            ],
            options={
                'verbose_name': 'contrôleur',
            },
        ),
        migrations.CreateModel(
            name='ControlerType',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('brand', models.CharField(max_length=20)),
                ('model', models.CharField(max_length=20)),
                ('image', models.ImageField(blank=True, null=True, upload_to='')),
                ('maxDigitalPins', models.PositiveIntegerField()),
                ('maxAnalogPins', models.PositiveIntegerField()),
            ],
            options={
                'verbose_name': '(Contrôleur) type',
            },
        ),
        migrations.CreateModel(
            name='Device',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, verbose_name='intitulé')),
                ('code', models.CharField(max_length=20)),
                ('pinNum', models.PositiveIntegerField(blank=True, help_text='donné à titre indicatif', null=True, verbose_name='n° de broche')),
                ('prefix', models.CharField(help_text="utilisé dans l'adressage du device", max_length=10, null=True, verbose_name="préfixe pour l'adressage")),
                ('index', models.PositiveIntegerField(help_text='combiné au préfixe pour adressage', null=True)),
            ],
            options={
                'verbose_name': 'équipement',
            },
        ),
        migrations.CreateModel(
            name='Function',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, verbose_name='intitulé')),
                ('code', models.CharField(max_length=20)),
            ],
            options={
                'verbose_name': 'fonction',
            },
        ),
        migrations.CreateModel(
            name='Interface',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, verbose_name='intitulé')),
            ],
            options={
                'verbose_name': 'interface',
            },
        ),
        migrations.CreateModel(
            name='Order',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('value', models.PositiveIntegerField(blank=True, help_text='valeur envoyée', null=True, verbose_name='valeur')),
            ],
            options={
                'verbose_name': 'Ordre',
            },
        ),
        migrations.CreateModel(
            name='OrderType',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, verbose_name='intitulé')),
                ('verb', models.CharField(help_text='le verbe dépend du protocole mis en place dans le contrôleur', max_length=20, verbose_name='verbe')),
            ],
            options={
                'verbose_name': '(Ordre) type',
            },
        ),
        migrations.CreateModel(
            name='Part',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, verbose_name='intitulé')),
            ],
            options={
                'verbose_name': 'partie',
            },
        ),
        migrations.CreateModel(
            name='SensorType',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, null=True)),
            ],
            options={
                'verbose_name': 'type de senseur',
            },
        ),
        migrations.CreateModel(
            name='Sequence',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, verbose_name='intitulé')),
                ('commands', models.ManyToManyField(to='inmoov.Command')),
            ],
            options={
                'verbose_name': 'séquence de commandes',
            },
        ),
        migrations.CreateModel(
            name='ServoType',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('model', models.CharField(max_length=20, null=True, verbose_name='marque ou modèle (ou standard)')),
                ('type', models.CharField(choices=[('lin', 'Linéaire'), ('ang', 'Angulaire')], default='ang', max_length=3)),
                ('defaultMin', models.PositiveIntegerField(default=0, help_text='en action, le servo ne pourra pas aller sous cette valeur', verbose_name='valeur maximale par défaut')),
                ('defaultMax', models.PositiveIntegerField(default=180, help_text='en action, le servo ne pourra pas aller au-dessus cette valeur', verbose_name='valeur minimale par défaut')),
            ],
            options={
                'verbose_name': '(Servo) type',
            },
        ),
        migrations.CreateModel(
            name='SpeedClass',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=50, null=True)),
                ('timeInSec', models.PositiveIntegerField(verbose_name='temps en secondes')),
                ('move', models.PositiveIntegerField(null=True, verbose_name='valeur du mouvement')),
                ('unit', models.CharField(max_length=20, null=True, verbose_name='unité de mouvement')),
            ],
            options={
                'verbose_name': 'classe de vitesse',
            },
        ),
        migrations.CreateModel(
            name='PowerLine',
            fields=[
                ('function_ptr', models.OneToOneField(auto_created=True, on_delete=django.db.models.deletion.CASCADE, parent_link=True, primary_key=True, serialize=False, to='inmoov.Function')),
                ('maxCurrent', models.DecimalField(decimal_places=1, default=0, help_text='unité = A', max_digits=5, null=True, verbose_name='courant maximal prévu')),
            ],
            options={
                'verbose_name': '(Alimentation) ligne',
            },
            bases=('inmoov.function',),
        ),
        migrations.CreateModel(
            name='Relay',
            fields=[
                ('device_ptr', models.OneToOneField(auto_created=True, on_delete=django.db.models.deletion.CASCADE, parent_link=True, primary_key=True, serialize=False, to='inmoov.Device')),
                ('closeLevel', models.CharField(choices=[('Low', 'Niveau bas'), ('High', 'Niveau haut')], default='Low', help_text='précise le niveau à donner à la broche pour fermer le relais', max_length=5, verbose_name='niveau fermé')),
            ],
            options={
                'verbose_name': 'relais',
            },
            bases=('inmoov.device',),
        ),
        migrations.CreateModel(
            name='Sensor',
            fields=[
                ('device_ptr', models.OneToOneField(auto_created=True, on_delete=django.db.models.deletion.CASCADE, parent_link=True, primary_key=True, serialize=False, to='inmoov.Device')),
                ('mesureUnit', models.CharField(max_length=20, null=True, verbose_name='unité de mesure')),
                ('sensorType', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.SensorType', verbose_name='type de senseur')),
            ],
            options={
                'verbose_name': 'senseur',
            },
            bases=('inmoov.device',),
        ),
        migrations.CreateModel(
            name='Serial',
            fields=[
                ('interface_ptr', models.OneToOneField(auto_created=True, on_delete=django.db.models.deletion.CASCADE, parent_link=True, primary_key=True, serialize=False, to='inmoov.Interface')),
                ('port', models.CharField(help_text='depending on operating system. e.g. /dev/ttyUSB0 on GNU/Linux or COM3 on Windows.', max_length=100, verbose_name="nom de l'interface")),
                ('baudrate', models.CharField(choices=[('9600', '9600'), ('19200', '19200'), ('57600', '57600'), ('115200', '115200')], default='115200', max_length=10, verbose_name='débit (baudrate)')),
                ('bytesize', models.CharField(choices=[('FIVEBITS', '5'), ('SIXBITS', '6'), ('SEVENBITS', '7'), ('EIGHTBITS', '8')], default='8', max_length=100, verbose_name='octets de données (bytesize)')),
                ('parity', models.CharField(choices=[('PARITY_NONE', 'None'), ('PARITY_EVEN', 'Even'), ('PARITY_ODD', 'Odd'), ('PARITY_MARK', 'Mark'), ('PARITY_SPACE', 'Space')], default='None', max_length=100)),
                ('stopbits', models.CharField(choices=[('STOPBITS_ONE', '1'), ('STOPBITS_ONE_POINT_FIVE', '1,5'), ('STOPBITS_TWO', '2')], default='1', max_length=20, verbose_name='bits de stop')),
                ('xonxoff', models.BooleanField(default=False, verbose_name='xonxoff : Enable software flow control')),
                ('rtscts', models.BooleanField(default=False, verbose_name='Enable hardware (RTS/CTS) flow control.')),
                ('dsrdtr', models.BooleanField(default=False, verbose_name='Enable hardware (DSR/DTR) flow control.')),
                ('write_timeout', models.CharField(default='None', help_text='Set a write timeout value', max_length=20)),
                ('inter_byte_timeout', models.CharField(default='None', help_text='Inter-character timeout, None to disable (default).', max_length=20)),
                ('exclusive', models.CharField(default='None', help_text=' Set exclusive access mode (POSIX only). A port cannot be opened in exclusive access mode if it is already open in exclusive access mode.', max_length=20)),
            ],
            options={
                'verbose_name': '(Série) interface',
            },
            bases=('inmoov.interface',),
        ),
        migrations.CreateModel(
            name='Servo',
            fields=[
                ('device_ptr', models.OneToOneField(auto_created=True, on_delete=django.db.models.deletion.CASCADE, parent_link=True, primary_key=True, serialize=False, to='inmoov.Device')),
                ('rev', models.BooleanField(help_text='inverser le sens de fonctionnement', verbose_name='reverse')),
                ('toggle', models.BooleanField(help_text='le servo se comporte comme un interrupteur', verbose_name='trigger')),
                ('min', models.PositiveIntegerField(help_text='en action, le servo ne pourra pas aller sous cette valeur', verbose_name='valeur minimale')),
                ('max', models.PositiveIntegerField(help_text='en action, le servo ne pourra pas aller au-dessus de cette valeur', verbose_name='valeur maximale')),
            ],
            options={
                'verbose_name': 'servo',
            },
            bases=('inmoov.device',),
        ),
        migrations.CreateModel(
            name='TcpIp',
            fields=[
                ('interface_ptr', models.OneToOneField(auto_created=True, on_delete=django.db.models.deletion.CASCADE, parent_link=True, primary_key=True, serialize=False, to='inmoov.Interface')),
            ],
            options={
                'verbose_name': 'interface TCP/IP',
            },
            bases=('inmoov.interface',),
        ),
        migrations.AddField(
            model_name='servotype',
            name='speedClass',
            field=models.ForeignKey(help_text='la classe de vitesse est indispensable pour moduler la vitesse du servo', null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.SpeedClass', verbose_name='classe de vitesse'),
        ),
        migrations.AddField(
            model_name='order',
            name='device',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.Device'),
        ),
        migrations.AddField(
            model_name='interface',
            name='accessTo',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.Controler', verbose_name='interface'),
        ),
        migrations.AddField(
            model_name='function',
            name='part',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.Part', verbose_name='Partie'),
        ),
        migrations.AddField(
            model_name='device',
            name='controler',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='inmoov.Controler', verbose_name='contrôleur de rattachement'),
        ),
        migrations.AddField(
            model_name='device',
            name='orderType',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.OrderType'),
        ),
        migrations.AddField(
            model_name='controler',
            name='controlerType',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.ControlerType', verbose_name='type de contrôleur'),
        ),
        migrations.AddField(
            model_name='command',
            name='function',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.Function'),
        ),
        migrations.AddField(
            model_name='command',
            name='order',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.Order'),
        ),
        migrations.AddField(
            model_name='servo',
            name='servoType',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.ServoType', verbose_name='type de servo'),
        ),
        migrations.AddField(
            model_name='controler',
            name='powerLine',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='inmoov.PowerLine', verbose_name='Alimentation'),
        ),
    ]
