############################################################
#		 To Do List	
#
#	1. 
#
#
#
############################################################
#		Basic Info about this Macro
#
#
#
#
############################################################

import sys

try:
	fp = open("ClassReadTree.h")
except IOError:
	sys.exit('\n=>  ERROR:: File not found : ClassReadTree.h\n')
else:
	print('File ClassReadTree.h opened')

sys.stdout = open('ClassReadTree.cc', 'w')

start1 = 0
start2 = 0
start3 = 0
for i, line in enumerate(fp):
    if "class ClassReadTree {" in line:
	print('Could not find line containing "class ClassReadTree {"')
	#print "line number is = ",i
        start1 = 1
    else:
	sys.exit('Could not find line containing "class ClassReadTree {"')

    if start1 == 1:
        print line
        if "}" in line:
            start1 = 0
    	else:
	    sys.exit('Could not find closing braces }')

    if "ClassReadTree::Init(" in line:
        #print "line number is = ",i
        start2 = 1
    else:
	sys.exit('Could not find line containing "ClassReadTree::Init("')

    if start2 == 1:
        print line
        if "}" in line:
            start2 = 0
    	else:
	    sys.exit('Could not find closing braces }')
    if "ClassReadTree::~ClassReadTree()" in line:
        start3 = 1
    else:
	sys.exit('Could not find line containing "ClassReadTree::~ClassReadTree()"')
    if start3 == 1:
        print line
        if "}" in line:
            start3 = 0
    	else:
	    sys.exit('Could not find closing braces }')
fp.close()
