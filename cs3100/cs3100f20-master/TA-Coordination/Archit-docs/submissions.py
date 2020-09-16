# Run as follows:
# python submission.py <submissions_folder>

from glob import glob
import subprocess
import sys

path = sys.argv[1]

# Add a slash at the end if not provided
if path[-1] != '/':
	path += '/'

zips = glob(path + '*.zip')

for filename in zips:
	student_name = filename.split('/')[-1].split('_')[0]
	rmdir = ['rm', '-rf', path + student_name]
	makedir_cmd = ['mkdir', path + student_name]
	extract_cmd = ['unzip', '-j', filename, '-d', path + student_name]
	makepdf_cmd = ['jupyter-nbconvert', '--to', 'pdf', path + student_name + '/' + '*.ipynb']
	print(' '.join(makepdf_cmd))	
	subprocess.call(rmdir, stdout=subprocess.PIPE)
	subprocess.call(makedir_cmd, stdout=subprocess.PIPE)
	subprocess.call(extract_cmd, stdout=subprocess.PIPE)
	subprocess.call(makepdf_cmd, stdout=subprocess.PIPE)
