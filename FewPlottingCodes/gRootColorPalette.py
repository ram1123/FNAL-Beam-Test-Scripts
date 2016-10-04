#! /usr/bin/env python2.6

import sys, time
from array import *
import ROOT as rt

##########################
#  Palette for 2D plots  #
##########################

NRGBs = 5
NCont = 500
stops = array("d",[0.00, 0.34, 0.61, 0.84, 1.00  ])
red   = array("d",[0.00, 0.00, 0.87, 1.00, 0.51  ])
green = array("d",[0.00, 0.81, 1.00, 0.20, 0.00  ])
blue  = array("d",[0.51, 1.00, 0.12, 0.00, 0.00  ])

rt.TColor.CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont)
rt.gStyle.SetNumberContours(NCont)

################################
#  Format for text on 2D plots #
################################

rt.gStyle.SetPaintTextFormat("4.1f");

