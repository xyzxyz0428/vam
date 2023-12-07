#!/usr/bin/env python

# This is a simple HMI display simulator for x86 platform
# It understands the HMI XML strings and tried to load the relevant icons
# and audio files when requested
# Built using pygame (sudo easy_install pygame)

import os
import socket
import signal
import select
import sys
import time
import threading

try:
  import pygame
except:
  print >> sys.stderr, "Missing pygame framework:"
  print >> sys.stderr, "\tsudo apt-get install python-pygame"
  raise

from optparse import OptionParser
from xml.dom.minidom import parseString

# Define display size
# Xenarc display is 640x480, but create additional debug info panel along the bottom
size = width, height = 640, 560
black = 0, 0, 0

# Attempt to start window about halfway across the screen
os.environ['SDL_VIDEO_WINDOW_POS'] = '640,0'

# Init pygame
pygame.init()

# Screen is: icon area, text alert, and additional info panel
pygame.display.set_caption('Display')
screen = pygame.display.set_mode(size)
beatwindow = pygame.Surface([width,40])
iconwindow = pygame.Surface([width,400])
textwindow = pygame.Surface([width,80])
infowindow = pygame.Surface([width,40])

def signal_handler(signal, frame):
    sys.exit(1)

def clearbeatarea():
    beatwindow.fill(black)
    screen.blit(beatwindow, (0, 0))
    pygame.display.flip()

def clearinfoarea():
    infowindow.fill(black)
    screen.blit(infowindow, (0, 520))
    pygame.display.flip()

def cleariconarea():
    iconwindow.fill(black)
    textwindow.fill(black)
    screen.blit(iconwindow, (0, 40))
    screen.blit(textwindow, (0, 440))
    pygame.display.flip()
    

# sample XML output:
# <ui_request><app_id>3</app_id><app_type>V2V</app_type><severity>100</severity>
# <tti_ms>450</tti_ms><icon>/mnt/ubi/asd/ui/RSA/SPEED/50_flash.gif</icon>
# <alt_icon>/mnt/ubi/asd/ui/RSA/SPEED/50_solid.gif</alt_icon>
# <icon_rate_sec>2</icon_rate_sec><text>Speed Limit 50 km/h</text>
# <audio>/mnt/ubi/asd/ui/RSA/short_alert.wav</audio></ui_request>


def main():

    usage = """usage: %prog [-a IP] [-p port]
        Emulate OBU display unit"""

    parser = OptionParser(usage=usage)
    parser.add_option("-a", "--ip-address", dest="ip_address",
                      help="IPv4 address to receive HMI sequences")
    parser.add_option("-p", "--port", dest="port_num",
                      help="port number to receive HMI sequences")
    (options, args) = parser.parse_args()

    # default host
    hostname = "127.0.0.1"
    port     = 7100

    signal.signal(signal.SIGINT, signal_handler)

    if (options.port_num):
        port = int(options.port_num)
    if (options.ip_address):
        hostname = options.ip_address

    # Create UDP socket
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.bind((hostname,port))
        print "Bind to ", hostname, port
    except:
        print "Can't bind to ", hostname, port
        sys.exit(0)

    lasticondisplay_t = 0;
    lastinfodisplay_t = 0;
    lastbeatdisplay_t = 0;
    lastSeverity = 0;

    # Run continuously, waiting on UDP data
    while 1:
        inputs = [s]
        rdy = select.select(inputs,[],[],1)

        # Simple timeout for clearing icon area
        if ((time.time() - lasticondisplay_t) > 2):
            cleariconarea();
            lastSeverity = 0;

        # Simple timeout for clearing heartbeat area
        if ((time.time() - lastbeatdisplay_t) > 1):
            clearbeatarea();

        # Simple timeout for clearing info area
        if ((time.time() - lastinfodisplay_t) > 2):
            clearinfoarea();

        if (rdy[0] and (rdy[0][0] == s)):

            xmltext, addr = s.recvfrom( 10000 )
            xmltext = xmltext.replace('\0','')
            #print "received message:", xmltext


            try:
                #parse the xml you got from the file
                dom = parseString(xmltext)
            except:
                print "Malformed XML: %s" % (xmltext)

            # Handle the heatbeat message
            if (dom.getElementsByTagName('heartbeat')):
                # Display stuff
                tempId = dom.getElementsByTagName('tempID')[0].firstChild.data
                numRemotes = int(dom.getElementsByTagName('numRemotes')[0].firstChild.data)
                numIntersections = int(dom.getElementsByTagName('numIntersections')[0].firstChild.data)
                txPower = int(dom.getElementsByTagName('txPower')[0].firstChild.data)

                infoData = "Id:"+str(tempId)+" Ints:"+str(numIntersections)+" Remotes:"+str(numRemotes)+" TxPower:"+str(txPower)

                # Display some heartbeat
                #print infoData
                ifont = pygame.font.Font(None, 36)
                itext = ifont.render(infoData, 1, (255, 255, 255))
                itextpos = itext.get_rect()
                itextpos.centerx = beatwindow.get_rect().centerx
                itextpos.centery = beatwindow.get_rect().centery

                beatwindow.fill(black)
                beatwindow.blit(itext, itextpos)

                lastbeatdisplay_t = time.time()

                # Write text
                screen.blit(beatwindow, (0, 0))
                pygame.display.flip()


            # Handle the info message
            try:
                appId = int(dom.getElementsByTagName('app_id')[0].firstChild.data)
            except:
                continue

            # AppId 99 is the debug position info (when enabled)
            # Displayed to info panel
            if (appId == 99):
                infoData = dom.getElementsByTagName('text')[0].firstChild.data

                # Display some info
                #print infoData
                ifont = pygame.font.Font(None, 36)
                itext = ifont.render(infoData, 1, (255, 255, 255))
                itextpos = itext.get_rect()
                itextpos.centerx = infowindow.get_rect().centerx
                itextpos.centery = infowindow.get_rect().centery

                infowindow.fill(black)
                infowindow.blit(itext, itextpos)

                lastinfodisplay_t = time.time()

                # Write text
                screen.blit(infowindow, (0, 520))
                pygame.display.flip()

            else:
                # Other appId alerts handled on icon/text area

                severity = int(dom.getElementsByTagName('severity')[0].firstChild.data)
                if (severity < lastSeverity):
                    continue

                # Handle the alert message
                audioData = None;
                iconData = None
                altIconData = None
                textData = None
                if (dom.getElementsByTagName('icon')):
                    if (dom.getElementsByTagName('icon')[0].firstChild):
                        iconData = dom.getElementsByTagName('icon')[0].firstChild.data
                        altIconData = dom.getElementsByTagName('alt_icon')[0].firstChild.data
                        if (dom.getElementsByTagName('text')[0].firstChild != None):
                            textData = dom.getElementsByTagName('text')[0].firstChild.data
                        #print iconData
                        #print altIconData
                        #print textData

                        if (dom.getElementsByTagName('audio')[0].firstChild):
                            audioData = dom.getElementsByTagName('audio')[0].firstChild.data
                            #print audioData

                            # play alert
                            if (audioData != None):
                                if (os.path.isfile(audioData)):
                                    try:
                                        pygame.mixer.music.load(audioData)
                                        pygame.mixer.music.play()
                                    except:
                                        print "error with audio file '%s'" % audioData
                                else:
                                    print "no audio file '%s'" % audioData

                img = None
                if (iconData != None):
                    if (os.path.isfile(iconData)):
                        try:
                            img = pygame.image.load(iconData)
                            imgrect = img.get_rect()
                        except:
                            print "error with image file '%s'" % iconData
                    else:
                        print "no image file '%s'" % iconData

                altimg = None
                if (altIconData != None):
                    if (os.path.isfile(altIconData)):
                        try:
                            altimg = pygame.image.load(altIconData)
                            altimgrect = altimg.get_rect()
                        except:
                            print "error with alt image file '%s'" % altIconData
                    else:
                        print "no alt image file '%s'" % altIconData

                # Blank icon area
                iconwindow.fill(black)

                lasticondisplay_t = time.time()
                lastSeverity = severity

                # Display some text
                font = pygame.font.Font(None, 72)
                text = font.render(textData, 1, (255, 255, 255))
                textpos = text.get_rect()
                textpos.centerx = textwindow.get_rect().centerx
                textpos.centery = textwindow.get_rect().centery

                textwindow.fill(black)
                textwindow.blit(text, textpos)

                # Write text
                screen.blit(textwindow, (0, 440))

                # Render graphic
                if (img):
                    iconwindow.blit(img, imgrect)
                screen.blit(iconwindow, (0, 40))
                pygame.display.flip()

                if (iconData != altIconData):
                    # Render graphic (with alternating image)
                    time.sleep(0.2)
                    if (altimg):
                        iconwindow.blit(altimg, altimgrect)
                    screen.blit(iconwindow, (0, 40))
                    pygame.display.flip()
                    time.sleep(0.2)
                    if (img):
                        iconwindow.blit(img, imgrect)
                    screen.blit(iconwindow, (0, 40))
                    pygame.display.flip()

if __name__=='__main__':
        main()

