#!/bin/bash



#This is the launcher for the vdr-mame plugin



#Please modify the following lines

#Path to sdlmame
MAME="/usr/games/sdlmame"



#Joydev name
JOYDEV="/dev/input/js"



#Joystick type
# 0 No joystick
# 1 Standard joystick
# 5 SDL joystick
JOYTYPE="1"



#lircrc file
LIRCRC="/etc/lirc/vdr-mame-lircrc"



#Command to stop VDR
VDRSTOPCMD="vdr.sh stop"



#Command to start VDR
VDRSTARTCMD="vdr.sh start"



#Stop VDR if stopping wanted
STOPVDR=$1

if [ $STOPVDR = "1" ]
then
    $VDRSTOPCMD
    sleep 5
fi



ROMPATH=$2
ROMNAME=$3

COMMAND="$MAME -video opengl -resolution 1920x1080 -autoframeskip -throttle -switchres -joystick -mouse -lightgun -rompath $ROMPATH $ROMNAME"


#Execute command
export DISPLAY=:0.0
svdrpsend.pl REMO off
irexec $LIRCRC &

$COMMAND

killall -9 irexec
svdrpsend.pl REMO on



#Start VDR if stopping wanted
if [ $STOPVDR = "1" ]
then
    sleep 5
    $VDRSTARTCMD
fi



exit 0
