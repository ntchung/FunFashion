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
	imagesList = getFileList(TEXTURES_DIR, ['.png', '.tga'], True)
	for image in imagesList:
		src = os.path.abspath(image)
		try:
			name = src[0 : src.rindex('.')]		
		except:
			name = src
			
		try:
			format = name[name.rindex('.') + 1 : len(name)]
		except:
			format = 'r8g8b8a8'
			
		try:
			name = name[0 : name.rindex('.')]
		except:
			name = name

		print format + ' : ' + os.path.basename(name) + '.pvr' + '\n'
		spawn([PVRTexTool, '-nt', '-yflip0', '-i' + src, '-f' + format, '-o' + os.path.join(BUILD_DIR, os.path.basename(name) + '.pvr')])		

if __name__ == "__main__":
	main()