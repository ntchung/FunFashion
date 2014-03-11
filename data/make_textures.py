import os
import sys
import time
import glob
import re
import shutil
import getopt
import tempfile
from ftplib import FTP
from distutils.spawn import spawn

#---- General paths
DATA_DIR				= os.getcwd()
TEXTURES_DIR		= os.path.join(DATA_DIR, 'textures')
BUILD_DIR				= os.path.join(DATA_DIR, '../build/data')

PVRTexTool				= os.path.join(DATA_DIR, 'PVRTexTool.exe')

def getFileList(folder, extensions, recursive=False) :
	listfiles = []
	for top, dirs, files in os.walk(folder):
		for nm in files:
			for ext in extensions:
				if nm.endswith(ext) :
					listfiles.append( os.path.join(top, nm) )
	return listfiles

def main():
	imagesList = getFileList(TEXTURES_DIR, ['.meta'], True)
	for image in imagesList:
		meta = os.path.abspath(image)

		format = 'OGL8888'
		mipmap = ''
		wrapMode = 'R'
		filteringMode = 'B'

		# Read meta information
		with open(meta) as f:
		    for line in f:
		        args = line.split()
		        if args[0] == 'FORMAT':
		        	format = args[1]
		        elif args[0] == 'MIPMAP':
		        	if args[1] == 'On':
		        		mipmap = '-m'
		        elif args[0] == 'WRAPMODE':
		        	wrapMode = args[1][0]
		        elif args[0] == 'FILTERMODE':
		        	filteringMode = args[1][0]

		# Convert the file
		img = meta[0:meta.rindex('.')]
		pvrname = os.path.join(BUILD_DIR, os.path.basename(img[0:img.rindex('.')]) + '.pvr')

		spawn([PVRTexTool, '-nt', '-yflip0', mipmap, '-i' + img, '-f' + format, '-oout.pvr'])

		# Store the pvr data
		pvrdat = ''
		with open('out.pvr', 'rb') as f:
			pvrdat = f.read();

		# Output to target file
		with open(pvrname, 'wb') as f:
			f.write('TEXT')
			f.write(wrapMode)
			f.write(filteringMode)
			f.write(pvrdat)

if __name__ == "__main__":
	main()
